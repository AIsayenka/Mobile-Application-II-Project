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
    GMSCameraPosition *camera = [GMSCameraPosition cameraWithLatitude:43.7182412
                                                            longitude:-79.378058
                                                                 zoom:12];
    
    self._mapsView = [GMSMapView mapWithFrame:CGRectZero camera:camera];
    //self._mapsView.myLocationEnabled = YES;
    DBManager* dbconnection = [[DBManager alloc] init];
    [self.view addSubview:self._mapsView];
    NSMutableArray* data = [[NSMutableArray alloc]init];
    data = [dbconnection selectDistinct];
    //if([dbconnection createDB])
    //{
        for(int i = 0; i < data.count; i++)
        {
            

            CLLocationCoordinate2D position = { [data[i][5] doubleValue], [data[i][6] doubleValue] };
            GMSMarker *_marker = [GMSMarker markerWithPosition:position];
            _marker.title = [NSString stringWithFormat:@"Actor: %@\nStatement ID: %@", data[i][2], data[i][1]];
            //marker.appearAnimation = YES;
            //marker.flat = YES;
            _marker.snippet = [NSString stringWithFormat:@"Marker #%i", i];
            _marker.map = self._mapsView;
        
        }
    
    //}
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end