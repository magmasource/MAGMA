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

@interface rMELTSframework : NSObject {
    int kSiO2, kTiO2, kAl2O3, kFe2O3, kCr2O3, kFeO, kMnO, kMgO, kNiO, kCoO, kCaO, kNa2O, kK2O, kP2O5, kH2O;
}

+(NSUInteger)MELTScalculationModeConstant;
+(NSUInteger)pMELTScalculationModeConstant;
+(NSUInteger)xMELTScalculationModeConstant;

-(id)initWithCalculationMode:(NSUInteger) mode;
-(NSUInteger)parseAndLoadDataStructuresFromXMLDocument:(NSXMLDocument *) inputXMLDocument;
-(NSXMLDocument *)writeDataStructuresToXMLDocument;
-(Boolean)performMELTScalculation:(NSUInteger)type;

@end
