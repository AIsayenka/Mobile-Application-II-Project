//
//  EXPPerson.h
//  xAPI SDK
//
//  Copyright (c) 2013 Float Mobile Learning. All rights reserved.
//  http://floatlearning.com/
//
//  Project assistance from Rustici Software.
//  http://scorm.com/
//

#import <xAPIKit/EXPObject.h>

@class EXPAgent, EXPAccount;

/**
 Person object
 */
@interface EXPPerson : EXPObject

@property (nonatomic, readonly) NSArray *name;
@property (nonatomic, readonly) NSArray *mbox;
@property (nonatomic, readonly) NSArray *openid;
@property (nonatomic, readonly) NSArray *account;
@property (nonatomic, strong) NSString *objectType;

- (id) initWithMbox:(NSString *)mbox;
- (id) initWithName:(NSString *)name andMbox:(NSString *)mbox;
+ (EXPPerson *) personWithMbox:(NSString *)mbox;
+ (EXPPerson *) personWithAgent:(EXPAgent *)agent;
- (void) addName:(NSString *)name;
- (void) removeName:(NSString *)name;
- (void) addMbox:(NSString *)mbox;
- (void) removeMbox:(NSString *)mbox;
- (void) addOpenid:(NSString *)openid;
- (void) removeOpenid:(NSString *)openid;
- (void) addAccount:(EXPAccount *)account;
- (void) removeAccount:(EXPAccount *)account;
- (EXPAgent *) agentFromIndex:(NSInteger)index;

@end
