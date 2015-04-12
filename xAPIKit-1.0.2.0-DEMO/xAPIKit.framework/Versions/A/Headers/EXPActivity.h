//
//  EXPActivity.h
//  EXPAPI
//
//  Copyright (c) 2013 Float Mobile Learning. All rights reserved.
//  http://floatlearning.com/
//
//  Project assistance from Rustici Software.
//  http://scorm.com/
//

#import <xAPIKit/EXPStatementObject.h>

@class EXPActivityDefinition;

/**
 A unit of instruction, experience, or performance that is to be tracks.
 */
@interface EXPActivity : EXPStatementObject

/**
 The URL or URI that uniquely identifies the activity.
 The id must always refer to a single unique activity.
 */
@property (nonatomic, strong) NSString *activityId;

/**
 Meta data about the activity.
 */
@property (nonatomic, strong) EXPActivityDefinition *definition;

/**
 Initializes the activity with an id and definition.
 
 @param aActivityId The activity ID.
 @param aDefinition The activity definition.
 */
- (id) initWithId:(NSString *)aActivityId andDefinition:(EXPActivityDefinition *)aDefinition;

/**
 Creates a stub activity with an ID.
 @param activityId  The ID for the activity.
 @return            The activity.
 */
+ (EXPActivity *) activityWithId:(NSString *)activityId;

/**
 Initializes the activity with an id and definition.
 
 @param aActivityId The activity ID.
 @param aDefinition The activity definition.
 */
+ (EXPActivity *) activityWithId:(NSString *)aActivityId andDefinition:(EXPActivityDefinition *)aDefinition;

@end
