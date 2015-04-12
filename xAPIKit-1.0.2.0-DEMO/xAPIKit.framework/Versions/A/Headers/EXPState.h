//
//  EXPState.h
//  EXPAPI
//
//  Copyright (c) 2013 Float Mobile Learning. All rights reserved.
//  http://floatlearning.com/
//
//  Project assistance from Rustici Software.
//  http://scorm.com/
//

#import <xAPIKit/EXPObject.h>

/**
 State object
 */
@interface EXPState : EXPObject

/**
 Required. The stateId serves as the key for whatever is stored on the LRS.
 This must be set before sending to the LRS.
 */
@property (nonatomic, strong) NSString *stateId;
@property (nonatomic, strong) NSData *contents;
@property (nonatomic, strong) NSDate *updated;
@property (nonatomic, strong) NSString *contentType;

// Convenient ways to set string/dictionary
@property (nonatomic, strong) NSString *stringContents;
@property (nonatomic, strong) NSDictionary *dictionaryContents;

- (id) initWithStateId:(NSString *)stateId;

@end
