//
//  ViewController.h
//  Mobile Application II Project
//
//  Created by Kirill Aliaev on 2015-03-13.
//  Copyright (c) 2015 COMP3097. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DisplayStatements.h"
#import "DBManager.h"

@interface ViewController : UIViewController 

@property(strong, nonatomic) Statement* s;
@property(strong, nonatomic) Statements* stmnts;
@end

