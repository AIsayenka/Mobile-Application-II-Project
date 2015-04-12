//
//  EXPActivityCollection.h
//  xAPI SDK
//
//  Copyright (c) 2013 Float Mobile Learning. All rights reserved.
//  http://floatlearning.com/
//
//  Project assistance from Rustici Software.
//  http://scorm.com/
//

#import <xAPIKit/EXPObject.h>

@class EXPActivity;

/**
 Represents a collection of activities. Used for context activities.
 */
@interface EXPActivityCollection : EXPObject

/**
 The activities represented by this collection.
 */
@property (nonatomic, strong, readonly) NSArray *activities;

/**
 The number of activities in the collection.
 */
@property (nonatomic, readonly) NSUInteger count;

/**
 Initializes a collection using the activities specified.
 
 @param activities  The activities to initialize the collection with (can be nil). All objects in activities must be of type EXPActivity.
 */
- (id) initWithArray:(NSArray *)activities;

/**
 Add's an activity to the collection.
 @param activity     The activity to add to a collection.
 @throws NSException    Throws an exception if the activity to add is not a valid activity.
 */
- (void) addActivity:(EXPActivity *)activity;

/**
 Add's an activity to the collection.
 @param activities   The activities to add to a collection.
 @throws NSException    Throws an exception any of the activities to add is not a valid activity.
 */
- (void) addActivities:(NSArray *)activities;

/**
 Removes the specified activity from the collection (if it exists).
 If the activity does not exist, then the collection will not change; no errors will be displayed.
 @param activity     The activity to remove from the collection.
 */
- (void) removeActivity:(EXPActivity *)activity;

/**
 Removes any instances of the specified activities from the collection (if they exist).
 If the activity does not exist, then the collection will not change; no errors will be displayed.
 @param activities     The activity to remove from the collection.
 */
- (void) removeActivities:(NSArray *)activities;

/**
 Removes all the activities in the collection.
 */
- (void) removeAllActivities;

@end
