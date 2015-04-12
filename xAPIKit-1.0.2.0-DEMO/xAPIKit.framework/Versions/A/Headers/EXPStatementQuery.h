//
//  EXPStatementQuery.h
//  EXPAPI
//
//  Copyright (c) 2013 Float Mobile Learning. All rights reserved.
//  http://floatlearning.com/
//
//  Project assistance from Rustici Software.
//  http://scorm.com/
//

#import <Foundation/Foundation.h>

extern NSString* const kStatementId;
extern NSString* const kVoidedStatementId;
extern NSString* const kAgent;
extern NSString* const kVerb;
extern NSString* const kActivity;
extern NSString* const kRegistration;
extern NSString* const kRelatedActivities;
extern NSString* const kRelatedAgents;
extern NSString* const kSince;
extern NSString* const kUntil;
extern NSString* const kLimit;
extern NSString* const kFormat;
extern NSString* const kAttachments;
extern NSString* const kAscending;

#import <xAPIKit/EXPStatement.h>

typedef enum
{
    EXPStatementQueryFormatExact,
    EXPStatementQueryFormatIds,
    EXPStatementQueryFormatCanonical
}EXPStatementQueryFormat;

@class EXPStatementObject, EXPAgent;

/**
 Provides parameters to specifiy when querying the LRS for statements.
 */
@interface EXPStatementQuery : NSObject

/**
 ID of statement to fetch.
 */
@property (nonatomic, strong) NSString *statementId;

/**
 ID of voided statement to fetch.
 */
@property (nonatomic, strong) NSString *voidedStatementId;

/**
 Filter, only return statements for which the specified agent or group is the actor or object of the statement.
 
 * Agents or identified groups are equal when the same Inverse Functional Identifier is used in each object compared and those Inverse Functional Identifiers have equal values.
 * For the purposes of this filter, groups that have members which match the specified agent based on their Inverse Functional Identifier as described above are considered a match
 @since 1.0
 */
@property (nonatomic, strong) EXPAgent *agent;

/**
 Filter, only return statements matching the specified verb id.
 */
@property (nonatomic, strong) NSString *verb;

/**
 Filter, only return statements for which the object of the statement is an activity with the specified id.
 @since 1.0
 */
@property (nonatomic, strong) NSString *activity;

/**
 Filter, only return statements matching the specified registration ID. Note that although frequently a unique registration ID will be used for one actor assigned to one activity, this should not be assumed. If only statements for a certain actor or activity should be returned, those parameters should also be specified.
 */
@property (nonatomic, strong) NSString *registration;

/**
 Apply the activity filter broadly. Include statements for which the object, any of the context activities, or any of those properties in a contained SubStatement match the activity parameter, instead of that parameter's normal behavior. Matching is defined in the same way it is for the 'activity' parameter."
 default = false
 @since 1.0
 */
@property (nonatomic, readwrite) BOOL relatedActivities;

/**
 Apply the agent filter broadly. Include statements for which the actor, object, authority, instructor, team, or any of these properties in a contained SubStatement match the agent parameter, instead of that parameter's normal behavior. Matching is defined in the same way it is for the 'agent' parameter.
 default = false
 @since 1.0
 */
@property (nonatomic, readwrite) BOOL relatedAgents;

/**
 Only statements stored since the specified timestamp (exclusive) are returned.
 */
@property (nonatomic, strong) NSDate *since;

/**
 Only statements stored at or before the specified timestamp are returned.
 */
@property (nonatomic, strong) NSDate *until;

/**
 Maximum number of statements to return. 0 indicates return the maximum the server will allow.
 default = 0
 */
@property (nonatomic, readwrite) NSInteger limit;

/**
 If "ids", only include minimum information necessary in agent and activity objects to identify them, If "exact", return agent and activity objects populated exactly as they were when the statement was received.
 
 If "canonical", return activity objects populated with the canonical definition of the activity objects as determined by the LRS, after applying the language filtering process defined below, and return the original agent objects as in "exact" mode. Activity objects contain Language Map objects for name and description. Only one language should be returned in each of these maps.
 
 In order to provide these strings in the most relevant language, the LRS will apply the Accept-Language header as described in  RFC 2616 (HTTP 1.1), except that this logic will be applied to each language map individually to select which language entry to include, rather than to the resource (list of statements) as a whole. An LRS requesting statements for the purpose of importing them SHOULD use a format of "exact".
 
 default = EXPStatementQueryFormatExact
 @since 1.0
 */
@property (nonatomic, readwrite) EXPStatementQueryFormat format;

/**
 If true LRS MUST use the multipart response format and include any attachments as described in 4.1.11. Attachments, otherwise the LRS MUST NOT include attachments.
 default = false
 @since 1.0
 */
@property (nonatomic, readwrite) BOOL attachments;

/**
 If true, return results in ascending order of stored time.
 default = false;
 */
@property (nonatomic, readwrite) BOOL ascending;

/**
 Retrieves the EXPStatementQuery parameters as an NSDictionary.
 */
- (NSDictionary *) dictionary;

/**
 Initializes a statement query by setting the statementId property to the specified value.
 
 @param statementId          The ID of the statement to fetch.
 */
- (id) initWithStatementId:(NSString *)statementId;

/**
 Creates a statement query with the specified statement ID.
 
 @param statementId          The ID of the statement to fetch.
 */
+ (EXPStatementQuery *) statementQueryWithStatementId:(NSString *)statementId;

/**
 Creates a statement query with the specified voided statement ID.
 
 @param voidedStatementId    The ID of the VOIDED statement to fetch.
 */
+ (EXPStatementQuery *) statementQueryWithVoidedStatementId:(NSString *)voidedStatementId;

/**
 Creates a statement query with the specified limit.
 
 @param limit                The number of statements to return.
 */
+ (EXPStatementQuery *) statementQueryWithLimit:(NSInteger)limit;

@end

/**
 @deprecated These properties are no longer supported by the xAPI specification.
 */
@interface EXPStatementQuery (Deprecated);

/**
 @deprecated Use agent instead.
 */
@property (nonatomic, strong) EXPAgent *actor DEPRECATED_ATTRIBUTE;

/**
 @deprecated If attempting to filter by activity, use the activity property. If attempting to filter by an agent (as an object), use the agent property. If the passed object is a EXPActivity, the activity property will be set with the ID. If the passed object is a EXPAgent, the agent property will be set with the agent data. Otherwise, this will throw an exception.
 */
@property (nonatomic, strong) EXPStatementObject *object DEPRECATED_ATTRIBUTE;

/**
 @deprecated This property is no longer supported. There is no replacement. Setting this value will have no effect.
 */
@property (nonatomic, readwrite) BOOL context DEPRECATED_ATTRIBUTE;

/**
 @deprecated This property is no longer supported. There is no replacement. Setting this value will have no effect.
 */
@property (nonatomic, readwrite) BOOL authoritative DEPRECATED_ATTRIBUTE;

/**
 @deprecated Set format to EXPStatementQueryFormatIds instead. Setting this value to YES will set format to EXPStatementQueryFormatIds automatically.
 */
@property (nonatomic, readwrite) BOOL sparse DEPRECATED_ATTRIBUTE;

/**
 @deprecated This proeprty is no longer supported. There is no replacement. Setting this value will have no effect.
 */
@property (nonatomic, strong) EXPAgent *instructor DEPRECATED_ATTRIBUTE;
@end
