//
//  EXPAPI.h
//  xAPI SDK
//
//  Copyright (c) 2013 Float Mobile Learning. All rights reserved.
//  http://floatlearning.com/
//
//  Project assistance from Rustici Software.
//  http://scorm.com/
//

#import <Foundation/Foundation.h>
#import <xAPIKit/EXPAPIActivityProfileRequest.h>
#import <xAPIKit/EXPAPIActivityRequest.h>
#import <xAPIKit/EXPAPIActivityStateRequest.h>
#import <xAPIKit/EXPAPIAgentProfileRequest.h>
#import <xAPIKit/EXPAPIAgentRequest.h>
#import <xAPIKit/EXPAPIGetStatementsRequest.h>
#import <xAPIKit/EXPAPIRequest.h>
#import <xAPIKit/EXPAPIStoreStatementsRequest.h>
#import <xAPIKit/EXPAPIQueueDelegate.h>

/**
 Posted to the notification center when a single batch of statements from the queue has successfully persisted to the LRS.
 By default, a batch is a maximum of 50 statements meaning that if more than 50 statements were
 sent to the LRS, this notification could possibly be posted multiple times.
 
 The "statements" key in the userInfo dictionary contains an array of statements that were successfully persisted.
 The notification object is a reference to the EXPAPI instance posting it.
 */
extern NSString* const EXPStatementsPersistedNotification;

/**
 Posted to the notification center when a single batch of statements from the queue failed to persist to the LRS
 for a (potentially) permanent reason. The statements may need modified before being sent again.
 By default, a batch is a maximum of 50 statements meaning that if more than 50 statements were
 sent to the LRS, this notification could possibly be posted multiple times.
 This notification is not posted if the failure is due to a request timing out or an Internet connection
 not being available. In those cases, the statements are left in the queue and retried the next time
 the queue is processed. This notification is psoted when a more serious error with the statements was
 encountered--this includes both client side (invalid information in the statement) and server side
 (the server is down for maintenance).
 
 The "statements" key in the userInfo dictionary contains an array of statements that were successfully persisted.
 The "error" key in the userInfo dictioanry contains an NSError describing the error that was encountered.
 The notification object is a reference to the EXPAPI instance posting it.
 */
extern NSString* const EXPStatementsFailedPersistingNotification;

@class EXPStatement, EXPAPIGetStatementsRequest, EXPAPIStoreStatementsRequest, EXPStatementQuery, EXPStatementQueue, EXPReachability;

/**
 Convenience class for interacting with the xAPI.
 Use the methods provided in this class for storing, retrieving, and voiding statements.
 */
@interface EXPAPI : NSObject <EXPAPIStatementRequestDelegate>
{
    @private
    /**
     EXPAPIRequests that are currently active.
     requestDidStart: adds requests to this container; request:didFailWithError: and requestDidFinish: remove requests from the container.
     */
    NSMutableArray *activeRequests;
    /**
     Handles whether the host is "Reachable" or not.
     */
    EXPReachability *reachability;
    /**
     Requests that are pending to be sent when the statement queue finishes flushing.
     */
    NSMutableArray *pendingRequests;
}

/**
 The base URL to the API. The endpoint for each requested is based off this value.
 */
@property (nonatomic, strong) NSURL *endpoint;

/**
 The object implementing the EXPAPIQueueDelegate protocol that will be invoked when statements
 from the statement queue were either successfully posted to the LRS or failed for some reason.
 
 EXPAPI does not retain ownership of the delegate--only a reference. If the delegate is deallocated
 and EXPAPI attempts to invoke a method, your application will crash.
 It is important that the delegate be present throughout the lifetime of the application, or that the delegate
 be set to nil when the object it references is deallocated.
 */
@property (nonatomic, weak) id<EXPAPIQueueDelegate> delegate;

/**
 The object responsible for authorizing the request (e.g. EXPBasicHTTPAuthentication).
 Must implement the EXPAPIAuthenticationProvider protocol.
 */
@property (nonatomic, strong) id<EXPAPIAuthenticationProvider> authorizationProvider;

/**
 The statement queue used for the EXPAPI implementation.
 */
@property (nonatomic, weak) EXPStatementQueue *statementQueue;

/**
 The number of seconds in between each attempt to persist the current statement queue
 to the LRS. Set to 0 to disable the automatic post interval (call flush:) to manually
 send the statement queue to the API (default=120).
 While the queue is attempting to persist the queue, the statement post interval will not run.
 that additional statements added to the queue may have to wait longer than the statement post interval.
 The post interval will be resumed when the original batch successfully persists.
 */
@property (nonatomic, readwrite) NSTimeInterval statementPostInterval;

/**
 YES if the device appears to have Internet access.
 This only indicates whether the network interface on the device is up. It doesn't actually indicate
 whether the device has a working Internet connection.
 The network interface on the device would be down if the device is in airplane mode 
 or not currently connected to any networks.
 */
@property (nonatomic, readonly) BOOL isOnline;

/**
 YES if the statement post interval is counting down the second until the next invocation.
 This may report NO if statementPostInterval is 0 or statements from the queue are currently
 persisting to the LRS.
 */
@property (nonatomic, readonly) BOOL isStatementPostIntervalActive;

/**
 The maximum number of statements to send to the server in each batch.
 If the queue is attempting to persist a higher number of statements than the batch size,
 the multiple, simultaneous requests will be made. (default=50)
 */
@property (nonatomic, readwrite) NSInteger batchSize;

/**
 Set the default actor for statements sent to the LRS.
 Use this to indicate the currently logged in user.
 */
@property (nonatomic, strong) EXPAgent *defaultActor;


#pragma mark - Statement queue management
/**
 Stores multiple statements in the queue for persisting in the LRS (or local store if the device is offline).
 
 @param statements  An array of statements to add to the default statement queue.
 @param synchronous Set to YES to bypass the statement queue and send the request directly to the LMS. Must be in an online environment.
 */
- (id) storeStatements:(NSArray *)statements synchronously:(BOOL)synchronous;

/**
 Calls storeStatements:synchronously: with the synchonous parameter set to NO.
 */
- (id) storeStatements:(NSArray *)statements;

/**
 Store a single statement in the queue for persisting in the LRS (or local store if the device is offline).
 Wraps the statement in an array and passes the call onto storeStatements:synchronously:.
 
 @param statement   The statement to store in the statement queue.
 @param synchronous Set to YES to bypass the statement queue and send the request directly to the LRS. Must be in an online environment.
 */
- (id) storeStatement:(EXPStatement *)statement synchronously:(BOOL)synchronous;

/**
 Calls storeStatement:synchronously: with the synchronous parameter set to NO.
 */
- (id) storeStatement:(EXPStatement *)statement;

/**
 Voids multiple statements in the LRS.
 This initially puts the information in the statement queue and will be persisted to the LRS eventually.
 It is expected that the LRS will set the actor of these voiding statements to the user that is
 currently logged in. If the LRS does not support user sessions, you may set defaultActor on the EXPAPI instance.
 If you do not specify an actor of the voiding statement, the actor will be sent to the actor of the statement
 that is being voided.
 
 @param statements  An array of statements to void.
 @param synchronous Set to YES to bypass the staement queue and send the request directly to the LRS. Must be in an online environment.
 */
- (void) voidStatements:(NSArray *)statements synchronously:(BOOL)synchronous;

/**
 Calls voidStatements:synchronously with the synchronous property set to NO.
 */
- (void) voidStatements:(NSArray *)statements;

/**
 Attempts to send all the statements in the statement queue to the API.
 If there are more than the maximum number of statements in the queue that
 can be processed in one request, then multiple requests are sent (this will cause
 the delegate method to get triggered more than one time--once for each batch.
 
 @return The number of statements sent to the LRS (to determine how many requests were made, divide this number by self.batchSize and round up).
 */
- (NSUInteger) flushStatementQueue;

/**
 Attempts to send all the statements in the statement queue to the API.
 When the statements have finished persisting to the LRS (or failed persisting)
 then the specified request will be made.
 This is ideal for flushing the statement queue and then immediately requesting statements from the LRS.
 
 @param request The request to start immediately upon finishing flushing the queue.
 */
- (void) startRequestAfterFlushingStatementQueue:(EXPAPIRequest *)request;

#pragma mark - Statement API Methods
/**
 Directly creates an API request to POST statements to the LRS (does not place statements in the statement queue).
 
 @param statements  An array of statements to POST to the LRS. The statements do not have to have an ID assigned--it will get assigned by the LRS.
 @param aDelegate   The delgate to use for the request (by default, it uses the current API instance).
 @return            The instantiated API request.
 */
- (EXPAPIStoreStatementsRequest *) postStatements:(NSArray *)statements delegate:(id<EXPAPIStatementRequestDelegate>)aDelegate;

/**
 Directly creates a synchronous API request to POST statements to the LRS (does not place statements in the statement queue).
 Uses the current API instance as the delegate for the request. This means that the delegate of the current API instance will get notified
 of the events of this request.
 
 @param statements  An array of statements to POST to the LRS. The statements do not have to have an ID assigned--it will get assigned by the LRS.
 @return            The instantiated API request.
 @remarks           This calls postStatements:delegate: with the aDelegate parameter set to nil.
 */
- (EXPAPIStoreStatementsRequest *) postStatementsSynchronously:(NSArray *)statements;

/**
 Directly creates an API request to PUT a single statement on the LRS (does not place the statement in the statement queue).
 
 @param statement   The EXPStatement to send to the LRS.
 @param statementId The statement id to assign the statement (must not be nil).
 @param aDelegate   The delegate to use for the request (by default, it uses the current API instance).
 @return            The instantiated API request.
 */
- (EXPAPIStoreStatementsRequest *) putStatement:(EXPStatement *)statement withStatementId:(NSString *)statementId delegate:(id<EXPAPIStatementRequestDelegate>)aDelegate;

/**
 Directly creates an API request to PUT a single statement on the LRS (does not place the statement in the statement queue).
 Attempts to use the id that is in the supplied statement or generates one if one does not exist.
 
 @param statement   The EXPStatement to send to the LRS.
 @param aDelegate   The delegate to use for the request (by default, it uses the current API instance).
 @return            The instantiated API request.
 @remarks           This calls putStatement:withStatementId:delegate using the supplied parameters and the statement id from the statement property or a generated one.
 */
- (EXPAPIStoreStatementsRequest *) putStatement:(EXPStatement *)statement delegate:(id<EXPAPIStatementRequestDelegate>)aDelegate;

/**
 Attempts to retrieve a single statement from the LRS with the specified id.
 Generates a EXPStatementQuery and passes the call onto getStatementWithQuery:delegate: and passes through it's return.
 
 @param sid         The statement id to attempt to retrieve from the LRS.
 @param aDelegate   The object to set the delegate of the EXPAPIStatementRequest.
 @return            A reference to the API request that was created.
 */
- (EXPAPIGetStatementsRequest *) getStatementWithId:(NSString *)sid delegate:(id<EXPAPIStatementRequestDelegate>)aDelegate;

/**
 Attempts to retreive multiple statements from the LRS using the specified query.
 Automatically creates a EXPAPIStatementRequest using the default API values specified in the default EXPAPI.
 Sets the delegate to the provided delegate--the delegate will be notified when the statement is available (see EXPAPIRequestDelegate).
 
 @param query       The query object to use to query the LRS for learning records.
 @param aDelegate   The object to set the delegate of the EXPAPIStatementRequest.
 @return            A reference to the API request that was created.
 
 @remarks           Passes the call onto getStatementsWithQuery:afterFlushingQueue:delegate: with the shouldFlushQueue parameter set to NO.
 */
- (EXPAPIGetStatementsRequest *) getStatementsWithQuery:(EXPStatementQuery *)query delegate:(id<EXPAPIStatementRequestDelegate>)aDelegate;

/**
 Attempts to retreive multiple statements from the LRS using the specified query.
 Automatically creates a EXPAPIStatementRequest using the default API values specified in the default EXPAPI.
 Sets the delegate to the provided delegate--the delegate will be notified when the statement is available (see EXPAPIRequestDelegate).
 
 @param query               The query object to use to query the LRS for learning records.
 @param shouldFlushQueue    Set to YES to first flush the queue before requesting statements from the LRS. 
                            If statements in the queue match the query but are not persisted to the LRS then the response from 
                            the LRS will NOT include these statements. It will take longer to get back a response since this 
                            has to wait for the statements to finish persisting before creating a request.
 @param aDelegate           The object to set the delegate of the EXPAPIStatementRequest.
 @return                    A reference to the API request that was created.
 */
- (EXPAPIGetStatementsRequest *) getStatementsWithQuery:(EXPStatementQuery *)query afterFlushingQueue:(BOOL)shouldFlushQueue delegate:(id<EXPAPIStatementRequestDelegate>)aDelegate;

/**
 Retrieves statements from the LRS using the more URL specified in a EXPStatementResult.
 
 @param moreURL     The URL to request statements from. This should be the URL received by a previous request.
 @param aDelegate   The delegate to use for the request.
 @return            A reference to the API request that was created.
 */
- (EXPAPIGetStatementsRequest *) getStatementsWithURL:(NSURL *)moreURL delegate:(id<EXPAPIStatementRequestDelegate>)aDelegate;

/**
 Retrieves statements from the LRS. Uses the moreURL parameter from the EXPStatementsResult to retrieve
 the statements and appends the retrieved statements to the EXPStatementsResult and updates the URL
 with the new URL (if there is one, otherwise it is set to nil.
 
 @param result      The EXPStatementsResult to append more statements to.
 @param aDelegate   The delegate for the request.
 @return            A reference to the API request that was created.
 */
- (EXPAPIGetStatementsRequest *) getStatementsWithStatementResult:(EXPStatementsResult *)result withDelegate:(id<EXPAPIStatementRequestDelegate>)aDelegate;

#pragma mark - Activity State API Methods
/**
 Saves an activity state to the LRS overwriting any previously existing state with an identical stateId.
 
 @param state       The activity state to save to the LRS. The activity state must have a stateId, activityId, and actor defined.
 @param aDelegate   The delegate for the request. Must implement the EXPAPIActivityStateRequestDelegate protocol.
 @return            A reference to the API request that was created. If a delegate was defined, then the request was started automatically.
                    If the delegate was nil, then the request was NOT started--your application is responsible for starting the request and
                    retaining a reference to the request so it can handle the response.
 */
- (EXPAPIActivityStateRequest *) saveActivityState:(EXPActivityState *)state withDelegate:(id<EXPAPIActivityStateRequestDelegate>)aDelegate;

/**
 Saves an activity state to the LRS. It evaluates a previous activity state and can overwrite the previous state with the new state.
 
 @param state               The activity state to save to the LRS. The activity state must have a stateId, activityId, and actor defined.
 @param shouldOverwrite     Set to YES to tell the server to overwrite any pre-existing activity states, regardless of when they were created.
                            Set to NO to have the request fail if there is the activity state already exists on the server and (may) have been
                            changed since the last time your application downloaded it.
 @param previousState       The most recent activity state your application is aware of. This activity state must have been received from any
                            one of the getActivityState... methods.
 @param delegate            The delegate for the request. Must implement the EXPAPIActivityStateRequestDelegate protocol.
 @return                    A reference to the API request that was created. If a delegate was defined, then the request was started automatically.
                            If the delegate was nil, then the request was NOT started--your application is responsible for starting the request and
                            retaining a reference to the request so it can handle the response.
 */
- (EXPAPIActivityStateRequest *) saveActivityState:(EXPActivityState *)state overwriting:(BOOL)shouldOverwrite previousState:(EXPActivityState *)previousState delegate:(id<EXPAPIActivityStateRequestDelegate>)delegate;

/**
 Retrieves an activity state from the server matching the activity id, actor, and stateId specified.
 
 @param activityId      The id of the activity--must not be empty.
 @param actor           The actor object--this must contain atleast one identifying property (e.g. an email address).
 @param stateId         The specific id of the activity state you want to retrieve--must not be empty.
 @param aDelegate       The delegate for the request. Must implement the EXPAPIActivityStateRequestDelegate protocol.
 @return                A reference to the API request that was created. If a delegate was defined, then the request was started automatically.
                        If the delegate was nil, then the request was NOT started--your application is responsible for starting the request and
                        retaining a reference to the request so it can handle the response.
 */
- (EXPAPIActivityStateRequest *) getActivityStateWithActivityId:(NSString *)activityId actor:(EXPAgent *)actor andStateId:(NSString *)stateId delegate:(id<EXPAPIActivityStateRequestDelegate>)aDelegate;

/**
 Retrieves an activity state from the server matching the activity id, actor, and stateId specified.
 
 @param activityId      The id of the activity--must not be empty.
 @param actor           The actor object--this must contain atleast one identifying property (e.g. an email address).
 @param stateId         The specific id of the activity state you want to retrieve--must not be empty.
 @param registrationId  Make the search for an activity state more specific by specifying a registration id.
 @param aDelegate       The delegate for the request. Must implement the EXPAPIActivityStateRequestDelegate protocol.
 @return                A reference to the API request that was created. If a delegate was defined, then the request was started automatically.
                        If the delegate was nil, then the request was NOT started--your application is responsible for starting the request and
                        retaining a reference to the request so it can handle the response.
 */
- (EXPAPIActivityStateRequest *) getActivityStateWithActivityId:(NSString *)activityId actor:(EXPAgent *)actor andStateId:(NSString *)stateId registrationId:(NSString *)registrationId delegate:(id<EXPAPIActivityStateRequestDelegate>)aDelegate;

/**
 Retrieves a list of activity state ids for the specified activity belonging to the specified actor. Can optionally be filtered by date to only show the activity states created/updated after a specific point in time.
 
 @param activityId      The id of the activity--must not be empty
 @param actor           Only fetch activity states relating to this actor--must contain atleast one identifiying propetty (e.g. an email address).
 @param since           Only fetch activity states created/updated after this date/time.
 @param aDelegate       The delegate for the request. Must implement the EXPAPIActivityStateRequestDelegate protocol.
 @return                A reference to the API request that was created. If a delegate was defined, then the request was started automatically.
                        If the delegate was nil, then the request was NOT started--your application is responsible for starting the request and
                        retaining a reference to the request so it can handle the response.
 */
- (EXPAPIActivityStateRequest *) getActivityStateIdsWithActivityId:(NSString *)activityId forActor:(EXPAgent *)actor since:(NSDate *)since delegate:(id<EXPAPIActivityStateRequestDelegate>)aDelegate;

/**
 Retrieves a list of activity state ids for the specified activity belonging to the specified actor. Can optionally be filtered by date to only show the activity states created/updated after a specific point in time.
 
 @param activityId      The id of the activity--must not be empty
 @param actor           Only fetch activity states relating to this actor--must contain atleast one identifiying propetty (e.g. an email address).
 @param since           Only fetch activity states created/updated after this date/time.
 @param registrationId  Make the search for an activity state more specific by specifying a registration id.
 @param aDelegate       The delegate for the request. Must implement the EXPAPIActivityStateRequestDelegate protocol.
 @return                A reference to the API request that was created. If a delegate was defined, then the request was started automatically.
                        If the delegate was nil, then the request was NOT started--your application is responsible for starting the request and
                        retaining a reference to the request so it can handle the response.
 */
- (EXPAPIActivityStateRequest *) getActivityStateIdsWithActivityId:(NSString *)activityId forActor:(EXPAgent *)actor registrationId:(NSString *)registrationId since:(NSDate *)since delegate:(id<EXPAPIActivityStateRequestDelegate>)aDelegate;

/**
 Deletes a specific activity state from the LRS matching the specified activity belonging to the specified actor.
 
 @param activityId      The id of the activity--must not be empty.
 @param actor           The actor object--this must contain atleast one identifying property (e.g. an email address).
 @param stateId         The specific id of the activity state you want to retrieve--must not be empty.
 @param aDelegate       The delegate for the request. Must implement the EXPAPIActivityStateRequestDelegate protocol.
 @return                A reference to the API request that was created. If a delegate was defined, then the request was started automatically.
                        If the delegate was nil, then the request was NOT started--your application is responsible for starting the request and
                        retaining a reference to the request so it can handle the response.
 */
- (EXPAPIActivityStateRequest *) deleteActivityStateWithActivityId:(NSString *)activityId actor:(EXPAgent *)actor andStateId:(NSString *)stateId delegate:(id<EXPAPIActivityStateRequestDelegate>)aDelegate;

/**
 Deletes a specific activity state from the LRS matching the specified activity belonging to the specified actor.
 The statement will only be deleted if the registrationId matches.
 
 @param activityId      The id of the activity--must not be empty.
 @param actor           The actor object--this must contain atleast one identifying property (e.g. an email address).
 @param stateId         The specific id of the activity state you want to retrieve--must not be empty.
 @param registrationId  Only delete activity state if the registration id matches.
 @param aDelegate       The delegate for the request. Must implement the EXPAPIActivityStateRequestDelegate protocol.
 @return                A reference to the API request that was created. If a delegate was defined, then the request was started automatically.
                        If the delegate was nil, then the request was NOT started--your application is responsible for starting the request and
                        retaining a reference to the request so it can handle the response.
 */
- (EXPAPIActivityStateRequest *) deleteActivityStateWithActivityId:(NSString *)activityId actor:(EXPAgent *)actor andStateId:(NSString *)stateId registrationId:(NSString *)registrationId delegate:(id<EXPAPIActivityStateRequestDelegate>)aDelegate;

/**
 Deletes all the activity states for an activity belonging to the specified actor.
 
 @param activityId      The id of the activity--must not be empty.
 @param actor           The actor object--this must contain atleast one identifying property (e.g. an email address).
 @param aDelegate       The delegate for the request. Must implement the EXPAPIActivityStateRequestDelegate protocol.
 @return                A reference to the API request that was created. If a delegate was defined, then the request was started automatically.
                        If the delegate was nil, then the request was NOT started--your application is responsible for starting the request and
                        retaining a reference to the request so it can handle the response.
 */
- (EXPAPIActivityStateRequest *) deleteAllActivityStatesWithActivityId:(NSString *)activityId forActor:(EXPAgent *)actor delegate:(id<EXPAPIActivityStateRequestDelegate>)aDelegate;

/**
 Deletes all the activity states for an activity belonging to the specified actor.
 
 @param activityId      The id of the activity--must not be empty.
 @param actor           The actor object--this must contain atleast one identifying property (e.g. an email address).
 @param aDelegate       The delegate for the request. Must implement the EXPAPIActivityStateRequestDelegate protocol.
 @param registrationId  Only delete activity state if the registration id matches.
 @return                A reference to the API request that was created. If a delegate was defined, then the request was started automatically.
                        If the delegate was nil, then the request was NOT started--your application is responsible for starting the request and
                        retaining a reference to the request so it can handle the response.
 */
- (EXPAPIActivityStateRequest *) deleteAllActivityStatesWithActivityId:(NSString *)activityId forActor:(EXPAgent *)actor registrationId:(NSString *)registrationId delegate:(id<EXPAPIActivityStateRequestDelegate>)aDelegate;


#pragma mark - Activity Profile API methods
/**
 Retrieves an activity profile from the LRS for an activity matching a specific profile id.
 
 @param activityId      The id of the activity--must not be empty.
 @param profileId       The specific if of the activity profile you want to retrieve--must not be empty.
 @param delegate        The delegate for the request. Must implement the EXPAPIActivityProfileRequestDelegate.
 @return                A reference to the API request that was created. If a delegate was defined, then the request was started automatically.
                        If the delegate was nil, then the request was NOT started--your application is responsible for starting the request and
                        retaining a reference to the request so it can handle the response.
 */
- (EXPAPIActivityProfileRequest *) getActivityProfileWithActivityId:(NSString *)activityId andProfileId:(NSString *)profileId delegate:(id<EXPAPIActivityProfileRequestDelegate>)delegate;

/**
 Saves an activity profile to the LRS. If the profile id is already used by an activity profile on the server, this will not overwrite. It will trigger a conflict error (409).
 
 @param activityProfile The activity profile to save to the LRS. The activity profile must have a profileId and activityId defined.
 @param delegate        The delegate for the request. Must implement the EXPAPIActivityProfileRequestDelegate.
 @return                A reference to the API request that was created. If a delegate was defined, then the request was started automatically.
                        If the delegate was nil, then the request was NOT started--your application is responsible for starting the request and
                        retaining a reference to the request so it can handle the response.
 */

- (EXPAPIActivityProfileRequest *) saveActivityProfile:(EXPActivityProfile *)activityProfile delegate:(id<EXPAPIActivityProfileRequestDelegate>)delegate; // Overwrite is true
/**
 Saves an activity profile to the LRS. Optionally, you may specifiy that this activity profile overwrite and preexisting activity profiles regardless of when they were created/updated. If you specify a previousProfile, the server will verify that you were working from the most recent version. If the activity profile cannot be updated due to a conflict, an error will be returned.
 
 @param activityProfile The activity profile to save to the LRS. The activity profile must have a profileId and activityId defined.
 @param shouldOverwrite Set to YES to tell the server to overwrite any pre-existing activity profiles, regardless of when they were created.
                        Set to NO to have the request fail if there is the activity profile already exists on the server and (may) have been
                        changed since the last time your application downloaded it.
 @param previousProfile The most recent activity profile your application is aware of. This activity profile must have been received from any
                        one of the getActivityProfile... methods.
 @param delegate        The delegate for the request. Must implement the EXPAPIActivityProfileRequestDelegate.
 @return                A reference to the API request that was created. If a delegate was defined, then the request was started automatically.
                        If the delegate was nil, then the request was NOT started--your application is responsible for starting the request and
                        retaining a reference to the request so it can handle the response.
 */
- (EXPAPIActivityProfileRequest *) saveActivityProfile:(EXPActivityProfile *)activityProfile overwriting:(BOOL)shouldOverwrite previousProfile:(EXPActivityProfile *)previousProfile delegate:(id<EXPAPIActivityProfileRequestDelegate>)delegate; // Overwrite is false
/**
 Deletes an activity profile for a specific activity.
 
 @param activityId      The id of the activity--must not be empty.
 @param profileId       The specific if of the activity profile you want to retrieve--must not be empty.
 @param delegate        The delegate for the request. Must implement the EXPAPIActivityProfileRequestDelegate.
 @return                A reference to the API request that was created. If a delegate was defined, then the request was started automatically.
                        If the delegate was nil, then the request was NOT started--your application is responsible for starting the request and
                        retaining a reference to the request so it can handle the response.
 */
- (EXPAPIActivityProfileRequest *) deleteActivityProfileWithActivityId:(NSString *)activityId andProfileId:(NSString *)profileId delegate:(id<EXPAPIActivityProfileRequestDelegate>)delegate;
/**
 Deletes all activity profiles for a specific activity.
 
 @param activityId      The id of the activity--must not be empty.
 @param delegate        The delegate for the request. Must implement the EXPAPIActivityProfileRequestDelegate.
 @return                A reference to the API request that was created. If a delegate was defined, then the request was started automatically.
                        If the delegate was nil, then the request was NOT started--your application is responsible for starting the request and
                        retaining a reference to the request so it can handle the response.
 */
- (EXPAPIActivityProfileRequest *) deleteAllActivityProfilesWithActivityId:(NSString *)activityId delegate:(id<EXPAPIActivityProfileRequestDelegate>)delegate;
/**
 Retrieves profile ids of all the activity profiles for the specified activity. This list may optionally be filtered by a date and the server will only return profiles that were created/updated after the date.
 
 @param activityId      The id of the activity--must not be empty.
 @param since           Only fetch activity profiles created/updated after this date/time.
 @param delegate        The delegate for the request. Must implement the EXPAPIActivityProfileRequestDelegate.
 @return                A reference to the API request that was created. If a delegate was defined, then the request was started automatically.
                        If the delegate was nil, then the request was NOT started--your application is responsible for starting the request and
                        retaining a reference to the request so it can handle the response.
 */
- (EXPAPIActivityProfileRequest *) getActivityProfileIdsWithActivityId:(NSString *)activityId since:(NSDate *)since delegate:(id<EXPAPIActivityProfileRequestDelegate>)delegate;
/**
 Retrieves an activity definition for the specified activity id.
 
 @param activityId      The id of the activity--must not be empty.
 @param delegate        The delegate for the request. Must implement the EXPAPIActivityRequestDelegate protocol.
 @return                A reference to the API request that was created. If a delegate was defined, then the request was started automatically.
                        If the delegate was nil, then the request was NOT started--your application is responsible for starting the request and
                        retaining a reference to the request so it can handle the response.
 */
- (EXPAPIActivityRequest *) getActivityWithActivityId:(NSString *)activityId delegate:(id<EXPAPIActivityRequestDelegate>)delegate;

#pragma mark - Agent Profile API Methods
/**
 Retrieves an agent profile from the LRS for an agent matching a specific profile id.
 
 @param agent           The agent object--this must contain atleast one identifying property (e.g. an email address).
 @param profileId       The specific if of the agent profile you want to retrieve--must not be empty.
 @param delegate        The delegate for the request. Must implement the EXPAPIAgentProfileRequestDelegate protocol.
 @return                A reference to the API request that was created. If a delegate was defined, then the request was started automatically.
 If the delegate was nil, then the request was NOT started--your application is responsible for starting the request and
 retaining a reference to the request so it can handle the response.
 @since                 1.0
 */
- (EXPAPIAgentProfileRequest *) getAgentProfileForAgent:(EXPAgent *)agent withProfileId:(NSString *)profileId delegate:(id<EXPAPIAgentProfileRequestDelegate>)delegate;

/**
 Saves an agent profile to the LRS. This will not overwrite any pre-existing profiles with a conflicting profile Id.
 
 @param profile         The agent profile to save to the LRS. The agent profile must have a profileId and agent defined.
 @param delegate        The delegate for the request. Must implement the EXPAPIAgentProfileRequestDelegate protocol.
 @return                A reference to the API request that was created. If a delegate was defined, then the request was started automatically.
 If the delegate was nil, then the request was NOT started--your application is responsible for starting the request and
 retaining a reference to the request so it can handle the response.
 @since                 1.0
 */
- (EXPAPIAgentProfileRequest *) saveAgentProfile:(EXPAgentProfile *)profile delegate:(id<EXPAPIAgentProfileRequestDelegate>)delegate;

/**
 Saves an agent profile to the LRS. Optionally, you may specifiy that this agent profile overwrite and preexisting agent profiles regardless of when they were created/updated. If you specify a previousProfile, the server will verify that you were working from the most recent version. If the agent profile cannot be updated due to a conflict, an error will be returned.
 
 @param profile         The agent profile to save to the LRS. The agent profile must have a profileId and agent defined.
 @param shouldOverwrite Set to YES to tell the server to overwrite any pre-existing agent profiles, regardless of when they were created.
 Set to NO to have the request fail if there is the agent profile already exists on the server and (may) have been
 changed since the last time your application downloaded it.
 @param previousProfile The most recent agent profile your application is aware of. This agent profile must have been received from any
 one of the getAgentProfile... methods.
 @param delegate        The delegate for the request. Must implement the EXPAPIAgentProfileRequestDelegate protocol.
 @return                A reference to the API request that was created. If a delegate was defined, then the request was started automatically.
 If the delegate was nil, then the request was NOT started--your application is responsible for starting the request and
 retaining a reference to the request so it can handle the response.
 @since                 1.0
 */
- (EXPAPIAgentProfileRequest *) saveAgentProfile:(EXPAgentProfile *)profile overwriting:(BOOL)shouldOverwrite previousProfile:(EXPAgentProfile *)previousProfile delegate:(id<EXPAPIAgentProfileRequestDelegate>)delegate;

/**
 Deletes an agent profile matching the profile id from the server for the specified agent.
 
 @param agent           The agent object--this must contain atleast one identifying property (e.g. an email address).
 @param profileId       The specific if of the agent profile you want to retrieve--must not be empty.
 @param delegate        The delegate for the request. Must implement the EXPAPIAgentProfileRequestDelegate protocol.
 @return                A reference to the API request that was created. If a delegate was defined, then the request was started automatically.
 If the delegate was nil, then the request was NOT started--your application is responsible for starting the request and
 retaining a reference to the request so it can handle the response.
 @since                 1.0
 */
- (EXPAPIAgentProfileRequest *) deleteAgentProfileForAgent:(EXPAgent *)agent withProfileId:(NSString *)profileId delegate:(id<EXPAPIAgentProfileRequestDelegate>)delegate;
/**
 Deletes all agent profiles for the specified agent.
 
 @param agent           The agent object--this must contain atleast one identifying property (e.g. an email address).
 @param delegate        The delegate for the request. Must implement the EXPAPIAgentProfileRequestDelegate protocol.
 @return                A reference to the API request that was created. If a delegate was defined, then the request was started automatically.
 If the delegate was nil, then the request was NOT started--your application is responsible for starting the request and
 retaining a reference to the request so it can handle the response.
 @since                 1.0
 */
- (EXPAPIAgentProfileRequest *) deleteAllAgentProfilesForAgent:(EXPAgent *)agent delegate:(id<EXPAPIAgentProfileRequestDelegate>)delegate;
/**
 Retrieves all the profiles id for the specified agent. This list may optionally be filtered by date to only show the profiles that were created/updated after the specified date.
 
 @param agent           The agent object--this must contain atleast one identifying property (e.g. an email address).
 @param since           Only fetch agent profiles created/updated after this date/time.
 @param delegate        The delegate for the request. Must implement the EXPAPIAgentProfileRequestDelegate protocol.
 @return                A reference to the API request that was created. If a delegate was defined, then the request was started automatically.
 If the delegate was nil, then the request was NOT started--your application is responsible for starting the request and
 retaining a reference to the request so it can handle the response.
 @since                 1.0
 */
- (EXPAPIAgentProfileRequest *) getAgentProfileIdsForAgent:(EXPAgent *)agent since:(NSDate *)since delegate:(id<EXPAPIAgentProfileRequestDelegate>)delegate;

/**
 Retrieves a Person object matching the identifying parameters on the provided agent.
 
 @param agent           The agent object--this must contain exactly one identifying property (e.g. an email address).
 @param delegate        The delegate for the request. Must implement the EXPAPIAgentRequestDelegate protocol.
 @return                A reference to the API request that was created. If a delegate was defined, then the request was started automatically.
 If the delegate was nil, then the request was NOT started--your application is responsible for starting the request and
 retaining a reference to the request so it can handle the response.
 @since                 0.95
 */
- (EXPAPIAgentRequest *)getExpandedAgentWithAgent:(EXPAgent *)agent delegate:(id<EXPAPIAgentRequestDelegate>)delegate;

// TODO: Implement the oAuth components of the EXPAPI.
//- (NSURL *) getOAuthAuthorizationURLWithRedirectURL:(NSURL *)redirectURL;
//- (id) updatedOauthTokenCredentialsWithTemporaryId:(NSString *)credentialsId andVerifierCode:(NSString *)verifierCode;

#pragma mark - Initialization and configuration
/**
 Initializes a EXPAPI implementation with the specified endpoint and delegate.
 For the most part, apps should be using the default API, but some cases may require
 creating a new API instance.
 
 @param aEndpoint   The endpoint to use for building requests to the API.
 @return            The newly instantiated EXPAPI object.
 */
- (id) initWithEndpoint:(NSURL *)aEndpoint;

/**
 Each xAPI project has a default API that it attempts to connect to.
 The implementing app can set the properties of the default API (e.g. the server).
 
 @return    A reference to the default API implementation.
 */
+ (EXPAPI *) defaultAPI;

/**
 Convenience method to quickly configure the defaultAPI object with an endpoint and delegate.
 It's recommended that this method get called in the AppDelegate of the implementing app
 so that the information is always available to the app.
 The delegate can be changed at any time.
 
 @param aEndpoint               The default API endpoint to use for building requests to the API.
 @param aAuthorizationProvider  The EXPAPIAuthorizationProvider that authenticates requests made through the default EXPAPI object.
 @return                        A reference to the default API.
 */
+ (EXPAPI *) configureDefaultAPIWithLRS:(NSURL *)aEndpoint authorizationProvider:(id<EXPAPIAuthenticationProvider>)aAuthorizationProvider;

/**
 Convenience method to quickly configure the defaultAPI object with an endpoint and delegate.
 It's recommended that this method get called in the AppDelegate of the implementing app
 so that the information is always available to the app.
 The delegate can be changed at any time.
 
 @param aEndpoint               The default API endpoint to use for building requests to the API.
 @param aAuthorizationProvider  The EXPAPIAuthorizationProvider that authenticates requests made through the default EXPAPI object.
 @param delegate                The queue delegate.
 @return                        A reference to the default API.
 */
+ (EXPAPI *) configureDefaultAPIWithLRS:(NSURL *)aEndpoint authorizationProvider:(id<EXPAPIAuthenticationProvider>)aAuthorizationProvider withQueueDelegate:(id<EXPAPIQueueDelegate>)delegate;
@end

/**
 Deprecated methods of EXPAPI
 */
@interface EXPAPI (Deprecated)
#pragma mark - Actor Profile API Methods
/**
 Retrieves an actor profile from the LRS for an actor matching a specific profile id.
 
 @param actor           The actor object--this must contain atleast one identifying property (e.g. an email address).
 @param profileId       The specific if of the actor profile you want to retrieve--must not be empty.
 @param delegate        The delegate for the request. Must implement the EXPAPIAgentProfileRequestDelegate protocol.
 @return                A reference to the API request that was created. If a delegate was defined, then the request was started automatically.
 If the delegate was nil, then the request was NOT started--your application is responsible for starting the request and
 retaining a reference to the request so it can handle the response.
 @deprecated            Use getAgentProfileForAgent:withProfileId:delegate instead.
 */
- (EXPAPIAgentProfileRequest *) getActorProfileForActor:(EXPAgent *)actor withProfileId:(NSString *)profileId delegate:(id<EXPAPIAgentProfileRequestDelegate>)delegate DEPRECATED_ATTRIBUTE;

/**
 Saves an actor profile to the LRS. This will not overwrite any pre-existing profiles with a conflicting profile Id.
 
 @param profile         The actor profile to save to the LRS. The actor profile must have a profileId and actor defined.
 @param delegate        The delegate for the request. Must implement the EXPAPIAgentProfileRequestDelegate protocol.
 @return                A reference to the API request that was created. If a delegate was defined, then the request was started automatically.
 If the delegate was nil, then the request was NOT started--your application is responsible for starting the request and
 retaining a reference to the request so it can handle the response.
 @deprecated            Use saveAgentProfile:delegate: instead.
 */
- (EXPAPIAgentProfileRequest *) saveActorProfile:(EXPActorProfile *)profile delegate:(id<EXPAPIAgentProfileRequestDelegate>)delegate DEPRECATED_ATTRIBUTE;

/**
 Saves an actor profile to the LRS. Optionally, you may specifiy that this actor profile overwrite and preexisting actor profiles regardless of when they were created/updated. If you specify a previousProfile, the server will verify that you were working from the most recent version. If the actor profile cannot be updated due to a conflict, an error will be returned.
 
 @param profile         The actor profile to save to the LRS. The actor profile must have a profileId and actor defined.
 @param shouldOverwrite Set to YES to tell the server to overwrite any pre-existing actor profiles, regardless of when they were created.
 Set to NO to have the request fail if there is the actor profile already exists on the server and (may) have been
 changed since the last time your application downloaded it.
 @param previousProfile The most recent actor profile your application is aware of. This actor profile must have been received from any
 one of the getActorProfile... methods.
 @param delegate        The delegate for the request. Must implement the EXPAPIAgentProfileRequestDelegate protocol.
 @return                A reference to the API request that was created. If a delegate was defined, then the request was started automatically.
 If the delegate was nil, then the request was NOT started--your application is responsible for starting the request and
 retaining a reference to the request so it can handle the response.
 @deprecated            Use saveAgentProfile:overwriting:previousProfile:delegate: instead
 */
- (EXPAPIAgentProfileRequest *) saveActorProfile:(EXPActorProfile *)profile overwriting:(BOOL)shouldOverwrite previousProfile:(EXPActorProfile *)previousProfile delegate:(id<EXPAPIAgentProfileRequestDelegate>)delegate DEPRECATED_ATTRIBUTE;

/**
 Deletes an actor profile matching the profile id from the server for the specified actor.
 
 @param actor           The actor object--this must contain atleast one identifying property (e.g. an email address).
 @param profileId       The specific if of the actor profile you want to retrieve--must not be empty.
 @param delegate        The delegate for the request. Must implement the EXPAPIAgentProfileRequestDelegate protocol.
 @return                A reference to the API request that was created. If a delegate was defined, then the request was started automatically.
 If the delegate was nil, then the request was NOT started--your application is responsible for starting the request and
 retaining a reference to the request so it can handle the response.
 @deprecated            Use deleteAgentProfileForAgent:withProfileId:delegate: instead.
 */
- (EXPAPIAgentProfileRequest *) deleteActorProfileForActor:(EXPAgent *)actor withProfileId:(NSString *)profileId delegate:(id<EXPAPIAgentProfileRequestDelegate>)delegate DEPRECATED_ATTRIBUTE;
/**
 Deletes all actor profiles for the specified actor.
 
 @param actor           The actor object--this must contain atleast one identifying property (e.g. an email address).
 @param delegate        The delegate for the request. Must implement the EXPAPIAgentProfileRequestDelegate protocol.
 @return                A reference to the API request that was created. If a delegate was defined, then the request was started automatically.
 If the delegate was nil, then the request was NOT started--your application is responsible for starting the request and
 retaining a reference to the request so it can handle the response.
 @deprecated            Use deleteAllAgentProfilesForAgent:delegate: instead.
 */
- (EXPAPIAgentProfileRequest *) deleteAllActorProfilesForActor:(EXPAgent *)actor delegate:(id<EXPAPIAgentProfileRequestDelegate>)delegate DEPRECATED_ATTRIBUTE;
/**
 Retrieves all the profiles id for the specified actor. This list may optionally be filtered by date to only show the profiles that were created/updated after the specified date.
 
 @param actor           The actor object--this must contain atleast one identifying property (e.g. an email address).
 @param since           Only fetch actor profiles created/updated after this date/time.
 @param delegate        The delegate for the request. Must implement the EXPAPIAgentProfileRequestDelegate protocol.
 @return                A reference to the API request that was created. If a delegate was defined, then the request was started automatically.
 If the delegate was nil, then the request was NOT started--your application is responsible for starting the request and
 retaining a reference to the request so it can handle the response.
 @deprecated            Use getAgentProfileIdsForAgent:since:delegate: instead.
 */
- (EXPAPIAgentProfileRequest *) getActorProfileIdsForActor:(EXPAgent *)actor since:(NSDate *)since delegate:(id<EXPAPIAgentProfileRequestDelegate>)delegate DEPRECATED_ATTRIBUTE;
/**
 Retrieves an actor object matching the identifying parameters on the provided actor.
 
 @param actor           The actor object--this must contain exactly one identifying property (e.g. an email address).
 @param delegate        The delegate for the request. Must implement the EXPAPIAgentRequestDelegate protocol.
 @return                A reference to the API request that was created. If a delegate was defined, then the request was started automatically.
 If the delegate was nil, then the request was NOT started--your application is responsible for starting the request and
 retaining a reference to the request so it can handle the response.
 @deprecated            Use getExpandedAgentWithAgent:delegate: instead.
 */
- (EXPAPIAgentRequest *)getActorWithPartialActor:(EXPAgent *)actor delegate:(id<EXPAPIAgentRequestDelegate>)delegate DEPRECATED_ATTRIBUTE;
@end
