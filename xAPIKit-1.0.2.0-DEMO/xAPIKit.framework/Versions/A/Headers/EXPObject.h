//
//  EXPObject.h
//  xAPI SDK
//
//  Copyright (c) 2013 Float Mobile Learning. All rights reserved.
//  http://floatlearning.com/
//
//  Project assistance from Rustici Software.
//  http://scorm.com/
//

#import <Foundation/Foundation.h>

extern NSString* const kObjectType;

@interface EXPObject : NSObject

/**
 Initializes a TCObject with the values in the supplied NSDictionary. Unless otherwise specified by
 a property mapping, the propery names matching the key name receives the value for that key.
 
 @param dict    A dictionary containing key-values.
 @return        An initialized TCObject.
 */
- (id) initWithDictionary:(NSDictionary *)dict;

/**
 Convenience method for creating a TCObject with the values in the supplied NSDictionary. Unless otherwise specified by
 a property mapping, the propery names matching the key name receives the value for that key.
 
 @param dict    A dictionary containing key-values.
 @return        An initialized TCObject.
 */
+ (id) objectFromDictionary:(NSDictionary *)dict;

/**
 Sets a property value on the object for a property matching the supplied key.
 Intended to be used when converting a JSON response to an object.
 
 @param value   The value to set to the property.
 @param key     The name of the property on which to set the value.
 */
- (void) setSerializedValue:(id)value forProperty:(NSString *)key;

/**
 Retrieves a value suitable for serialization (as an foundation object such as NSDictionary or NSArray) from the specified property name.
 
 @param key     The name of the property from which to retrieve a value suitable for serialization.
 @return        The value as a foundation object.
 */
- (id) serializedValueForKey:(NSString *)key;

/**
 Subclasses override this method to create a mapping between the key name in a dictioanry and the property name on the object.
 
 @return        The key-property mapping.
 */
- (NSDictionary *) propertyMapping;

/**
 Returns an array of all the class properties that should be included when converting the class to a dictionary.
 The default implementation of this method iterates through all the properties of the class and its superclasses (until NSObject).
 Subclasses may explicitly define what properties can be retrieved by overriding this method and returning an NSArray.
 
 @return    An array of NSString objects that represent the property names to add to the dictionary representation of the class.
 */
- (NSArray *) classProperties;

/**
 Retrieves a dictionary reprsentation of this xAPI object.
 */
- (NSDictionary *) dictionary;

/**
 Converts this object to a JSON string compatible with the xAPI.
 */
- (NSString *) JSONString;

/**
 Same as JSONString but the output is formatted nicely (suitable for on-screen display).
 */
- (NSString *) prettyJSONString;

/**
 Same as JSONString, but it represents the bytes of the string.
 */
- (NSData *) JSONData;


@end
