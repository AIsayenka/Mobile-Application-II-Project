//
//  EXPAPIStoreStatementsRequest.h
//  xAPI SDK
//
//  Copyright (c) 2013 Float Mobile Learning. All rights reserved.
//  http://floatlearning.com/
//
//  Project assistance from Rustici Software.
//  http://scorm.com/
//

#import "EXPAPIRequest.h"

@class EXPStatement;

/**
 Used to POST statements or PUT a statement on the LRS.
 Triggers statementsStored: and statementsFailed:withError:--they get called after requestDidFinish: and request:didFailWithError: respectively.
 */
@interface EXPAPIStoreStatementsRequest : EXPAPIRequest

/**
 The delegate of the request. Redefined from the super class to be a stricter subclass of EXPAPIRequestDelegate.
 */
@property (nonatomic, weak) id<EXPAPIStatementRequestDelegate>delegate;

/**
 The statement(s) to send to the LRS.
 */
@property (nonatomic, copy) NSArray *statements;

/**
 Creates a PUT request for sending a single statement to the LRS.
 
 @param aStatement      The statement to persist on the LRS (doesn't need to contain a statement ID).
 @param aId             The statement ID to assign to the statement (must NOT be empty).
 @param aURL            The LRS url (do NOT include the endpoint for statements--it is automatically appended).
 @param aAuthProvider   The authorization provider for the request.
 @param aDelegate       The delegate for the request.
 @return                An initialized request (not yet started).
 */
- (id) initWithStatement:(EXPStatement *)aStatement andStatementId:(NSString *)aId toPUTOnLRS:(NSURL *)aURL usingAuthenticationProvider:(id<EXPAPIAuthenticationProvider>)aAuthProvider delegate:(id<EXPAPIStatementRequestDelegate>)aDelegate;

/**
 Creates a POST request for sending multiple statements to the LRS.
 
 @param aStatements     The statements to persist on the LRS (statements do not have to have a Statement ID).
 @param aURL            The LRS url (do NOT include the endpoint for statements--it is automatically appended).
 @param aAuthProvider   The authorization provider for the request.
 @param aDelegate       The delegate for the request.
 @return                An initialized request (not yet started).
 */
- (id) initWithStatements:(NSArray *)aStatements toPOSTOnLRS:(NSURL *)aURL usingAuthenticationProvider:(id<EXPAPIAuthenticationProvider>)aAuthProvider delegate:(id<EXPAPIStatementRequestDelegate>)aDelegate;

@end
