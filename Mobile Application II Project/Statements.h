//
//  Statements.h
//  Mobile Application II Project
//
//  Created by Kirill Aliaev on 2015-04-05.
//  Copyright (c) 2015 COMP3097. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Statement.h"

@interface Statements : NSObject

@property (strong, nonatomic)NSMutableArray* stm;

-(void)setStm:(NSMutableArray *)st;
-(NSMutableArray*)getStm;

@end
