//
//  rMELTSframeworkTestsXC.m
//  rMELTSframeworkTestsXC
//
//  Created by Mark Ghiorso on 3/23/16.
//  Copyright © 2016 Mark Ghiorso. All rights reserved.
//

#import <XCTest/XCTest.h>
#import "rMELTSframework.h"

static NSString *testLiquidusXML = @"<?xml version=\"1.0\" encoding=\"UTF-8\"?><MELTSinput><initialize><SiO2>51.2391498538724</SiO2><TiO2>0.594955067513126</TiO2><Al2O3>16.2610441207776</Al2O3><Fe2O3>1.23188823876986</Fe2O3><Cr2O3>0</Cr2O3><FeO>6.75429678718295</FeO><MgO>10.6984480038516</MgO><CaO>9.58801773823569</CaO><Na2O>2.22105947959088</Na2O><K2O>0.416398915333547</K2O><P2O5>0</P2O5><H2O>0.994741794872305</H2O></initialize><calculationMode>findLiquidus</calculationMode><title>Magma_OCT10H_000033</title><constraints><setTP><initialT>1500</initialT><initialP>1000</initialP><finalP>1000</finalP><incP>0.00</incP><dpdt>0.00</dpdt><fo2Path>none</fo2Path></setTP></constraints><fractionationMode>fractionateNone</fractionationMode></MELTSinput>";

static NSString *testWetLiquidusXMLunsat = @"<?xml version=\"1.0\" encoding=\"UTF-8\"?><MELTSinput><initialize><SiO2>51.2391498538724</SiO2><TiO2>0.594955067513126</TiO2><Al2O3>16.2610441207776</Al2O3><Fe2O3>1.23188823876986</Fe2O3><Cr2O3>0</Cr2O3><FeO>6.75429678718295</FeO><MgO>10.6984480038516</MgO><CaO>9.58801773823569</CaO><Na2O>2.22105947959088</Na2O><K2O>0.416398915333547</K2O><P2O5>0</P2O5><H2O>0.994741794872305</H2O></initialize><calculationMode>findWetLiquidus</calculationMode><title>Magma_OCT10H_000033</title><constraints><setTP><initialT>1500</initialT><initialP>1000</initialP><finalP>1000</finalP><incP>0.00</incP><dpdt>0.00</dpdt><fo2Path>none</fo2Path></setTP></constraints><fractionationMode>fractionateNone</fractionationMode></MELTSinput>";

static NSString *testWetLiquidusXMLsat = @"<?xml version=\"1.0\" encoding=\"UTF-8\"?><MELTSinput><initialize><SiO2>77.8</SiO2><TiO2>0.09</TiO2><Al2O3>12.0</Al2O3><Fe2O3>0.196</Fe2O3><Cr2O3>0</Cr2O3><FeO>0.474</FeO><MgO>0.04</MgO><CaO>0.45</CaO><Na2O>3.7</Na2O><K2O>5.36</K2O><P2O5>0</P2O5><H2O>6.0</H2O></initialize><calculationMode>findWetLiquidus</calculationMode><title>LateBishopTuff</title><constraints><setTP><initialT>800</initialT><initialP>2000</initialP><finalP>2000</finalP><incP>0.00</incP><dpdt>0.00</dpdt><fo2Path>none</fo2Path></setTP></constraints><fractionationMode>fractionateNone</fractionationMode></MELTSinput>";

@interface rMELTSframeworkTestsXC : XCTestCase

@end

@implementation rMELTSframeworkTestsXC

- (void)setUp {
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testExample {
    // This is an example of a functional test case.
    // Use XCTAssert and related functions to verify your tests produce the correct results.
}

- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
    }];
}

- (void)testLiquidusExample {
    NSXMLDocument *testDoc = [[NSXMLDocument alloc] initWithXMLString:testLiquidusXML options:NSXMLNodeOptionsNone error:nil];
    rMELTSframework *melts = [[rMELTSframework alloc] init];
    NSUInteger calculationMode = [melts parseAndLoadDataStructuresFromXMLDocument:testDoc];
    if ([melts performMELTScalculation:calculationMode]) NSLog(@"Sucess");
    else NSLog(@"Failure");
}

- (void)testWetLiquidusUnsatExample {
    NSXMLDocument *testDoc = [[NSXMLDocument alloc] initWithXMLString:testWetLiquidusXMLunsat options:NSXMLNodeOptionsNone error:nil];
    rMELTSframework *melts = [[rMELTSframework alloc] init];
    NSUInteger calculationMode = [melts parseAndLoadDataStructuresFromXMLDocument:testDoc];
    if ([melts performMELTScalculation:calculationMode]) NSLog(@"Sucess");
    else NSLog(@"Failure");
}

- (void)testWetLiquidusSatExample {
    NSXMLDocument *testDoc = [[NSXMLDocument alloc] initWithXMLString:testWetLiquidusXMLsat options:NSXMLNodeOptionsNone error:nil];
    rMELTSframework *melts = [[rMELTSframework alloc] init];
    NSUInteger calculationMode = [melts parseAndLoadDataStructuresFromXMLDocument:testDoc];
    if ([melts performMELTScalculation:calculationMode]) NSLog(@"Sucess");
    else NSLog(@"Failure");
}

@end
