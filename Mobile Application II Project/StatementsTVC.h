//
//  StatementsTVC.h
//  Mobile Application II Project
//
//  Created by Kirill Aliaev on 2015-04-09.
//  Copyright (c) 2015 COMP3097. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Statements.h"

@interface StatementsTVC :  UITableViewController<UITableViewDelegate, UITableViewDataSource>
@property (strong, nonatomic)NSArray *list;
@property (strong, nonatomic)NSArray *statement;
@end
