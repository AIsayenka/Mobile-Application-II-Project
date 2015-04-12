//
//  EXPActivityProfile.h
//  EXPAPI
//
//  Copyright (c) 2013 Float Mobile Learning. All rights reserved.
//  http://floatlearning.com/
//
//  Project assistance from Rustici Software.
//  http://scorm.com/
//

#import <xAPIKit/EXPState.h>

@class EXPActivity;

/**
 Activity profile
 */
@interface EXPActivityProfile : EXPState

/**
 The activity id.
 */
@property (nonatomic, strong) NSString *activityId;
/**
 The profile id.
 */
@property (nonatomic, strong) NSString *profileId; //Just a map to stateId

- (id) initWithActivityId:(NSString *)activityId andProfileId:(NSString *)profileId;
+ (EXPActivityProfile *) activityProfileForActivity:(EXPActivity *)activity;
+ (EXPActivityProfile *) activityProfileForActivity:(EXPActivity *)activity andProfileId:(NSString *)profileId;
+ (EXPActivityProfile *) activityProfileForActivityId:(NSString *)activityId andProfileId:(NSString *)profileId;

@end
