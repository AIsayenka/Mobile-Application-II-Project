//
//  GoogleMapsViewController.m
//  Mobile Application II Project
//
//  Created by Aliaksei Isayenka on 2015-04-08.
//  Copyright (c) 2015 COMP3097. All rights reserved.
//

#import "GoogleMapsViewController.h"

@implementation GoogleMapsViewController

- (void)viewDidLoad {
    
    [super viewDidLoad];
    GMSCameraPosition *camera = [GMSCameraPosition cameraWithLatitude:-33.86
                                                            longitude:151.20
                                                                 zoom:6];
    self.mapView = [GMSMapView mapWithFrame:CGRectZero camera:camera];
    self.mapView.myLocationEnabled = YES;
    self.view = self.mapView;
    
    // Creates a marker in the center of the map.
    /*GMSMarker *marker = [[GMSMarker alloc] init];
    marker.position = CLLocationCoordinate2DMake(-33.86, 151.20);
    marker.title = @"Sydney";
    marker.snippet = @"Australia";
    marker.map = self.mapView;*/
    
    //Controls whether the My Location dot and accuracy circle is enabled.
    /*@try {
        self.mapView.myLocationEnabled = NO;
    
        //Controls the type of map tiles that should be displayed.
    
        self.mapView.mapType = kGMSTypeNormal;
    
        //Shows the compass button on the map
    
        self.mapView.settings.compassButton = YES;
    
        //Shows the my location button on the map
    
        self.mapView.settings.myLocationButton = YES;
        
        //Sets the view controller to be the GMSMapView delegate
    
        self.mapView.delegate = self;
    } @catch (NSException *e)
    {
        NSLog(@"%@", e.reason);
    }*/
    NSLog(@"It kinda works");
    
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end