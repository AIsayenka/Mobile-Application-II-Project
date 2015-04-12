//
//  EXPStatementObject.h
//  xAPI SDK
//
//  Copyright (c) 2013 Float Mobile Learning. All rights reserved.
//  http://floatlearning.com/
//
//  Project assistance from Rustici Software.
//  http://scorm.com/
//

#import <xAPIKit/EXPObject.h>

/**
 Parent class for objects that are eligible to be the object property on a statement.
 */
@interface EXPStatementObject : EXPObject

/**
 The object type of the object (e.g. StatementRef).
 */
@property (nonatomic, strong) NSString *objectType;

@end
