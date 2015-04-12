//
//  DownloadAndDisplayStatements.m
//  Mobile Application II Project
//
//  Created by Kirill Aliaev on 2015-04-05.
//  Copyright (c) 2015 COMP3097. All rights reserved.
//

#import "DownloadAndDisplayStatements.h"

@implementation DisplayStatements(DownloadAndDisplayStatements)

-(void)downloadAndLoadJSON{
}

-(void) statementsReceived:(EXPStatementsResult *)result{
    NSLog(@"%d statements received.", result.numberOfStatements);
    NSLog(@"Statements: %@", result.statements);
}

@end
