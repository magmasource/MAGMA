//
//  AppDelegate.m
//  MELTS WS BxApp
//
//  Created by Mark Ghiorso on 1/7/13.
//  Copyright (c) 2013 Mark Ghiorso. All rights reserved.
//

#import "AppDelegate.h"

@implementation AppDelegate

- (id)setup {
    // These are for debug mode
    [self setHandler:@"BaseProcessor" forMatch:@"/MELTSWSBxApp/Compute"];
    [self setHandler:@"Test" forMatch:@"/MELTSWSBxApp/Test"];
    // These are for normal mode
    [self setHandler:@"BaseProcessor" forMatch:@"/Compute"];
    [self setHandler:@"Test" forMatch:@"/Test"];
    // This is a default
    [self setDefaultHandler:@"Documentation"];
    return self;
}

@end
