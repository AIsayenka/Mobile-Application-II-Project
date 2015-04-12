//
//  EXPContextActivities.h
//  xAPI SDK
//
//  Copyright (c) 2013 Float Mobile Learning. All rights reserved.
//  http://floatlearning.com/
//
//  Project assistance from Rustici Software.
//  http://scorm.com/
//

#import "EXPObject.h"

@class EXPActivity, EXPActivityCollection;

/**
 Context activities.
 */
@interface EXPContextActivities : EXPObject

/**
 An activity with a direct relation to the activity which is the object of the statement. In almost all cases there is only one sensible parent or none, not multiple. For example: a statement about a quiz question would have the quiz as its parent activity.
 */
@property (nonatomic, strong, readonly) EXPActivityCollection *parent;

/**
 An activity with an indirect relation to the activity which is the object of the statement. For example: a course that is part of a qualification. The course has several classes. The course relates to a class as the parent, the qualification relates to the class as the grouping.
 */
@property (nonatomic, strong, readonly) EXPActivityCollection *grouping;

/**
 An activity used to categorize the statement. "Tags" would be a synonym. Category SHOULD be used to indicate a "profile" of xAPI behaviors, as well as other categorizations. For example: Anna attempts a biology exam, and the statement is tracked using the CMI-5 profile. The statement's activity refers to the exam, and the category is the CMI-5 profile.
 */
@property (nonatomic, strong, readonly) EXPActivityCollection *category;

/**
 A context activity that doesn't fit one of the other fields. For example: Anna studies a textbook for a biology exam. The statement's activity refers to the textbook, and the exam is a context activity of type "other".
 */
@property (nonatomic, strong, readonly) EXPActivityCollection *other;

@end
