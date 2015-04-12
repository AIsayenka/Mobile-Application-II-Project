//
//  EXPAPIGetStatementsRequest.h
//  xAPI SDK
//
//  Copyright (c) 2013 Float Mobile Learning. All rights reserved.
//  http://floatlearning.com/
//
//  Project assistance from Rustici Software.
//  http://scorm.com/
//

#import "EXPAPIRequest.h"

@class EXPStatementQuery, EXPStatementsResult;

/**
 Retrieves statements from the LRS using a statement query.
 @todo Should support retrieving statements via POST if needed
 */
@interface EXPAPIGetStatementsRequest : EXPAPIRequest
{
    /**
     Reference to the previous result that this request is continuing.
     Value provided by initWithPreviousResult...
     */
    EXPStatementsResult *previousResult;
}

/**
 The delegate of the request. Redefined from the super class to be a stricter subclass of EXPAPIRequestDelegate.
 */
@property (nonatomic, weak) id<EXPAPIStatementRequestDelegate> delegate;

/**
 The result from the request (nil if no result has returned yet or if the request failed).
 */
@property (nonatomic, readonly) EXPStatementsResult *result;

/**
 Initializes a request to the LRS to retrieve statements that match the provided query.
 
 @param aQuery          The EXPStatementQuery to use to filter the statements from the database.
 @param aURL            The URL to the LRS (not to the endpoint for the API call--the endpoint is automatically appended).
 @param aAuthProvider   The class that provides the authorization instructions for the class.
 @param aDelegate       The delegate for the request.
 @return                Newly initialized EXPAPIRequest to obtain statements.
 */
- (id) initWithQuery:(EXPStatementQuery *)aQuery onLRS:(NSURL *)aURL usingAuthenticationProvider:(id<EXPAPIAuthenticationProvider>)aAuthProvider delegate:(id<EXPAPIStatementRequestDelegate>)aDelegate;

/**
 Initializes a request to the LRS to continue to retrive statements from a previous request.
 The result EXPStatementResult will also contain the statements from the previous result.
 
 @param aResult         The previous EXPStatementResult.
 @param aURL            The URL to the LRS (not to the endpoint for the API call--the endpoint it automatically appended).
 @param aAuthProvider   The class that provides the authorization instructions for the class.
 @param aDelegate       The delegate for the request.
 @return                The initialized EXPAPIRequest to obtain statements.
 */
- (id) initWithPreviousResult:(EXPStatementsResult *)aResult fromLRS:(NSURL *)aURL usingAuthenticationProvider:(id<EXPAPIAuthenticationProvider>)aAuthProvider delegate:(id<EXPAPIStatementRequestDelegate>)aDelegate;
@end
