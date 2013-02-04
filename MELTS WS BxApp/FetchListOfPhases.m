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
    
    [transport writeData:[[rMELTSframework phaseListAsXMLDocument] XMLData]];
    
    return self;
}

@end
