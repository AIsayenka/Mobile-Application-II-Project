//
//  GoogleMapsViewController.h
//  Mobile Application II Project
//
//  Created by Aliaksei Isayenka on 2015-04-12.
//  Copyright (c) 2015 COMP3097. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <GoogleMaps/GoogleMaps.h>

@interface GoogleMapsViewController : UIViewController <GMSMapViewDelegate>

@property (weak, nonatomic) IBOutlet GMSMapView *_mapsView;

@end