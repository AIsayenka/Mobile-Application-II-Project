//
//  Statement.h
//  Mobile Application II Project
//
//  Created by Kirill Aliaev on 2015-04-05.
//  Copyright (c) 2015 COMP3097. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Statement : NSObject
@property (strong, nonatomic) NSString* actor;
@property (strong, nonatomic) NSString* verb;
@property (strong, nonatomic) NSString* object;
@property (strong, nonatomic) NSString* _id;
@property (strong, nonatomic) NSString* timestamp;
@property (strong, nonatomic) NSString* longitude;
@property (strong, nonatomic) NSString* latitude;


@end
