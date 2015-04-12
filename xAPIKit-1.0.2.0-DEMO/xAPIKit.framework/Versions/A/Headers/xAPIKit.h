//
//  xAPIKit.h
//  xAPI SDK
//
//  Copyright (c) 2013 Float Mobile Learning. All rights reserved.
//  http://floatlearning.com/
//
//  Project assistance from Rustici Software.
//  http://scorm.com/
//

// SDK Information
#define XAPIKIT_VERSION   @"1.0.2.0"
// Debugger
// To enable debug messages from xAPIKit, simply call EXPEnableLogging() anywhere in your code.
// To disable debugging, call EXPDisableLogging().
// Logging will NOT be enabled if __OPTIMIZE__ is defined. __OPTIMIZE__ is defined, by default, on release builds of your application.
BOOL EXPShouldLogDebugMessages;
#ifndef __OPTIMIZE__
#define EXPEnableLogging()  {EXPShouldLogDebugMessages = YES;}
#else
#define EXPEnableLogging()  {EXPShouldLogDebugMessages = NO;}
#endif
#define EXPDisableLogging() {EXPShouldLogDebugMessages = NO;}

// API Interaction
#import <xAPIKit/EXPAPI.h>
#import <xAPIKit/EXPBasicHTTPAuthentication.h>
#import <xAPIKit/EXPStatementQueue.h>
#import <xAPIKit/EXPStatementQueueFilePersistence.h>

// Extended Types
#import <xAPIKit/EXPActivityProfile.h>
#import <xAPIKit/EXPActivityState.h>
#import <xAPIKit/EXPActorProfile.h>
#import <xAPIKit/EXPAgentProfile.h>
#import <xAPIKit/EXPContextActivities.h>
#import <xAPIKit/EXPInteraction.h>
#import <xAPIKit/EXPInteractionComponents.h>
#import <xAPIKit/EXPInteractionDefinition.h>
#import <xAPIKit/EXPStatementQuery.h>

// Standard Types
#import <xAPIKit/EXPAccount.h>
#import <xAPIKit/EXPActivity.h>
#import <xAPIKit/EXPActivityCollection.h>
#import <xAPIKit/EXPActivityDefinition.h>
#import <xAPIKit/EXPAgent.h>
#import <xAPIKit/EXPContext.h>
#import <xAPIKit/EXPGroup.h>
#import <xAPIKit/EXPLanguageMap.h>
#import <xAPIKit/EXPObject.h>
#import <xAPIKit/EXPPerson.h>
#import <xAPIKit/EXPResult.h>
#import <xAPIKit/EXPScore.h>
#import <xAPIKit/EXPState.h>
#import <xAPIKit/EXPStatement.h>
#import <xAPIKit/EXPStatementAttachment.h>
#import <xAPIKit/EXPStatementSignature.h>
#import <xAPIKit/EXPStatementVerb.h>
#import <xAPIKit/EXPStatementObject.h>
#import <xAPIKit/EXPStatementRef.h>
#import <xAPIKit/EXPStatementsResult.h>

