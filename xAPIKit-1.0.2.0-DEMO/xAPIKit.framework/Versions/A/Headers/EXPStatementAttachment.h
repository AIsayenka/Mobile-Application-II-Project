//
//  EXPStatementAttachment.h
//  xAPI SDK
//
//  Copyright (c) 2013 Float Mobile Learning. All rights reserved.
//  http://floatlearning.com/
//
//  Project assistance from Rustici Software.
//  http://scorm.com/
//

#import <xAPIKit/EXPObject.h>

@class EXPLanguageMap, UIImage;

/**
 Represents an attachment on a statement. A statement attachment is a digital artefact providing evidence of a learning experience.
 
 In some cases an attachment may logically be an important part of a learning record. Think of a simulated communication with AEXP, an essay, a video, etc. Another example of such an attachment is (the image of) a certificate that was granted as a result of an experience. It is useful to have a way to store these attachments in and retrieve them from an LRS.
 */
@interface EXPStatementAttachment : EXPObject

/**
 Identifies the usage of this attachment. For example: one expected use case for attachments is to include a "completion certificate". A type URI corresponding to this usage should be coined, and used with completion certificate attachments. Required.
 */
@property (nonatomic, strong) NSString *usageType;

/**
 Display name (title) of this attachment. Required.
 */
@property (nonatomic, strong) EXPLanguageMap *display;

/**
 A description of the attachment.
 */
@property (nonatomic, strong) EXPLanguageMap *desc;

/**
 The content type of the attachment. Required.
 */
@property (nonatomic, strong) NSString *contentType;

/**
 The length of the attachment data in octets.
 */
@property (nonatomic, readonly) NSUInteger length;

/**
 The SHA-2 hash of the attachment data. A minimum key size of 256 bits is recommended. Required.
 */
@property (nonatomic, readonly) NSString *sha2;

/**
 A URL at which the attachment data may be retrieved, or from which it used to be retrievable.
 */
@property (nonatomic, strong) NSURL *fileUrl;

/**
 The actual contents of the attachment.
 When this is set, sha2 and length are automatically calculated.
 You cannot change this value without first calling clear.
 */
@property (nonatomic, strong) NSData *attachmentData;

/**
 Creates a new attachment for any statement.
 
 @param attachmentData  The contents of the attachment.
 @param usageType       Identifies the intended usage for this attachment.
 @param name            The display name of the attachment. Creates language map with the specified value using the current locale as the identifier.
 @param contentType     The type of content represented by attachmentData (e.g. image/png).
 @return                    A valid attachment that is ready to be attached to a statement.
 */
+ (EXPStatementAttachment *) attachmentWithData:(NSData *)attachmentData usageType:(NSString *)usageType displayName:(NSString *)name andContentType:(NSString *)contentType;

/**
 A convenience method to create an attachment for a UIImage. Saves the image as a PNG.
 
 @param image       The UIImage for which to create an attachment.
 @param usageType   Identifies the intended usage for this attachment.
 @param name        The display name of the attachment. Creates language map with the specified value using the current locale as the identifier.
 @return                A valid attachment that is ready to be attached to a statement.
 */
+ (EXPStatementAttachment *) attachmentWithImage:(UIImage *)image usageType:(NSString *)usageType andDisplayName:(NSString *)name;

/**
 Clears the computed values for sha2 and length; also clears out the attachmentData.
 Use this if you want to reuse the current container for different attachment data.
 */
- (void) clear;

@end
