//
//  StatementViewController.m
//  Mobile Application II Project
//
//  Created by Kirill Aliaev on 2015-04-09.
//  Copyright (c) 2015 TeamPros. All rights reserved.
//

#import "StatementViewController.h"
#define METERS_PER_MILE 1609.344

@interface StatementViewController ()

@end

@implementation StatementViewController

- (void)viewDidLoad {
    [super viewDidLoad];
//    // Do any additional setup after loading the view.
    UITextView *myUITextView = [[UITextView alloc] init];
    myUITextView.delegate = self;
//    myUITextView.text = self.desc;
//    [self setView:myUITextView];
    [myUITextView setText:_desc];
    myUITextView.textColor = [UIColor blueColor];
    myUITextView.backgroundColor = [UIColor lightGrayColor];
}

- (void)viewWillAppear:(BOOL)animated {
    // 1
    CLLocationCoordinate2D zoomLocation;
    zoomLocation.latitude = 39.281516;
    zoomLocation.longitude= -76.580806;
    
    // 2
    MKCoordinateRegion viewRegion = MKCoordinateRegionMakeWithDistance(zoomLocation, 0.5*METERS_PER_MILE, 0.5*METERS_PER_MILE);
    
    // 3
    [_mapview setRegion:viewRegion animated:YES];
}
/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
