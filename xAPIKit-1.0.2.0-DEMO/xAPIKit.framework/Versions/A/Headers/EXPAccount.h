//
//  EXPAccount.h
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
 Represents an account owned by a user.
 
 @remarks   If the agent is authenticated via the OAuth Reigstered application workflow (with no known user),
            then the consumer_key should be used as the accountName, and the token request endpoint should
            be used as the accountServiceHomePage. <strong>It is crucial not to do this for any agent object
            where a known user is involved, as this would lead to logically different agents being considered
            identical by the LRS.</strong>
 */
@interface EXPAccount : EXPObject

/**
 The URI to the canonical home page for the system the account is on. Must NOT be nil or empty string.
 @since 0.95
 */
@property (nonatomic, strong) NSString *homePage;

/**
 The unique ID or name used to log in to this account. Must NOT be nil or empty string.
 @since 0.95
 */
@property (nonatomic, strong) NSString *name;

/**
 Creates a new account reference specifying the account name and service homepage.
 
 @param aHomePage    The URI to the canonical home page for the system the account is on (e.g http://twitter.com).
 @param aAccountName        The unique ID or name used to log in to this account.
 @since 0.95
 @return                    The initialized account object.
 */
- (id) initWithHomePage:(NSString *)aHomePage andAccountName:(NSString *)aAccountName;

/**
 Creates a new account reference specifying the account name and service homepage.
 
 @param aAccountName        The unique ID or name used to log in to this account.
 @param aHomePage           The URI to the canonical home page for the system the account is on (e.g http://twitter.com).
 @since 0.95
 @return                    The initialized account object.
 */
+ (EXPAccount *) accountWithId:(NSString *)aAccountName forHomePage:(NSString *)aHomePage;

@end
