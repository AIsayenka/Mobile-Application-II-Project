//
//  EXPAPIActivityStateRequest.h
//  xAPI SDK
//
//  Copyright (c) 2013 Float Mobile Learning. All rights reserved.
//  http://floatlearning.com/
//
//  Project assistance from Rustici Software.
//  http://scorm.com/
//

#import <xAPIKit/EXPAPIRequest.h>

@class EXPActivityState, EXPAgent;

/**
 Activity state request delegate
 */
@protocol EXPAPIActivityStateRequestDelegate <EXPAPIRequestDelegate>

@optional
/**
 Invoked when the activity state was saved succesfully.
 */
- (void) activityStateSaved:(EXPActivityState *)state;
/**
 Invoked when an activity state was retrieved from the server.
 */
- (void) activityStateRetrieved:(EXPActivityState *)state;
/**
 Invoked when an activity state is deleted from the LRS.
 */
- (void) activityStateDeleted:(EXPActivityState *)state;
/**
 Invoked when multiple activities are deleted from the LRS.
 */
- (void) activityStatesDeleted:(NSArray *)activityStateIds;
/**
 Invoked when multiple activity ids are retrieved from the LRS.
 */
- (void) activityStateIdsRetrieved:(NSArray *)activityStateIds;

@end

/**
 Activity state request
 */
@interface EXPAPIActivityStateRequest : EXPAPIRequest

/**
 The object to receive delegate events from the request.
 */
@property (nonatomic, weak) id<EXPAPIActivityStateRequestDelegate> delegate;

/**
 @param state       The activity state to save to the LRS. The activity state must have a stateId, activityId, and actor defined.
 */
- (void) saveActivityState:(EXPActivityState *)state;
/**
 @param state               The activity state to save to the LRS. The activity state must have a stateId, activityId, and actor defined.
 @param shouldOverwrite     Set to YES to tell the server to overwrite any pre-existing activity states, regardless of when they were created.
                            Set to NO to have the request fail if there is the activity state already exists on the server and (may) have been
                            changed since the last time your application downloaded it.
 @param previousState       The most recent activity state your application is aware of. This activity state must have been received from any
                            one of the getActivityState... methods.
 */
- (void) saveActivityState:(EXPActivityState *)state overwriting:(BOOL)shouldOverwrite previousState:(EXPActivityState *)previousState;
/**
 @param activityId      The id of the activity--must not be empty.
 @param actor           The actor object--this must contain atleast one identifying property (e.g. an email address).
 @param stateId         The specific id of the activity state you want to retrieve--must not be empty.
 @param registrationId  Make the search for an activity state more specific by specifying a registration id.
 */
- (void) getActivityStateWithActivityId:(NSString *)activityId actor:(EXPAgent *)actor andStateId:(NSString *)stateId registrationId:(NSString *)registrationId;
/**
 @param activityId      The id of the activity--must not be empty
 @param actor           Only fetch activity states relating to this actor--must contain atleast one identifiying propetty (e.g. an email address).
 @param since           Only fetch activity states created/updated after this date/time.
 @param registrationId  Make the search for an activity state more specific by specifying a registration id.
 */
- (void) getActivityStateIdsWithActivityId:(NSString *)activityId forActor:(EXPAgent *)actor registrationId:(NSString *)registrationId since:(NSDate *)since;
/**
 @param activityId      The id of the activity--must not be empty.
 @param actor           The actor object--this must contain atleast one identifying property (e.g. an email address).
 @param stateId         The specific id of the activity state you want to retrieve--must not be empty.
 @param registrationId  Only delete activity state if the registration id matches.
 */
- (void) deleteActivityStateWithActivityId:(NSString *)activityId actor:(EXPAgent *)actor andStateId:(NSString *)stateId registrationId:(NSString *)registrationId;
/**
 @param activityId      The id of the activity--must not be empty.
 @param actor           The actor object--this must contain atleast one identifying property (e.g. an email address).
 @param registrationId  Only delete activity state if the registration id matches.
 */
- (void) deleteAllActivityStatesWithActivityId:(NSString *)activityId actor:(EXPAgent *)actor registrationId:(NSString *)registrationId;

@end