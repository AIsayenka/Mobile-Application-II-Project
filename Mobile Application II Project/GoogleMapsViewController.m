//
//  GoogleMapsViewController.m
//  Mobile Application II Project
//
//  Created by Aliaksei Isayenka on 2015-04-12.
//  Copyright (c) 2015 COMP3097. All rights reserved.
//

#import "GoogleMapsViewController.h"
#import <GoogleMaps/GMSMapLayer.h>



@implementation GoogleMapsViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    GMSCameraPosition *camera = [GMSCameraPosition cameraWithLatitude:-33.868
                                                            longitude:151.2086
                                                                 zoom:6];
    
    NSLog(self.view.description);
    NSLog(camera.description);
    self._mapsView = [GMSMapView mapWithFrame:CGRectZero camera:camera];
    
    /*GMSMarker *marker = [[GMSMarker alloc] init];
    marker.position = camera.target;
    marker.snippet = @"Hello World";
    marker.appearAnimation = kGMSMarkerAnimationPop;
    marker.map = mapView;*/
    
    //self.view = mapView;
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end