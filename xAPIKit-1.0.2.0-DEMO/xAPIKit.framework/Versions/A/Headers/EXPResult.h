//
//  EXPResult.h
//  EXPAPI
//
//  Copyright (c) 2013 Float Mobile Learning. All rights reserved.
//  http://floatlearning.com/
//
//  Project assistance from Rustici Software.
//  http://scorm.com/
//

#import <xAPIKit/EXPObject.h>

typedef enum
{
    EXPResultSuccessStatusNotSpecified,
    EXPResultSuccessStatusFailed,
    EXPResultSuccessStatusSucceeded,
} EXPResultSuccessStatus;

typedef enum
{
    EXPResultCompletionStatusNotSpecified,
    EXPResultCompletionStatusCompleted,
} EXPResultCompletionStatus;

@class EXPScore;

/**
 Result object
 */
@interface EXPResult : EXPObject

/**
 The score object.
 */
@property (nonatomic, strong) EXPScore *score;
/**
 Whether the result represents a success or a failure. It can also be unspecified (EXPResultSuccessStatusNotSpecified).
 */
@property (nonatomic, readwrite) EXPResultSuccessStatus success;
/**
 Whether the result represents a completion or not. It can be unspecified (EXPResultCompletionStatusNotSpecified).
 */
@property (nonatomic, readwrite) EXPResultCompletionStatus completion;
/**
 A response appropriately formatted for the given activity.
 Only valid for an interaction activity. In the case of an activity of type “cmi.interaction”, this field is formatted according
 to the “cmi.interactions.n.learner_response” element defined in the SCORM 2004 4th edition Runtime Environment.
 */
@property (nonatomic, strong) NSString *response;
/**
 Period of time overwhich the statement occurred. In seconds.
 */
@property (nonatomic, readwrite) NSTimeInterval duration;
/**
 A map of other properties as needed.
 */
@property (nonatomic, strong) NSDictionary *extensions;

/**
 Initializes a result object with a score and completion/success status.
 
 @param score
 @param completion
 @param success
 */
- (id) initWithScore:(EXPScore *)score completion:(EXPResultCompletionStatus)completion success:(EXPResultSuccessStatus)success;

/**
 Initializes a result object with a score and completion/success status.
 
 @param score
 @param completion
 @param success
 */
+ (EXPResult *) resultWithScore:(EXPScore *)score completion:(EXPResultCompletionStatus)completion success:(EXPResultSuccessStatus)success;

/**
 Initializes a result with a score.
 Success and completion are set to not specified.
 */
+ (EXPResult *) resultWithScore:(EXPScore *)score;
/**
 Initializes a result with a raw score. Value stored in raw property of score object.
 Success and completion are set to not specified.
 */
+ (EXPResult *) resultWithRawScore:(NSNumber *)rawScore;

@end
