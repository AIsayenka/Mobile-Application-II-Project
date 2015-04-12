//
//  Statement.m
//  Mobile Application II Project
//
//  Created by Kirill Aliaev on 2015-04-05.
//  Copyright (c) 2015 COMP3097. All rights reserved.
//

#import "Statement.h"

@implementation Statement

-(id)init{
    self = [super init];
    if(self){
        _actor = nil;
        _verb = nil;
        _object = nil;
        __id = nil;
        _timestamp = nil;
    }
    return self;
}

@end
