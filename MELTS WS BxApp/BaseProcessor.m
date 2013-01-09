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

-(id)init {
    if ((self = [super init])) {
        _respondUsingJSON = NO;
        _inputXML = nil;
    }
    return self;
}

-(NSString *)parseAndValidateInputXML:(NSString *)inputXMLString {
    NSError *error = nil;
    [self setInputXML:[[NSXMLDocument alloc] initWithXMLString:testXML options:NSXMLNodeOptionsNone error:&error]];
    if (error) return [error description];
    
    NSXMLNode *noNamespaceSchemaLocation = [NSXMLNode attributeWithName:@"xsi:noNamespaceSchemaLocation" stringValue:@"MELTSinput.xsd"];
    NSXMLElement *rootElement = [[self inputXML] rootElement];
    NSMutableArray *rootAttributes = [[rootElement attributes] mutableCopy];
    [rootAttributes replaceObjectAtIndex:1 withObject:noNamespaceSchemaLocation];
    [rootElement setAttributes:rootAttributes];
    if (![[self inputXML] validateAndReturnError:&error]) return @"The input XML is NOT valid";
    if (error) return [error description];
    
    return nil;
}

-(id)renderWithTransport:(BxTransport *)transport {
    [transport write:@"<p>BaseProcessor Class:(renderWithTransport) Entry...</p>"];
    NSString *error;
    if ((error = [self parseAndValidateInputXML:testXML])) {
        [transport writeFormat:@"<p>...BaseProcessor Class:(renderWithTransport) Error in parse: %@</p>", error];
        return self;
    }
    [transport write:@"<p>...BaseProcessor Class:(renderWithTransport) Document is valid.</p>"];
    
    rMELTSframework *melts = [[rMELTSframework alloc] initWithCalculationMode:[rMELTSframework MELTScalculationModeConstant]];
    NSUInteger calculationMode = [melts parseAndLoadDataStructuresFromXMLDocument:[self inputXML]];
    [transport writeFormat:@"<p>...BaseProcessor Class:(renderWithTransport) Input parsed, MELTS initialized %lu.</p>", calculationMode];
    
    
    if ([melts performMELTScalculation:calculationMode])
         [transport write:@"<p>...BaseProcessor Class:(renderWithTransport) MELTS call - success.</p>"];
    else [transport write:@"<p>...BaseProcessor Class:(renderWithTransport) MELTS call - failure.</p>"];
    
    NSXMLDocument *outputXML = [melts writeDataStructuresToXMLDocument];
    [transport writeFormat:@"<p>...BaseProcessor Class:(renderWithTransport) Output: %@.</p>", [outputXML description]];
    
    // NSDictionary *results = [Papale satFromgH2OgCO2:[transport queryVars] returnMode:respondUsingJSON];
    // [transport writeData:[NSJSONSerialization dataWithJSONObject:results options:0 error:nil]];
    return self;
}

@end
