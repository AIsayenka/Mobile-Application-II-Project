//
//  EXPActivityDefinition.h
//  EXPAPI
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
 Activity definition.
 */
@interface EXPActivityDefinition : EXPObject

/**
 The name of the activity.
 */
@property (nonatomic, strong) EXPLanguageMap *name;

/**
 A description of the activity.
 */
@property (nonatomic, strong, getter = getDescription) EXPLanguageMap *desc;

/**
 The URI for the activity.
 */
@property (nonatomic, strong) NSString *type;

/**
 Identifies a specific interaction type, in the case of an interaction activity.
 */
@property (nonatomic, strong) NSString *interactionType;

/**
 A map of any domain-specific content relative to this statement.
 Objects in extensions must be based on NSString, NSArray, or NSDictionary.
 If an object is an NSArray or NSDictionary, then the objects it contains must also be based on these classes.
 This is to support JSON encoding of the dictionary.
 
 @todo  The setter should do some basic validation to ensure that the value is okay.
 */
@property (nonatomic, strong) NSMutableDictionary *extensions;

/**
 Initializes an activity with a name, description, and type.
 
 @param aName           The name of the activity.
 @param aDescription    The description of the activity.
 @param aType           The type of activity.
 @param aExtensions     A map of domain-specific content.
 */
- (id) initWithName:(NSString *)aName description:(NSString *)aDescription type:(NSString *)aType extensions:(NSDictionary *)aExtensions;

/**
 Initializes an activity with a name, description, and type.
 
 @param aName           The name of the activity.
 @param aDescription    The description of the activity.
 */

+ (EXPActivityDefinition *) activityDefinitionWithName:(NSString *)aName description:(NSString *)aDescription;

/**
 Initializes an activity with a name, description, and type.
 
 @param aName           The name of the activity.
 @param aDescription    The description of the activity.
 @param aType           The type of activity.
 */
+ (EXPActivityDefinition *) activityDefinitionWithName:(NSString *)aName description:(NSString *)aDescription type:(NSString *)aType;

/**
 Initializes an activity with a name, description, and type.
 
 @param aName           The name of the activity.
 @param aDescription    The description of the activity.
 @param aType           The type of activity.
 @param aExtensions     A map of domain-specific content.
 */
+ (EXPActivityDefinition *) activityDefinitionWithName:(NSString *)aName description:(NSString *)aDescription type:(NSString *)aType extensions:(NSDictionary *)aExtensions;

/**
 Convenience method to add a property and value to the extensions dictionary
 without having to create a dictionary.
 
 @param value   The value to store in the extension. Must be either an NSArray, NSDictionary, or NSString.
 @param key     Store the value in this key.
 */
- (void) setExtensionPropertyValue:(id)value forKey:(NSString *)key;

/**
 Convenience method to remove a property from the extensions dictionary.
 
 @param key Removes the object at this key.
 */
- (void) removeExtensionPropertyForKey:(NSString *)key;

@end
