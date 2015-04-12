//
//  EXPAPIRequest.h
//  xAPI SDK
//
//  Copyright (c) 2013 Float Mobile Learning. All rights reserved.
//  http://floatlearning.com/
//
//  Project assistance from Rustici Software.
//  http://scorm.com/
//

#import <Foundation/Foundation.h>

@protocol EXPAPIRequestDelegate, EXPAPIStatementRequestDelegate, EXPAPIAuthenticationProvider;
@class EXPStatementsResult;

typedef enum
{
    EXPAPIRequestTypeGET,
    EXPAPIRequestTypePOST,
    EXPAPIRequestTypePUT,
    EXPAPIRequestTypeOPTIONS,
    EXPAPIRequestTypeDELETE
}EXPAPIRequestType;

extern NSString* const kIfMatch;
extern NSString* const kIfNoneMatch;

/**
 A request was sent to the server and the application is waiting for a response. Not posted if the request is sent synchronously.
 */
extern NSString* const EXPRequestStartedNotification;
/**
 A response was received back from the server and was successfully parsed.
 */
extern NSString* const EXPRequestFinishedNotification;
/**
 A problem was encountered while handling the response from the server--
 either one was never received or what was received was confusing.
 */
extern NSString* const EXPRequestFailedNotification;
/**
 The request was cancelled before receiving a response from the server.
 */
extern NSString* const EXPRequestCanceledNotification;

/**
 The arguments sent to the server were invalid.
 */
extern NSString* const EXPRequestInvalidArgumentError;
/**
 The server rejected the credentials that the library sent.
 */
extern NSString* const EXPRequestUnauthorizedError;
/**
 The requested resource was not found.
 */
extern NSString* const EXPRequestNotFoundError;
/**
 The request timed out before getting a response from the server.
 */
extern NSString* const EXPRequestTimedOutError;
/**
 The request encountered a conflict (e.g. an actor profile with the same actor id already existed).
 */
extern NSString* const EXPRequestConflictError;
/**
 The request encountered a conflict (e.g. an actor profile with the same actor id already existed).
 */
extern NSString* const EXPRequestPreconditionFailedError;
/**
 A server error occurred.
 */
extern NSString* const EXPRequestServerError;

/**
 A wrapper for NSURLConnection to easily make requests to a server.
 */
@interface EXPAPIRequest : NSObject <NSURLConnectionDelegate, NSURLConnectionDataDelegate>
{
    @private
    NSMutableData *responseData;
    NSHTTPURLResponse *response;
    NSURLConnection *conn;
    NSMutableURLRequest *request;
    NSDate *requestStarted;
    NSDate *requestFinished;
    NSTimeInterval timeToCompleteRequest;
    BOOL didFail;
    NSTimer *timeoutTimer;
}

/**
 The object responsible for authorizing the request (e.g. EXPBasicHTTPAuthentication).
 Must implement the EXPAPIAuthenticationProvider protocol.
 */
@property (nonatomic, assign) id<EXPAPIAuthenticationProvider> authorizationProvider;

/**
 The object to receive delegate events from the request.
 */
@property (nonatomic, assign) id<EXPAPIRequestDelegate> delegate;

/**
 The X-Experience-API-Version header of the request (default=0.95).
 @since 0.95
 */
@property (nonatomic, strong) NSString *experienceAPIVersion;

/**
 The URL the request will be sent to. This can be changed any time before the request is sent.
 */
@property (nonatomic, strong) NSURL *URL;

/**
 The number of seconds to wait before considering a request as timed out (default=120).
 @since 1.0
 */
@property (nonatomic, readwrite) float timeoutInterval;

/**
 The HTTP method to use for the request (default=GET).
 */
@property (nonatomic, readwrite) EXPAPIRequestType HTTPMethod;

/**
 The body of the request.
 */
@property (nonatomic, assign) NSData *HTTPBody;

/**
 Set to YES to send the statement synchronously--default NO.
 When a request is made synchronously, the requestDidStart: delegate method is NOT called,
 however requestShouldStart, request:didFailWithError:, and requestDidFinish: will all be called on the delegate.
 */
@property (nonatomic, readwrite) BOOL synchronous;

/**
 Set to YES to consider an error received from the server (e.g. a 4xx or 5xx error)
 as a failed request. If the status code is in the 400s or 500s, the request:didFailWithError:
 delegate will be called even though the request was made successfully (default is YES).
 */
@property (nonatomic, readwrite) BOOL serverErrorsAreFailures;

/**
 By default, the error message that is received from the server is returned as the error.
 You may overwrite these messages with nicer error messages. (default=NO)
 */
@property (nonatomic, readwrite) BOOL niceErrorMessages;

/**
 An extra property for implementations to attach an identifying value.
 */
@property (nonatomic, readwrite) NSInteger tag;

/**
 YES if the request failed due to a time out.
 */
@property (nonatomic, readonly) BOOL didTimeOut;

/**
 YES if the request has been sent and is waiting for a response from the server.
 */
@property (nonatomic, readonly) BOOL isActive;

/**
 Initializes a EXPAPIRequest with a URL, authentication provider, and a delegate.
 This does not start the request--a call to start: must come too.
 
 @param aURL            The URL for the request.
 @param aAuthProvider   The object that authenticates the request before being sent to the API.
 @param aDelegate       The delegate for the request.
 @return                The initialized request (not yet started).
 */
- (id) initWithURL:(NSURL *)aURL andAuthorizationProvider:(id<EXPAPIAuthenticationProvider>)aAuthProvider delegate:(id<EXPAPIRequestDelegate>)aDelegate;

/**
 Initializes a EXPAPIRequest with a URL, authentication provider, and a delegate.
 This does not start the request--a call to start: must come too.
 This is the same thing as -initWithURL:andAuthorizationProvider:delegate:. By convention, subclasses of EXPAPIRequest use this initialization method to append their respective endpoints to the URL.
 
 @param aURL            The URL for the request.
 @param aAuthProvider   The object that authenticates the request before being sent to the API.
 @param aDelegate       The delegate for the request.
 @return                The initialized request (not yet started).
 */
- (id) initWithLRS:(NSURL *)aURL andAuthorizationProvider:(id<EXPAPIAuthenticationProvider>)aAuthProvider delegate:(id<EXPAPIRequestDelegate>)aDelegate;

/**
 Sets the value of an HTTP header field.
 
 @param value   The value to set for the header field.
 @param field   The header field to set the value of.
 @remarks    value must not contain a linebreak--if it does, the header field will NOT be set.
 */
- (void) setValue:(NSString *)value forHTTPHeaderField:(NSString *)field;

/**
 Retrieves the value for an HTTP header field.
 
 @param field   The header field to retrieve the value of.
 @return        The value of the specified field or nil if the field didn't exist.
 */
- (NSString *) valueForHTTPHeaderField:(NSString *)field;

/**
 Prepares the request. This includes integrating the authorization information.
 Subclasses that want to add their own headers should override this and must call super in order to integrate authorization.
 */
- (void) prepareRequest;

/**
 Adds authorization credentials to the request (e.g. setting the Authorization header).
 */
- (void) addAuthorizationCredentials;

/**
 Start the request. This method should not be overridden; instead subclasses should override prepareRequest
 to add any custom headers or body to the request.
 This will trigger the requestShouldStart: method just before sending the request and requestDidStart: after it has started.
 
 @return    Itself (for method chaining).
 */
- (id) start;

/**
 Cancel the request. No more delegate methods will be triggered.
 */
- (void) cancel;

/**
 This is called when a request has finished successfully.
 */
- (void) requestDidFinish;

/**
 Mark the request as failed and notify the delegate that the request failed.
 If this is called before the request is sent, then any attempt to send the request will do nothing.
 A new request will have to be created.
 */
- (void) requestDidFailWithError:(NSError *)error;

@end

/**
 Basic request delegate. Notified when the requests is about to start, when it starts, when it finishes, and when it fails.
 */
@protocol EXPAPIRequestDelegate <NSObject>
@optional

/**
 The request is just about to be sent.
 
 @param request The request that is about to be sent.
 @return        YES to allow the request to continue; NO cancel the request.
 */
- (BOOL) requestShouldStart:(EXPAPIRequest *)request;

/**
 The request was just sent to the API.
 
 @param request The request that was sent.
 */
- (void) requestDidStart:(EXPAPIRequest *)request;

/**
 The request made progress.
 
 @param request     The request that made progress.
 @param percentComplete    Percent complete (out of 1).
 */
- (void) request:(EXPAPIRequest *)request didMakeProgress:(float)percentComplete;

/**
 The request completed succesfully (with a 200 status code).
 
 @param request The request that completed.
 */
- (void) requestDidFinish:(EXPAPIRequest *)request;

/**
 The request failed--it may have been malformed, or the server responded with an error.
 
 @param request The request that failed.
 @param error   The error that was encountered while trying to fulfill the request.
 */
- (void) request:(EXPAPIRequest *)request didFailWithError:(NSError *)error;

@end

/**
 Extended delegate methods for statement requests. Notified when statements are received from the LRS, 
 when they are stored on the LRS, or when a failure was encountered while trying to persist statements on the LRS.
 Each of these come before requestDidFinish:
 */
@protocol EXPAPIStatementRequestDelegate <EXPAPIRequestDelegate>
@optional
/**
 Statements were received from the LRS.
 @param result  The statement result containing the retrieved statements an a URI for more results if they exist.
 */
- (void) statementsReceived: (EXPStatementsResult *)result;

/**
 Statements were persisted on the LRS.
 @param statements  The statements that were persisted. The statements will have an ID assigned if they did not have one previously.
 */
- (void) statementsStored: (NSArray *)statements;

/**
 Statements failed to persist to the LRS.
 NOTE: This method is not called on EVERY failure--it is only triggered on permenant failures. Notably, it will NOT be triggered if the request times out.
 @param statements  The statements that failed to persist to the LRS.
 @param error       The error that was encountered.
 */
- (void) statementsFailedToPersist: (NSArray *)statements withError:(NSError *)error;

/**
 There is an inconsistency with how the More link is generated from different LRS's.
 As the creation of the 0.95 library, this inconsistency has yet to be resolved.
 In response, the library is offering a delegate method to allow implementations to customize this.
 If you implement this method, you should return the full URL for where the next request should be made.
 
 @param moreLink    The URL/path received from the last statement result.
 @return            The resolved URL for the next request.
 @since             1.0
 */
- (NSURL *) resolveURLFromMoreLink:(NSString *)moreLink;

@end

/**
 Modifies the request with the required authentication parameters (e.g. the Authorization header).
 */
@protocol EXPAPIAuthenticationProvider <NSObject>
@required
/**
 Authentication providers should modify the request.
 @param request The request to modify;
 */
- (void) configureRequest:(EXPAPIRequest *)request;

@end