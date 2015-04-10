//
//  StatementViewController.m
//  Mobile Application II Project
//
//  Created by Kirill Aliaev on 2015-04-09.
//  Copyright (c) 2015 TeamPros. All rights reserved.
//

#import "StatementViewController.h"
#define METERS_PER_MILE 1609.344
#import "DBManager.h"

@interface StatementViewController ()

@end

@implementation StatementViewController

DBManager *dbm;

NSArray *temp;

- (void)viewDidLoad {
    [super viewDidLoad];
    if (self.desc) {
        temp = [[NSArray alloc] init];
        dbm = [DBManager new];
        temp = [dbm findById:_desc];
        
        NSString *lStr = [NSString stringWithFormat:@"%f %f", [[temp objectAtIndex:4] floatValue], [[temp objectAtIndex:5] floatValue]];
        _lblName.text = [temp objectAtIndex:0];
        _lblVerb.text = [temp objectAtIndex:1];
        _lblLocation.text = lStr;
        
        CLLocationCoordinate2D centerCoordinate = CLLocationCoordinate2DMake([[temp objectAtIndex:4] floatValue], [[temp objectAtIndex:5] floatValue]);
        MKPointAnnotation *annotation = [[MKPointAnnotation alloc] init];
        [annotation setCoordinate:centerCoordinate];
        [annotation setTitle:lStr]; //You can set the subtitle too
        [self.mapview addAnnotation:annotation];
    }
   
}

- (void)viewWillAppear:(BOOL)animated {
    // 1
    CLLocationCoordinate2D zoomLocation;
//    zoomLocation.latitude = 39.281516;
//    zoomLocation.longitude= -76.580806;
    zoomLocation.latitude = [[temp objectAtIndex:4] doubleValue];
    zoomLocation.longitude= [[temp objectAtIndex:5] doubleValue];
    
    // 2
    MKCoordinateRegion viewRegion = MKCoordinateRegionMakeWithDistance(zoomLocation, 2000*METERS_PER_MILE, 2000*METERS_PER_MILE);
    
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
