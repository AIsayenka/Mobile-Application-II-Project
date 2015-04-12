//
//  DownloadAndDisplayStatements.h
//  Mobile Application II Project
//
//  Created by Kirill Aliaev on 2015-04-05.
//  Copyright (c) 2015 COMP3097. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <xAPIKit/xAPIKit.h>
#import "DisplayStatements.h"

@interface DownloadAndDisplayStatements : DisplayStatements<EXPAPIStatementRequestDelegate>

-(void)downloadAndLoadJSON;

@end
