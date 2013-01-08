//
//  BaseProcessor.m
//  MELTS
//
//  Created by Mark Ghiorso on 1/7/13.
//  Copyright (c) 2013 Mark Ghiorso. All rights reserved.
//

#import "BaseProcessor.h"

static NSString *testXML = @"<?xml version=\"1.0\" encoding=\"UTF-8\"?><MELTSinput><initialize><SiO2>51.2391498538724</SiO2><TiO2>0.594955067513126</TiO2><Al2O3>16.2610441207776</Al2O3><Fe2O3>1.23188823876986</Fe2O3><Cr2O3>0</Cr2O3><FeO>6.75429678718295</FeO><MgO>10.6984480038516</MgO><CaO>9.58801773823569</CaO><Na2O>2.22105947959088</Na2O><K2O>0.416398915333547</K2O><P2O5>0</P2O5><H2O>0.994741794872305</H2O></initialize><calculationMode>findLiquidus</calculationMode><title>Magma_OCT10H_000033</title><constraints><setTP><initialT>1500</initialT><finalT>-2</finalT><incT>0.2</incT><initialP>1000</initialP><finalP>1000</finalP><incP>0.00</incP><dpdt>0.00</dpdt><fo2Path>none</fo2Path></setTP></constraints><fractionationMode>fractionateNone</fractionationMode></MELTSinput>";

@implementation BaseProcessor

@synthesize respondUsingJSON;

-(id)init {
    if ((self = [super init])) {
        respondUsingJSON = YES;
    }
    return self;
}

-(id)renderWithTransport:(BxTransport *)transport {
    [transport write:@"<h2>renderWithTransport method of BaseProcessor called.</h2>"];
    
    NSError *error = nil;
    NSXMLDocument *inputXML = [[NSXMLDocument alloc] initWithXMLString:testXML options:NSXMLNodeOptionsNone error:&error];
    if (error) [transport write:[@"Parse call, error = %@" stringByAppendingString:[error description]]];
    
    NSXMLNode *noNamespaceSchemaLocation = [NSXMLNode attributeWithName:@"xsi:noNamespaceSchemaLocation" stringValue:@"MELTSinput.xsd"];
    NSXMLElement *rootElement = [inputXML rootElement];
    NSMutableArray *rootAttributes = [[rootElement attributes] mutableCopy];
    [rootAttributes replaceObjectAtIndex:1 withObject:noNamespaceSchemaLocation];
    [rootElement setAttributes:rootAttributes];
    BOOL isValid = [inputXML validateAndReturnError:&error];
    if (error) [transport write:[@"Parse call, error = %@" stringByAppendingString:[error description]]];
    if (isValid) {
        [transport write:@"<h2>The input XML is valid</h2>"];
    } else {
        [transport write:@"<h2>The input XML is NOT valid</h2>"];
    }
    
    // NSDictionary *results = [Papale satFromgH2OgCO2:[transport queryVars] returnMode:respondUsingJSON];
    // [transport writeData:[NSJSONSerialization dataWithJSONObject:results options:0 error:nil]];
    return self;
}

@end
