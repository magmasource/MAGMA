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

+(NSXMLDocument *)oxideListAsXMLDocument;
+(NSXMLDocument *)phaseListAsXMLDocument;

-(NSUInteger)parseAndLoadDataStructuresFromXMLDocument:(NSXMLDocument *) inputXMLDocument;
-(NSXMLDocument *)writeDataStructuresToXMLDocument:(NSString *)sessionID;
-(Boolean)performMELTScalculation:(NSUInteger)type;

-(double)initialTemperature;
-(void)setInitialTemperature:(double)tValue;

-(double)finalTemperature;
-(void)setFinalTemperature:(double)tValue;

-(double)incrementTemperature;
-(void)setIncrementTemperature:(double)tValue;

-(double)initialPressure;
-(void)setInitialPressure:(double)tValue;

-(double)finalPressure;
-(void)setFinalPressure:(double)tValue;

-(double)incrementPressure;
-(void)setIncrementPressure:(double)tValue;

-(double)initialVolume;
-(void)setInitialVolume:(double)tValue;

-(double)finalVolume;
-(void)setFinalVolume:(double)tValue;

-(double)incrementVolume;
-(void)setIncrementVolume:(double)tValue;

-(double)initialEnthalpy;
-(void)setInitialEnthalpy:(double)tValue;

-(double)finalEnthalpy;
-(void)setFinalEnthalpy:(double)tValue;

-(double)incrementEnthalpy;
-(void)setIncrementEnthalpy:(double)tValue;

-(double)initialEntropy;
-(void)setInitialEntropy:(double)tValue;

-(double)finalEntropy;
-(void)setFinalEntropy:(double)tValue;

-(double)incrementEntropy;
-(void)setIncrementEntropy:(double)tValue;

-(Boolean)isIsochoric;
-(Boolean)isIsenthalpic;
-(Boolean)isIsotropic;
@end
