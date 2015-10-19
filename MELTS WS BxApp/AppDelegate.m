//
//  AppDelegate.m
//  MELTS WS BxApp
//
//  Created by Mark Ghiorso on 1/7/13.
//  Copyright (c) 2013 Mark Ghiorso. All rights reserved.
//

#import "AppDelegate.h"

@implementation AppDelegate

+(void)initialize {
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSDictionary *appDefaults = [NSDictionary dictionaryWithObjectsAndKeys:@0, @"MELTSBxApp.MODEL", nil];
    [defaults registerDefaults:appDefaults];
}

static NSRecursiveLock *_stateLock = nil;

-(id)setup {
    // These are for debug mode
    [self setHandler:@"BaseProcessor" forMatch:@"/MELTSWSBxApp/Compute"];
    [self setHandler:@"Test" forMatch:@"/MELTSWSBxApp/Test"];
    [self setHandler:@"FetchListOfOxides" forMatch:@"/MELTSWSBxApp/Oxides"];
    [self setHandler:@"FetchListOfPhases" forMatch:@"/MELTSWSBxApp/Phases"];
    // These are for normal mode
    [self setHandler:@"BaseProcessor" forMatch:@"/Compute"];
    [self setHandler:@"Test" forMatch:@"/Test"];
    [self setHandler:@"FetchListOfOxides" forMatch:@"/Oxides"];
    [self setHandler:@"FetchListOfPhases" forMatch:@"/Phases"];
    // This is a default
    [self setDefaultHandler:@"FetchDocumentation"];
    return self;
}

-(NSMutableDictionary *)lockState {
    if (!_stateLock) _stateLock = [[NSRecursiveLock alloc] init];
    [_stateLock lock];
    return self.state;
}

-(id)unloackState {
    [_stateLock unlock];
    return self;
}

-(id)launchConfigurator {
    NSApplication *app = [NSApplication sharedApplication];
    NSArray *_configurationWindowTopLevelObjects;
    [[NSBundle mainBundle] loadNibNamed:@"ConfigurationWindow" owner:self topLevelObjects:&_configurationWindowTopLevelObjects];
    
    NSDictionary *infoDict = [[NSBundle mainBundle] infoDictionary];
    NSString *bombaxticVersion = [infoDict objectForKey:@"BxApp Bombaxtic Version"];
    if (bombaxticVersion == nil) {
        bombaxticVersion = @"";
    }
    [self setBomBaxticVersion:bombaxticVersion];
    
    NSString *description = [infoDict objectForKey:@"BxApp Description"];
    if (description == nil) {
        description = @"";
    }
    [self setAppDescription:description];
    
    NSString *version = [infoDict objectForKey:@"CFBundleVersion"];
    [self setAppVersion:version];
    
    [[NSNotificationCenter defaultCenter] addObserver:app
                                             selector:@selector(terminate:)
                                                 name:NSWindowWillCloseNotification
                                               object:_configurationWindow];
    
    [app run];
    return self;
}

//NSString *path = [[NSUserDefaults standardUserDefaults]
//                  objectForKey:@"uploadPath"];

@end
