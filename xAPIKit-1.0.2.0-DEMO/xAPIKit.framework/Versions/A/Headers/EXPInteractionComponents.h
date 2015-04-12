//
//  EXPInteractionComponents.h
//  EXPAPI
//
//  Copyright (c) 2013 Float Mobile Learning. All rights reserved.
//  http://floatlearning.com/
//
//  Project assistance from Rustici Software.
//  http://scorm.com/
//

#import <Foundation/Foundation.h>

@class EXPLanguageMap;

/**
 Interaction components.
 */
@interface EXPInteractionComponents : NSObject

@property (nonatomic, strong) NSString *componentId;
@property (nonatomic, strong, getter=getDescription) EXPLanguageMap *desc;

@end
