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
    [self setHandler:@"BaseProcessor" forMatch:@"/MELTSWSBxApp/Equilibrate"];
    [self setDefaultHandler:@"BaseProcessor"];
    return self;
}

@end
