//
//  EXPAgent.h
//  EXPAPI
//
//  Copyright (c) 2013 Float Mobile Learning. All rights reserved.
//  http://floatlearning.com/
//
//  Project assistance from Rustici Software.
//  http://scorm.com/
//

#import <xAPIKit/EXPStatementObject.h>

@class EXPAccount;

/**
 An "agent" may refer to an indiviual learner or a team of learners.
 
 @remarks   Note that all properties are arrays. The most correct, or most recent data should be listed first in each array.
 */
@interface EXPAgent : EXPStatementObject

/**
 An array of known names for this agent.
 */
@property (nonatomic, strong) NSString *name;

/**
 An array of e-mail addresses that have only ever been assigned to this agent.
 */
@property (nonatomic, strong) NSString *mbox;

/**
 An array of SHA1 hashed e-mail addresses that have only ever been assigned to this agent. 
 The LRS will compare this value with mbox values by applying SHA1(mbox).
 */
@property (weak, nonatomic, readonly) NSString *mbox_sha1sum;

/**
 An array of URIs associated with an openID for this agent.
 */
@property (nonatomic, strong) NSString *openid;

/**
 An array of account objects associated with this agent.
 You can conveniently add account information by calling -addAccountWithId:serviceHomePage:.
 */
@property (nonatomic, strong) EXPAccount *account;

/**
 Initializes an agent with a name and an e-mail address.
 */
- (id) initWithName:(NSString *)aName andMbox:(NSString *)aMbox;

/**
 Convenience method for creating an agent with a name and e-mail address.
 
 @param aName   The name of the agent.
 @param aMbox   The email address (in mailto:{email}) form.
 */
+ (EXPAgent *) agentWithName:(NSString *)aName andMbox:(NSString *)aMbox;

@end
