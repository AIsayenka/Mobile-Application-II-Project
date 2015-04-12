//
//  ViewController.m
//  Mobile Application II Project
//  Maps tutorial http://www.techotopia.com/index.php/Working_with_Maps_on_iOS_7_with_MapKit_and_the_MKMapView_Class
//  Created by Kirill Aliaev on 2015-03-13.
//  Copyright (c) 2015 COMP3097. All rights reserved.
//

#import "ViewController.h"
#import "Statement.h"
#import "Statements.h"
#import "DisplayStatements.h"
#import "DownloadAndDisplayStatements.h"

@interface ViewController ()

@property (weak, nonatomic) IBOutlet UITextField *textLink;
@property (weak, nonatomic) IBOutlet UITextField *textEmail;
@property (weak, nonatomic) IBOutlet UITextField *textPasswd;
@property (weak, nonatomic) IBOutlet UILabel *staticTitle;
@end

@implementation ViewController

DisplayStatements* ds;
DownloadAndDisplayStatements* dds;
EXPStatementsResult* res;

- (IBAction)btnDisplay:(id)sender {
}
- (IBAction)btnDonloadAndDisplay:(id)sender {
    [[EXPAPI defaultAPI] getStatementsWithQuery:[EXPStatementQuery statementQueryWithLimit:10] delegate:self];
    res = [[EXPStatementsResult alloc] init];
    [self statementsReceived:res];
}
- (IBAction)btnReset:(id)sender {
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    [UIApplication sharedApplication].networkActivityIndicatorVisible = YES;
    _staticTitle.font = [UIFont fontWithName:@"Zapfino" size:21.0f];
    _staticTitle.textAlignment = NSTextAlignmentCenter;
    _textPasswd.secureTextEntry = YES;
    
    ds = [DisplayStatements new];
    [ds loadJSON];
    //[[EXPAPI defaultAPI] getStatementsWithQuery:[EXPStatementQuery statementQueryWithLimit:10] delegate:self];
    [dds statementsReceived:res];
}
- (void) statementsReceived:(EXPStatementsResult *)result
{
    NSLog(@"%d statements received.", result.numberOfStatements);
    NSLog(@"Statements: %@", result.statements);
}
- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
