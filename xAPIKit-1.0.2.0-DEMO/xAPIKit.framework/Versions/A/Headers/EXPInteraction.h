//
//  EXPInteraction.h
//  EXPAPI
//
//  Copyright (c) 2013 Float Mobile Learning. All rights reserved.
//  http://floatlearning.com/
//
//  Project assistance from Rustici Software.
//  http://scorm.com/
//

#import "EXPActivity.h"
#import "EXPInteractionDefinition.h"

/**
 Interaction object
 */
@interface EXPInteraction : EXPActivity

@property (nonatomic, strong) EXPInteractionDefinition *definition;

@end
