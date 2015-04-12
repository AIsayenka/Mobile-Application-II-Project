//
//  DisplayStatements.h
//  Mobile Application II Project
//
//  Created by Kirill Aliaev on 2015-04-05.
//  Copyright (c) 2015 COMP3097. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Statements.h"

@interface DisplayStatements : NSObject

@property(strong, nonatomic) Statement* s;
@property(strong, nonatomic) Statements* stmnts;

-(void)loadJSON;

@end
