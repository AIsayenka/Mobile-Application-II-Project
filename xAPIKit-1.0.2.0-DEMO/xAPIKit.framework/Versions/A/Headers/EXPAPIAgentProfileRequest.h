//
//  EXPAPIAgentProfileRequest.h
//  xAPI SDK
//
//  Copyright (c) 2013 Float Mobile Learning. All rights reserved.
//  http://floatlearning.com/
//
//  Project assistance from Rustici Software.
//  http://scorm.com/
//

#import <xAPIKit/EXPAPIRequest.h>

@class EXPActorProfile, EXPAgentProfile, EXPAgent;

/**
 Profile request delegate
 */
@protocol EXPAPIAgentProfileRequestDelegate <EXPAPIRequestDelegate>
@optional
/**
 Invoked when an agent profile is retrieved from the LRS.
 @since         1.0
 */
- (void) agentProfileRetrieved:(EXPAgentProfile *)profile;
/**
 Invoked when an agent profile is saved to the LRS.
 @since         1.0
 */
- (void) agentProfileSaved:(EXPAgentProfile *)profile;
/**
 Invoked when an agent profile is deleted from the LRS.
 @since         1.0
 */
- (void) agentProfileDeleted:(EXPAgentProfile *)profile;
/**
 Invoked when multiple profile ids are retrieved from the LRS.
 @since         1.0
 */
- (void) agentProfileIdsRetrieved:(NSArray *)profileIds;
/**
 Invoked when multiple profiles are deleted for an agent.
 @since         1.0
 */
- (void) agentProfilesDeleted;

//-----DEPRECATED-------
/**
 Invoked when an actor profile is retrieved from the LRS.
 @deprecated    Use agentProfileRetrieved: instead.
 */
- (void) actorProfileRetrieved:(EXPActorProfile *)profile DEPRECATED_ATTRIBUTE;
/**
 Invoked when an actor profile is saved to the LRS.
 @deprecated    Use agentProfileSaved: instead
 */
- (void) actorProfileSaved:(EXPActorProfile *)profile DEPRECATED_ATTRIBUTE;
/**
 Invoked when an actor profile is deleted from the LRS.
 @deprecated    Use agentProfileDeleted: instead.
 */
- (void) actorProfileDeleted:(EXPActorProfile *)profile DEPRECATED_ATTRIBUTE;
/**
 Invoked when multiple profile ids are retrieved from the LRS.
 @deprecated    Use agentProfileIdsRetrieved: instead.
 */
- (void) actorProfileIdsRetrieved:(NSArray *)profileIds DEPRECATED_ATTRIBUTE;
/**
 Invoked when multiple profiles are deleted for an actor.
 @deprecated    Use agentProfilesDeleted instead.
 */
- (void) actorProfilesDeleted DEPRECATED_ATTRIBUTE;

@end

/**
 Profile request
 */
@interface EXPAPIAgentProfileRequest : EXPAPIRequest

/**
 The object to receive delegate events from the request.
 */
@property (nonatomic, weak) id<EXPAPIAgentProfileRequestDelegate> delegate;

/**
 @param agent           The agent object--this must contain atleast one identifying property (e.g. an email address).
 @param profileId       The specific if of the agent profile you want to retrieve--must not be empty.
 @since                 1.0.
 */
- (void) retrieveAgentProfileForAgent:(EXPAgent *)agent andProfileId:(NSString *)profileId;
/**
 @param profile         The agent profile to save to the LRS. The agent profile must have a profileId and agent defined.
 @since                 1.0.
 */
- (void) saveAgentProfile:(EXPAgentProfile *)profile;
/**
 @param profile         The agent profile to save to the LRS. The agent profile must have a profileId and agent defined.
 @param shouldOverwrite Set to YES to tell the server to overwrite any pre-existing agent profiles, regardless of when they were created.
 Set to NO to have the request fail if there is the agent profile already exists on the server and (may) have been
 changed since the last time your application downloaded it.
 @param previousProfile The most recent agent profile your application is aware of. This agent profile must have been received from any
 one of the getAgentProfile... methods.
 @since                 1.0.
 */
- (void) saveAgentProfile:(EXPAgentProfile *)profile overwriting:(BOOL)shouldOverwrite previousProfile:(EXPAgentProfile *)previousProfile;
/**
 @param agent           The agent object--this must contain atleast one identifying property (e.g. an email address).
 @param profileId       The specific if of the agent profile you want to retrieve--must not be empty.
 @since                 1.0.
 */
- (void) deleteAgentProfileForAgent:(EXPAgent *)agent andProfileId:(NSString *)profileId;
/**
 @param agent           The agent object--this must contain atleast one identifying property (e.g. an email address).
 @since                 1.0.
 */
- (void) deleteAllAgentProfilesForAgent:(EXPAgent *)agent;
/**
 @param agent           The agent object--this must contain atleast one identifying property (e.g. an email address).
 @param since           Only fetch agent profiles created/updated after this date/time.
 @since                 1.0.
 */
- (void) retrieveAgentProfileIdsForAgent:(EXPAgent *)agent since:(NSDate *)since;

@end

@interface EXPAPIAgentProfileRequest (Deprecated)
/**
 @param actor           The actor object--this must contain atleast one identifying property (e.g. an email address).
 @param profileId       The specific if of the actor profile you want to retrieve--must not be empty.
 @deprecated            Use retrieveAgentProfileForAgent:andProfileId: instead.
 */
- (void) retrieveActorProfileForActor:(EXPAgent *)actor andProfileId:(NSString *)profileId DEPRECATED_ATTRIBUTE;
/**
 @param profile         The actor profile to save to the LRS. The actor profile must have a profileId and actor defined.
 @deprecated            Use saveAgentProfile: instead.
 */
- (void) saveActorProfile:(EXPActorProfile *)profile DEPRECATED_ATTRIBUTE;
/**
 @param profile         The actor profile to save to the LRS. The actor profile must have a profileId and actor defined.
 @param shouldOverwrite Set to YES to tell the server to overwrite any pre-existing actor profiles, regardless of when they were created.
 Set to NO to have the request fail if there is the actor profile already exists on the server and (may) have been
 changed since the last time your application downloaded it.
 @param previousProfile The most recent actor profile your application is aware of. This actor profile must have been received from any
 one of the getActorProfile... methods.
 @deprecated            Use saveAgentProfile:overwriting:previousProfile: instead
 */
- (void) saveActorProfile:(EXPActorProfile *)profile overwriting:(BOOL)shouldOverwrite previousProfile:(EXPActorProfile *)previousProfile DEPRECATED_ATTRIBUTE;
/**
 @param actor           The actor object--this must contain atleast one identifying property (e.g. an email address).
 @param profileId       The specific if of the actor profile you want to retrieve--must not be empty.
 @deprecated            Use deleteAgentProfileForAgent:andProfileId: instead
 */
- (void) deleteActorProfileForActor:(EXPAgent *)actor andProfileId:(NSString *)profileId DEPRECATED_ATTRIBUTE;
/**
 @param actor           The actor object--this must contain atleast one identifying property (e.g. an email address).
 @deprecated            Use deleteAllAgentProfilesForAgent: instead.
 */
- (void) deleteAllActorProfilesForActor:(EXPAgent *)actor DEPRECATED_ATTRIBUTE;
/**
 @param actor           The actor object--this must contain atleast one identifying property (e.g. an email address).
 @param since           Only fetch actor profiles created/updated after this date/time.
 @deprecated            Use retrieveAgentProfileIdsForAgent:since: instead.
 */
- (void) retrieveActorProfileIdsForActor:(EXPAgent *)actor since:(NSDate *)since DEPRECATED_ATTRIBUTE;
@end
