//
//  EXPActorProfile.h
//  EXPAPI
//
//  Copyright (c) 2013 Float Mobile Learning. All rights reserved.
//  http://floatlearning.com/
//
//  Project assistance from Rustici Software.
//  http://scorm.com/
//

#import <xAPIKit/EXPState.h>

@class EXPAgent;

/**
 @deprecated Use EXPAgentProfile instead.
 */
DEPRECATED_ATTRIBUTE
@interface EXPActorProfile : EXPState

@property (nonatomic, strong) EXPAgent *actor;
@property (nonatomic, strong) NSString *profileId;

- (id) initWithActor:(EXPAgent *)actor andProfileId:(NSString *)profileId;
+ (EXPActorProfile *) actorProfileWithActor:(EXPAgent *)actor andProfileId:(NSString *)profileId;

@end
