//
//  EXPContext.h
//  EXPAPI
//
//  Copyright (c) 2013 Float Mobile Learning. All rights reserved.
//  http://floatlearning.com/
//
//  Project assistance from Rustici Software.
//  http://scorm.com/
//

#import <xAPIKit/EXPObject.h>

@class EXPAgent, EXPStatement, EXPContextActivities;

/**
 An optional field that provides a place to add contextual information to a Statement. All properties are optional.
 
 The "context" field provides a place to add some contextual information to a Statement. It can store information such as the instructor for an experience, if this experience happened as part of a team Activity, or how an experience fits into some broader activity.
 */
@interface EXPContext : EXPObject

/**
 UUID of the registration statement is associated with.
 */
@property (nonatomic, strong) NSString *registration;
/**
 Instructor that the statement relates to, if not included as the actor or object of the statement.
 */
@property (nonatomic, strong) EXPAgent *instructor;
/**
 Team that this statement relates to, if not included as the actor or object of the statement.
 */
@property (nonatomic, strong) EXPAgent *team;
/**
 A map of the types of learning activity context that this statement is related to. Valid context types are: "parent", "grouping", "category" and "other".
 */
@property (nonatomic, strong, readonly) EXPContextActivities *contextActivities;
/**
 Revision of the learning activity associated with this statement.
 Revisions are to track fixes of minor issues (like a spelling error), if there is any substantive change to the learning objectives, pedagogy, or assets associated with an activity, a new activity ID should be used.
 Revision format is up to the owner of the associated activity. Not applicable if statement's object is a Person.
 */
@property (nonatomic, strong) id revision;
/**
 Platform used in the experience of this learning activity. Not applicable if statement's object is a Person. Defined vocabulary, TBD.
 */
@property (nonatomic, strong) NSString *platform;
/**
 Code representing the language in which the experience being recorded in this statement (mainly) occurred in, if applicable and known. Do not specify any value if not applicable or not known.
 Format for this value is as defined in RFC3066.
 For example, US English would be recorded as: en-US
 */
@property (nonatomic, strong) NSString *language;
/**
 Another statement (either existing or new), which should be considered as context for this statement. This could be used to add context to a comment, or when grading.
 */
@property (nonatomic, strong) EXPStatement *statement;
/**
 A map of any other domain-specific context relevant to this statement. For example, in a flight simulator altitude, airspeed, wind, attitude, GPS coordinates might all be relevant.
 */
@property (nonatomic, strong) NSMutableDictionary *extensions;

/**
 Returns an autoreleased blank context object.
 */
+ (EXPContext *) context;

@end
