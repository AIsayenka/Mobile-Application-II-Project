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
    //if([dbconnection createDB])
    //{
        for(int i = 0; i < data.count; i++)
        {
            NSDictionary* statement = [data objectAtIndex:i];
            Statement* _s = [Statement new];
            for(NSString *key in [statement allKeys]){
                if([key isEqualToString:@"id"]){
                    _s._id = [statement objectForKey:key];
                }else if ([key isEqualToString:@"authority"]){
                    _s.actor = [[statement objectForKey:@"authority"] objectForKey:@"name"];
                }else if ([key isEqualToString:@"verb"]){
                    _s.verb = [[[statement objectForKey:@"verb"] objectForKey:@"display"] objectForKey:@"en-US"];
                }else if ([key isEqualToString:@"object"]){
                    _s.object = [[[[statement objectForKey:@"object"] objectForKey:@"definition"] objectForKey:@"description"] objectForKey:@"en-US"];
                }else if ([key isEqualToString:@"location"]){
                    _s.longitude = [[statement objectForKey:@"location"] objectForKey:@"longitude"];
                    _s.latitude = [[statement objectForKey:@"location"] objectForKey:@"latitude"];
                }
            }

            CLLocationCoordinate2D position = { [_s.latitude doubleValue], [_s.longitude doubleValue] };
            GMSMarker *marker = [GMSMarker markerWithPosition:position];
            marker.title = [NSString stringWithFormat:@"Actor: %@\nStatement ID: %@", _s.actor, _s._id];
            marker.appearAnimation = YES;
            marker.flat = YES;
            marker.snippet = @"";
            marker.map = self._mapsView;
        
        }
    //}
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end