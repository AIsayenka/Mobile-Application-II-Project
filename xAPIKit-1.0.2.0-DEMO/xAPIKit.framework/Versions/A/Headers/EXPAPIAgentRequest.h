//
//  EXPAPIAgentRequest.h
//  xAPI SDK
//
//  Copyright (c) 2013 Float Mobile Learning. All rights reserved.
//  http://floatlearning.com/
//
//  Project assistance from Rustici Software.
//  http://scorm.com/
//

#import <xAPIKit/EXPAPIRequest.h>

@class EXPAgent, EXPPerson;

@protocol EXPAPIAgentRequestDelegate <EXPAPIRequestDelegate>
@optional
/**
 Invoked when a Person object is received from the LRS.
 @param person  The Person received from the API.
 @since         0.95
 */
- (void) personRetrieved:(EXPPerson *)person;
/**
 Invoked when a Person object is received from the LRS.
 Uses the objects at the first index to create an agent from the Person.
 
 @deprecated Use personRetrieved: instead.
 */
- (void) actorRetrieved:(EXPAgent *)actor DEPRECATED_ATTRIBUTE;
@end

@interface EXPAPIAgentRequest : EXPAPIRequest

@property (nonatomic, weak) id<EXPAPIAgentRequestDelegate> delegate;

/**
 Retrieves everything the LRS knows about an actor that has identifying propeties that match the supplied actor.
 @param actor   The actor to find on the LRS.
 @deprecated    Use retrieveExpandedAgentWithAgent instead.
 */
- (void) retrieveActorWithPartialActor:(EXPAgent *)actor DEPRECATED_ATTRIBUTE;

/**
 Retrieves everything the LRS knows about an actor that has identifying propeties that match the supplied actor.
 @param agent   The person to find on the LRS.
 @since         0.95
 */
- (void) retrieveExpandedAgentWithAgent:(EXPAgent *)agent;

@end
