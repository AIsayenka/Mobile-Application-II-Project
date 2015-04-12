//
//  EXPAPIActivityRequest.h
//  xAPI SDK
//
//  Copyright (c) 2013 Float Mobile Learning. All rights reserved.
//  http://floatlearning.com/
//
//  Project assistance from Rustici Software.
//  http://scorm.com/
//

#import <xAPIKit/EXPAPIRequest.h>

@class EXPActivity;

/**
 Activity request delegate
 */
@protocol EXPAPIActivityRequestDelegate <EXPAPIRequestDelegate>
@optional
/**
 Invoked when an activity definition is retrieved from the LRS.
 */
- (void) activityRetrieved:(EXPActivity *)activity;
@end

/**
 Activity request
 */
@interface EXPAPIActivityRequest : EXPAPIRequest

/**
 The object to receive delegate events from the request.
 */
@property (nonatomic, weak) id<EXPAPIActivityRequestDelegate> delegate;

/**
 @param activityId  The id of the activity to retrieve from the LRS.
 */
- (void) retrieveActivityWithActivityId:(NSString *)activityId;

@end
