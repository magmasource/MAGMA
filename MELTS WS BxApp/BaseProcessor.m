//
//  BaseProcessor.m
//  MELTS
//
//  Created by Mark Ghiorso on 1/7/13.
//  Copyright (c) 2013 Mark Ghiorso. All rights reserved.
//

#import "BaseProcessor.h"
#import "AppDelegate.h"

@implementation BaseProcessor

-(id)init {
    if ((self = [super init])) {
        _respondUsingJSON = NO;
        _inputXML = nil;
        _debug = YES;
    }
    return self;
}

-(NSString *)parseAndValidateInputXMLAsString:(NSString *)inputXMLString orAsData:(NSData *)inputXMLData  {
    NSError *error = nil;
    if (inputXMLString)    [self setInputXML:[[NSXMLDocument alloc] initWithXMLString:inputXMLString options:NSXMLNodeOptionsNone error:&error]];
    else if (inputXMLData) [self setInputXML:[[NSXMLDocument alloc] initWithData:inputXMLData        options:NSXMLNodeOptionsNone error:&error]];
    else                   return @"Internal error in creation of XML Document";
    if (error) return [error description];
    
    NSString *xsdPath = [[NSBundle mainBundle] pathForResource:@"MELTSinput" ofType:@"xsd"];
    NSXMLNode *noNamespaceSchemaLocation = [NSXMLNode attributeWithName:@"xsi:noNamespaceSchemaLocation" stringValue:xsdPath];
    NSXMLElement *rootElement = [[self inputXML] rootElement];
    NSMutableArray *rootAttributes = [[rootElement attributes] mutableCopy];
    [rootAttributes replaceObjectAtIndex:1 withObject:noNamespaceSchemaLocation];
    [rootElement setAttributes:rootAttributes];
    if (![[self inputXML] validateAndReturnError:&error]) return @"The input XML is NOT valid";
    if (error) return [error description];
    
    return nil;
}

-(id)renderWithTransport:(BxTransport *)transport {
    if (self.debug) {
        NSLog(@"BaseProcessor Class:(renderWithTransport) Entry...");
        NSLog(@"Query variables:  %@", [[transport queryVars] description]);
        NSLog(@"Post variables:   %@", [[transport postVars] description]);
        NSLog(@"Server variables: %@", [[transport serverVars] description]);
        NSLog(@"Cookies:          %@", [[transport cookies] description]);
        [(AppDelegate *)[self app] lockState];
        NSLog(@"State:            %@", [[[self app] state] description]);
        [(AppDelegate *)[self app] unloackState];
        if ([transport rawPostData]) NSLog(@"Raw post data are available");
        else NSLog(@"Raw post data are not available.");
    }
    [transport setHeader:@"Access-Control-Allow-Origin" value:@"*"];
    [transport setHeader:@"Access-Control-Allow-Methods" value:@"GET,POST,OPTIONS"];
    [transport setHeader:@"Access-Control-Allow-Headers" value:@"Content-Type"];
    [transport setHeader:@"Access-Control-Max-Age" value:@"86400"];
    
    if ([[transport postVars] objectForKey:@"dataXML"]) {
        NSString *error = nil;;
        if (self.debug) NSLog(@"... input data transmitted as a post variable (dataXML) string.");
        if ((error = [self parseAndValidateInputXMLAsString:[[transport postVars] objectForKey:@"dataXML"] orAsData:nil])) {
            [transport setHttpStatusCode:400];
            [transport writeFormat:@"<p>MELTS WS: Error in parsing of XML string form data: %@</p>", error];
            return self;
        }
        if (self.debug) NSLog(@"...BaseProcessor Class:(renderWithTransport) XML Document is valid.");
    } else if ([[transport postVars] objectForKey:@"dataJSON"]) {
        [transport setHttpStatusCode:415];
        [transport write:@"<p>MELTS WS: Parsing of JSON input is not yet supported.</p>"];
        return self;
    } else if ([transport rawPostData] && [[[transport serverVars] objectForKey:@"CONTENT_TYPE"] hasPrefix:@"text/xml"]) {
        NSString *error = nil;;
        if (self.debug) NSLog(@"... input data transmitted as a post variable (dataXML) string.");
        if ((error = [self parseAndValidateInputXMLAsString:nil orAsData:[transport rawPostData]])) {
            [transport setHttpStatusCode:400];
            [transport writeFormat:@"<p>MELTS WS: Error in parsing of XML string form data: %@</p>", error];
            return self;
        }
        if (self.debug) NSLog(@"...BaseProcessor Class:(renderWithTransport) XML Document is valid.");
    } else {
        [transport setHttpStatusCode:415];
        [transport write:@"<p>MELTS WS: Unrecognizable or unspecified input.</p>"];
        return self;
    }
    
    [self setRespondUsingJSON:NO];
    if ([[transport postVars] objectForKey:@"returnJSON"]) [self setRespondUsingJSON:YES];
    
    NSString *sessionId = [[transport cookies] objectForKey:@"sessionid"];
    
    if (!sessionId) {
        NSError *err;
        NSArray *levelOneChildrenWithSessionID = [[self inputXML] nodesForXPath:@".//sessionID" error:&err];
        if (levelOneChildrenWithSessionID && ([levelOneChildrenWithSessionID count] > 0)) {
            sessionId = [(NSXMLElement *)[levelOneChildrenWithSessionID objectAtIndex:0] stringValue];
            if (self.debug) NSLog(@"... BaseProcessor Class: Obtained session cookie from XML Input: %@", sessionId);
        }
    }
    
    // Lock thread from here to ...
    [(AppDelegate *)[self app] lockState];
    
    rMELTSframework *melts = nil;
    if (!sessionId) {
        sessionId = [NSString stringWithFormat:@"%f.%ld", [NSDate timeIntervalSinceReferenceDate], random()];
        [transport setCookie:@"sessionid" value:sessionId];
        melts = [[rMELTSframework alloc] init];
        [[[self app] state] setObject:melts forKey:sessionId];
    } else melts = [[[self app] state] objectForKey:sessionId];
    
    NSUInteger calculationMode = [melts parseAndLoadDataStructuresFromXMLDocument:[self inputXML]];
    if (self.debug) NSLog(@"...BaseProcessor Class:(renderWithTransport) Input parsed, MELTS initialized %lu.", calculationMode);
    
    
    if ([melts performMELTScalculation:calculationMode] && self.debug) NSLog(@"...BaseProcessor Class:(renderWithTransport) MELTS call - success.");
    else if (self.debug)                                               NSLog(@"...BaseProcessor Class:(renderWithTransport) MELTS call - failure.");
    
    NSXMLDocument *outputXML = [melts writeDataStructuresToXMLDocument:sessionId];
    
    [(AppDelegate *)[self app] unloackState];
    // ... to here
    
    if (![self respondUsingJSON]) {
        [transport setHeader:@"Content-type" value:@"text/xml"];
        [transport writeData:[outputXML XMLData]];
    } else {
        if (self.debug) NSLog(@"...BaseProcessor Class:(renderWithTransport) Transform XML to JSON.");
        NSError *err = nil;
        NSString *xsltPath = [[NSBundle mainBundle] pathForResource:@"xml2json" ofType:@"xslt"];
        if (!xsltPath) {
            [transport setHttpStatusCode:500];
            [transport write:@"<p>MELTS WS: Internal error in converting XML to JSON.</p>"];
            if (self.debug) NSLog(@"...BaseProcessor Class:(renderWithTransport) Error in transforming XML to JSON.");
            return self;
        }
        NSData *JSONdata = (NSData *)[outputXML objectByApplyingXSLTAtURL:[NSURL fileURLWithPath:xsltPath]
                                                                arguments:nil  // no extra XSLT parameters needed
                                                                    error:&err];
        if (!JSONdata) {
            [transport setHttpStatusCode:500];
            [transport write:@"<p>MELTS WS: Internal error in converting XML to JSON.</p>"];
            if (self.debug) NSLog(@"<p>...BaseProcessor Class:(renderWithTransport) Error - no transformed file.</p>");
            return self;
        }
        if (err) {
            [transport setHttpStatusCode:500];
            [transport write:@"<p>MELTS WS: Internal error in converting XML to JSON.</p>"];
            if (self.debug) NSLog(@"<p>...BaseProcessor Class:(renderWithTransport) Err: %@.</p>", [err localizedDescription]);
            return self;
        }
        
        [transport setHeader:@"Content-type" value:@"application/json"];
        [transport writeData:JSONdata];
    }
    
    return self;
}

@end
