//
//  EXPActivityState.h
//  EXPAPI
//
//  Copyright (c) 2013 Float Mobile Learning. All rights reserved.
//  http://floatlearning.com/
//
//  Project assistance from Rustici Software.
//  http://scorm.com/
//

#import <xAPIKit/EXPState.h>

@class EXPAgent, EXPActivity;

/**
 Activity state
 */
@interface EXPActivityState : EXPState

@property (nonatomic, strong) NSString *activityId;
@property (nonatomic, strong) EXPAgent *actor;
@property (nonatomic, strong) NSString *registrationId;

- (id) initWithStateId:(NSString *)stateId activityId:(NSString *)activityId andActor:(EXPAgent *)actor;
+ (EXPActivityState *) stateForActivity:(EXPActivity *)activity forActor:(EXPAgent *)actor; // automatically generates state id
+ (EXPActivityState *) activityStateWithActivityId:(NSString *)activityId andActor:(EXPAgent *)actor;
+ (EXPActivityState *) stateWithId:(NSString *)stateId forActivity:(EXPActivity *)activity forActor:(EXPAgent *)actor;
+ (EXPActivityState *) stateWithId:(NSString *)stateId forActivityId:(NSString *)activityId forActor:(EXPAgent *)actor;

@end
