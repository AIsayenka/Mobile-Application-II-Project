//
//  GoogleMapsViewController.h
//  Mobile Application II Project
//
//  Created by Aliaksei Isayenka on 2015-04-08.
//  Copyright (c) 2015 COMP3097. All rights reserved.
//

#import <GoogleMaps/GMSMapView.h>
#import <GoogleMaps/GoogleMaps.h>
#import <UIKit/UIKit.h>

@interface GoogleMapsViewController : UIViewController //<GMSMapViewDelegate>


@property (strong, nonatomic) IBOutlet GMSMapView *mapView;


@end
