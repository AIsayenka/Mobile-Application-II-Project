//
//  EXPStatementRef.h
//  xAPI SDK
//
//  Copyright (c) 2013 Float Mobile Learning. All rights reserved.
//  http://floatlearning.com/
//
//  Project assistance from Rustici Software.
//  http://scorm.com/
//

#import <xAPIKit/EXPStatement.h>

/**
 Represents a StatementRef. A Statement Reference is a pointer to another pre-existing Statement.
 
 * A Statement Reference MUST specify an "objectType" property with the value "StatementRef".
 * A Statement Reference MUST set the "id" property to the UUID of a Statement which is present on the system.
 
 StatementRefs are used when voiding statements.
 */
@interface EXPStatementRef : EXPStatement

/**
 Creates a new StatementRef referencing the statement identified by the UUID.
 
 @param sid     The UUID of the statement to reference.
 */
- (id) initWithStatementId:(NSString *)sid;

/**
 Creates a statement ref for the specified statement.
 
 @param statement   The statement to create a StatementRef for.
 @return                A valid StatementRef.
 @throws                Exception if statement does not have a statement id
 */
+ (EXPStatementRef *) statementRefWithStatement:(EXPStatement *)statement;

@end
