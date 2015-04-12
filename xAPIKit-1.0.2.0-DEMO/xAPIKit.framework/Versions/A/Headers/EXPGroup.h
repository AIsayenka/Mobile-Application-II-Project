//
//  EXPGroup.h
//  EXPAPI
//
//  Copyright (c) 2013 Float Mobile Learning. All rights reserved.
//  http://floatlearning.com/
//
//  Project assistance from Rustici Software.
//  http://scorm.com/
//

#import <xAPIKit/EXPAgent.h>

/**
 Group object
 */
@interface EXPGroup : EXPAgent

/**
 (array of) Agent objects representing members of this group.
 */
@property (nonatomic, strong) NSMutableArray *members;

@end
