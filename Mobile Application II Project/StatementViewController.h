//
//  StatementViewController.h
//  Mobile Application II Project
//
//  Created by Kirill Aliaev on 2015-04-09.
//  Copyright (c) 2015 TeamPros. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MapKit/MapKit.h>


@interface StatementViewController : UIViewController<UITextViewDelegate>

@property (strong, nonatomic) NSString *desc;
@property(weak, nonatomic) IBOutlet MKMapView *mapview;
@property (weak, nonatomic) IBOutlet UILabel *lblName;
@property (weak, nonatomic) IBOutlet UILabel *lblVerb;
@property (weak, nonatomic) IBOutlet UILabel *lblLocation;

@end
