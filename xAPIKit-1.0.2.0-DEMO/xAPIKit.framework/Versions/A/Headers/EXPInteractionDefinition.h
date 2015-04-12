//
//  EXPInteractionDefinition.h
//  EXPAPI
//
//  Copyright (c) 2013 Float Mobile Learning. All rights reserved.
//  http://floatlearning.com/
//
//  Project assistance from Rustici Software.
//  http://scorm.com/
//

#import "EXPActivityDefinition.h"

/**
 Interaction definition
 */
@interface EXPInteractionDefinition : EXPActivityDefinition

@property (nonatomic, strong) NSArray *correctResponsesPattern;
@property (nonatomic, strong) NSArray *choices;
@property (nonatomic, strong) NSArray *scale;
@property (nonatomic, strong) NSArray *source;
@property (nonatomic, strong) NSArray *target;
@property (nonatomic, strong) NSArray *steps;

@end
