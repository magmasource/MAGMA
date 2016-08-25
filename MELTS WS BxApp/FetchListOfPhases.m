//
//  FetchListOfPhases.m
//  MELTS
//
//  Created by Mark Ghiorso on 2/3/13.
//  Copyright (c) 2013 Mark Ghiorso. All rights reserved.
//

#import "FetchListOfPhases.h"

@implementation FetchListOfPhases

-(id)init {
    if ((self = [super init])) {
        _debug = YES;
    }
    return self;
}

- (id)renderWithTransport:(BxTransport *)transport {
    if (self.debug) {
        NSLog(@"FetchListOfPhases Class:(renderWithTransport) Entry...");
        NSLog(@"Query variables:  %@", [[transport queryVars] description]);
        NSLog(@"Post variables:   %@", [[transport postVars] description]);
        NSLog(@"Server variables: %@", [[transport serverVars] description]);
        NSLog(@"Cookies:          %@", [[transport cookies] description]);
        if ([transport rawPostData]) NSLog(@"Raw post data are available");
        else NSLog(@"Raw post data are not available.");
    }
    [transport setHeader:@"Access-Control-Allow-Origin" value:@"*"];
    [transport setHeader:@"Access-Control-Allow-Methods" value:@"GET,POST,OPTIONS"];
    [transport setHeader:@"Access-Control-Allow-Headers" value:@"Content-Type"];
    [transport setHeader:@"Access-Control-Max-Age" value:@"86400"];
    
    [transport setHeader:@"Content-type" value:@"text/xml"];
    
    if ([[transport postVars] objectForKey:@"modelSelection"]) {
        if (self.debug) NSLog(@"... Phase list requested for non-default calibration.");
        NSString *modelSelection = [transport.postVars objectForKey:@"modelSelection"];
        
        if ([modelSelection isEqualToString:@"MELTS_v1.0.x"]) {
            [transport writeData:[[rMELTSframework phaseListAsXMLDocument:@"MELTS_v1.0.x"] XMLData]];
        } else if ([modelSelection isEqualToString:@"MELTS_v1.1.x"]) {
            [transport writeData:[[rMELTSframework phaseListAsXMLDocument:@"MELTS_v1.1.x"] XMLData]];
        } else if ([modelSelection isEqualToString:@"MELTS_v1.2.x"]) {
            [transport writeData:[[rMELTSframework phaseListAsXMLDocument:@"MELTS_v1.2.x"] XMLData]];
        } else if ([modelSelection isEqualToString:@"pMELTS_v5.6.1"]) {
            [transport writeData:[[rMELTSframework phaseListAsXMLDocument:@"MELTS_v5.6.1"] XMLData]];
        } else {
            NSString *error = [NSString stringWithFormat:@"Invalid modelSelection quaery: the designator %@ is not valid", modelSelection];
            [transport setHttpStatusCode:400];
            [transport writeFormat:@"<p>MELTS WS: Error in specification of model calibration: %@</p>", error];
            if (self.debug) NSLog(@"... ERROR. Error in specification of model calibration. Return status 400.");
            return self;
        }
        if (self.debug) NSLog(@"... Phase list request successful.");
    } else {
        [transport writeData:[[rMELTSframework phaseListAsXMLDocument:@"MELTS_v1.0.x"] XMLData]];
    }
    
    return self;
}

@end
