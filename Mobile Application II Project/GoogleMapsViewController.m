//
//  GoogleMapsViewController.m
//  Mobile Application II Project
//
//  Created by Aliaksei Isayenka on 2015-04-12.
//  Copyright (c) 2015 COMP3097. All rights reserved.
//

#import "GoogleMapsViewController.h"
#import <GoogleMaps/GMSMapLayer.h>
#import "Statement.h"

@implementation GoogleMapsViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    GMSCameraPosition *camera = [GMSCameraPosition cameraWithLatitude:-33.868
                                                            longitude:151.2086
                                                                 zoom:6];
    
    self._mapsView = [GMSMapView mapWithFrame:CGRectZero camera:camera];
    
    DBManager* dbconnection = [[DBManager alloc] init];
    
    NSMutableArray* data = [[NSMutableArray alloc]init];
    data = [dbconnection selectDistinct];
    //NSMutableArray *markersArray = [[NSMutableArray alloc] init];
    for(int i = 0; i < data.count; i++)
    {
        NSDictionary* statement = [data objectAtIndex:i];
        Statement* _s = [Statement new];
        
        CLLocationCoordinate2D position = { [_s.latitude doubleValue], [_s.longitude   doubleValue] };
        GMSMarker *marker = [GMSMarker markerWithPosition:position];
        marker.title = [NSString stringWithFormat:@"Marker %i", i];
        marker.appearAnimation = YES;
        marker.flat = YES;
        marker.snippet = @"";
        marker.map = self._mapsView;
        
    }
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end