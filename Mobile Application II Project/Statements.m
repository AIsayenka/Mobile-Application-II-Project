//
//  Statements.m
//  Mobile Application II Project
//
//  Created by Kirill Aliaev on 2015-04-05.
//  Copyright (c) 2015 COMP3097. All rights reserved.
//

#import "Statements.h"

@implementation Statements

-(id)init{
    self = [super init];
    if(self){
        _statements = nil;
    }
    return self;
}

-(void)setStatements:(NSMutableArray *)statements{
    _statements = statements;
}
-(NSMutableArray*)getStatements{
    return _statements;
}
@end
