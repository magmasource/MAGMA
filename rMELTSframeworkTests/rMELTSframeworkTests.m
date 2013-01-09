//
//  rMELTSframeworkTests.m
//  rMELTSframeworkTests
//
//  Created by Mark Ghiorso on 1/7/13.
//  Copyright (c) 2013 Mark Ghiorso. All rights reserved.
//

#import "rMELTSframeworkTests.h"
#import "rMELTSframework.h"

static NSString *testXML = @"<?xml version=\"1.0\" encoding=\"UTF-8\"?><MELTSinput><initialize><SiO2>51.2391498538724</SiO2><TiO2>0.594955067513126</TiO2><Al2O3>16.2610441207776</Al2O3><Fe2O3>1.23188823876986</Fe2O3><Cr2O3>0</Cr2O3><FeO>6.75429678718295</FeO><MgO>10.6984480038516</MgO><CaO>9.58801773823569</CaO><Na2O>2.22105947959088</Na2O><K2O>0.416398915333547</K2O><P2O5>0</P2O5><H2O>0.994741794872305</H2O></initialize><calculationMode>findLiquidus</calculationMode><title>Magma_OCT10H_000033</title><constraints><setTP><initialT>1500</initialT><finalT>-2</finalT><incT>0.2</incT><initialP>1000</initialP><finalP>1000</finalP><incP>0.00</incP><dpdt>0.00</dpdt><fo2Path>none</fo2Path></setTP></constraints><fractionationMode>fractionateNone</fractionationMode></MELTSinput>";

@implementation rMELTSframeworkTests

- (void)setUp
{
    [super setUp];
    
    // Set-up code here.
}

- (void)tearDown
{
    // Tear-down code here.
    
    [super tearDown];
}

- (void)testExample
{
    NSXMLDocument *testDoc = [[NSXMLDocument alloc] initWithXMLString:testXML options:NSXMLNodeOptionsNone error:nil];
    rMELTSframework *melts = [[rMELTSframework alloc] initWithCalculationMode:[rMELTSframework MELTScalculationModeConstant]];
    NSUInteger calculationMode = [melts parseAndLoadDataStructuresFromXMLDocument:testDoc];
    if ([melts performMELTScalculation:calculationMode]) NSLog(@"Sucess");
    else NSLog(@"Failure");
}

@end
