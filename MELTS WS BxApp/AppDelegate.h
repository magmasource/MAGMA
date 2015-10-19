//
//  AppDelegate.h
//  MELTS WS BxApp
//
//  Created by Mark Ghiorso on 1/7/13.
//  Copyright (c) 2013 Mark Ghiorso. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <Bombaxtic/Bombaxtic.h>

@interface AppDelegate : BxApp {
    IBOutlet NSWindow *_configurationWindow;
}

@property NSString *bomBaxticVersion;
@property NSString *appVersion;
@property NSString *appDescription;

-(NSMutableDictionary *)lockState;
-(id)unloackState;

@end
