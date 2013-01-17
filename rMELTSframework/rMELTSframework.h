//
//  rMELTSframework.h
//  rMELTSframework
//
//  Created by Mark Ghiorso on 1/7/13.
//  Copyright (c) 2013 Mark Ghiorso. All rights reserved.
//

#import <Foundation/Foundation.h>

#define PARSE_ERROR             0
#define GENERIC_CALC            1
#define RUN_LIQUIDUS_CALC       2
#define RUN_EQUILIBRATE_CALC    3
#define RETURN_WITHOUT_CALC     4
#define RETURN_DO_FRACTIONATION 5

@interface rMELTSframework : NSObject

@property int nodeIndex;

+(NSUInteger)MELTScalculationModeConstant;
+(NSUInteger)pMELTScalculationModeConstant;
+(NSUInteger)xMELTScalculationModeConstant;

-(NSUInteger)parseAndLoadDataStructuresFromXMLDocument:(NSXMLDocument *) inputXMLDocument;
-(NSXMLDocument *)writeDataStructuresToXMLDocument;
-(Boolean)performMELTScalculation:(NSUInteger)type;

@end
