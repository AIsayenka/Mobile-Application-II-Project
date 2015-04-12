//
//  EXPAgentProfile.h
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
 Part of the Document API
 @since 1.0
 */
@interface EXPAgentProfile : EXPState

@property (nonatomic, strong) EXPAgent *agent;
@property (nonatomic, strong) NSString *profileId;

- (id) initWithAgent:(EXPAgent *)agent andProfileId:(NSString *)profileId;
+ (EXPAgentProfile *) agentProfileWithAgent:(EXPAgent *)agent andProfileId:(NSString *)profileId;

@end
