//
//  BaseProcessor.h
//  MELTS
//
//  Created by Mark Ghiorso on 1/7/13.
//  Copyright (c) 2013 Mark Ghiorso. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Bombaxtic/Bombaxtic.h>
#import <rMELTSframework/rMELTSframework.h>

@interface BaseProcessor : BxHandler {
}

@property BOOL respondUsingJSON;
@property NSXMLDocument *inputXML;
@property Boolean debug;

@end
