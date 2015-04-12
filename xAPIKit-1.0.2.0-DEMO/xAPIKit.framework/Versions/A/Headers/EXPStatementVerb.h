//
//  EXPStatementVerb.h
//  xAPI SDK
//
//  Copyright (c) 2013 Float Mobile Learning. All rights reserved.
//  http://floatlearning.com/
//
//  Project assistance from Rustici Software.
//  http://scorm.com/
//

#import <xAPIKit/EXPObject.h>

@class EXPLanguageMap;

/**
 The Verb defines the action between Actor and Activity.
 
 The Verb in an xAPI Statement describes the action performed during the learning experience. The xAPI does not specify any particular Verbs. (With one exception, namely the reserved Verb 'http://adlnet.gov/expapi/verbs/voided'). Instead, it defines how to create Verbs so that communities of practice can establish Verbs meaningful to their members and make them available for use by anyone. A predefined list of Verbs would be limited by definition and might not be able to effectively capture all possible future learning experiences.
 */
@interface EXPStatementVerb : EXPObject

/**
 Corresponds to a Verb definition. Each Verb definition corresponds to the meaning of a Verb, not the word. The URI should be human-readable and contain the Verb meaning.
 */
@property (nonatomic, strong) NSString *uri;
/**
 The human readable representation of the Verb in one or more languages. This does not have any impact on the meaning of the Statement, but serves to give a human-readable display of the meaning already determined by the chosen Verb.
 */
@property (nonatomic, strong) EXPLanguageMap *display;

/**
 Creates a verb with a URI and display string.
 
 @param uri         The URI for the verb.
 @param verb        The display string--converted into a language map using the current locale as the identifier.
 */
- (id) initWithURI:(NSString *)uri andDisplayString:(NSString *)verb;

/**
 Creates a verb with a URI and display string.
 
 @param uri         The URI for the verb.
 @param display     The display string--converted into a language map using the current locale as the identifier.
 @return            Verb
 */
+ (EXPStatementVerb *) verbWithURI:(NSString *)uri andDisplayString:(NSString *)display;

/**
 Creates the special, reserved "voided" verb.
 */
+ (EXPStatementVerb *) voided;

@end
