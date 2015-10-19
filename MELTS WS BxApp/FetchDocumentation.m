//
//  FetchDocumentation.m
//  MELTS
//
//  Created by Mark Ghiorso on 1/16/13.
//  Copyright (c) 2013 Mark Ghiorso. All rights reserved.
//

#import "FetchDocumentation.h"

@implementation FetchDocumentation

- (id)renderWithTransport:(BxTransport *)transport {
    [transport setHttpStatusCode:301];
    [transport setHeader:@"Location" value:@"http://thermofit.ofm-research.org/MELTS_WS"];
    return self;
}


@end
