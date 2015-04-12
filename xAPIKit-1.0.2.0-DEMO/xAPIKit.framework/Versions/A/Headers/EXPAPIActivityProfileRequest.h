//
//  EXPAPIActivityProfileRequest.h
//  xAPI SDK
//
//  Copyright (c) 2013 Float Mobile Learning. All rights reserved.
//  http://floatlearning.com/
//
//  Project assistance from Rustici Software.
//  http://scorm.com/
//

#import <xAPIKit/EXPAPIRequest.h>

@class EXPActivityProfile, EXPActivity;

/**
 Activity profile request delegate
 */
@protocol EXPAPIActivityProfileRequestDelegate <EXPAPIRequestDelegate>
@optional
/**
 Invoked when an activity profile is retrieved from the LRS.
 */
- (void) activityProfileRetrieved:(EXPActivityProfile *)profile;
/**
 Invoked when an activity profile is saved to the LRS.
 */
- (void) activityProfileSaved:(EXPActivityProfile *)profile;
/**
 Invoked when an activity profile is deleted from the LRS.
 */
- (void) activityProfileDeleted:(EXPActivityProfile *)profile;
/**
 Invoked when multiple profile ids are retrieved from the LRS for an activity.
 */
- (void) activityProfileIdsRetrieved:(NSArray *)profileIds;
/**
 Invoked when multiple profiles are deleted from the LRS for an activity.
 */
- (void) activityProfilesDeleted;

@end

/**
 Activity profile request
 */
@interface EXPAPIActivityProfileRequest : EXPAPIRequest

/**
 The object to receive delegate events from the request.
 */
@property (nonatomic, weak) id<EXPAPIActivityProfileRequestDelegate> delegate;

/**
 @param activity        The activity--must contain an activity id.
 @param profileId       The specific if of the activity profile you want to retrieve--must not be empty.
 */
- (void) retrieveActivityProfileForActivity:(EXPActivity *)activity andProfileId:(NSString *)profileId;
/**
 @param profile         The activity profile to save to the LRS. The activity profile must have a profileId and activityId defined.
 */
- (void) saveActivityProfile:(EXPActivityProfile *)profile;
/**
 @param profile         The activity profile to save to the LRS. The activity profile must have a profileId and activityId defined.
 @param shouldOverwrite Set to YES to tell the server to overwrite any pre-existing activity profiles, regardless of when they were created.
                        Set to NO to have the request fail if there is the activity profile already exists on the server and (may) have been
                        changed since the last time your application downloaded it.
 @param previousProfile The most recent activity profile your application is aware of. This activity profile must have been received from any
                        one of the getActivityProfile... methods.
 */
- (void) saveActivityProfile:(EXPActivityProfile *)profile overwriting:(BOOL)shouldOverwrite previousProfile:(EXPActivityProfile *)previousProfile;
/**
 @param activity        The activity--must contain an activity id.
 @param profileId       The specific if of the activity profile you want to retrieve--must not be empty.
 */
- (void) deleteActivityProfileForActivity:(EXPActivity *)activity andProfileId:(NSString *)profileId;
/**
 @param activity        The activity--must contain an activity id.
 */
- (void) deleteAllActivityProfilesForActivity:(EXPActivity *)activity;
/**
 @param activity        The activity--must contain an activity id.
 @param since           Only fetch activity profiles created/updated after this date/time.
 */
- (void) retrieveActivityProfileIdsForActivity:(EXPActivity *)activity since:(NSDate *)since;

@end
