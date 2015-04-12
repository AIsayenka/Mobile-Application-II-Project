//
//  EXPStatementSignature.h
//  xAPI SDK
//
//  Copyright (c) 2013 Float Mobile Learning. All rights reserved.
//  http://floatlearning.com/
//
//  Project assistance from Rustici Software.
//  http://scorm.com/
//


#import <xAPIKit/EXPStatementAttachment.h>

typedef enum
{
    EXPStatementSigningAlgorithmRS256,
    
    // Currently not supported:
//    EXPStatementSigningAlgorithmRS384,
//    EXPStatementSigningAlgorithmRS512
} EXPStatementSigningAlgorithm;

/**
 When generating the signature, you can specifiy properties on the statement that should be ignored when creating the signature.
 This should be specified in the options parameter in signStatementWithPKCS12:usingPassphrase:withAlgorithm:options:error:.
 Only the following keys may be specified: id, authority, stored, timestamp, version
 */
extern NSString* const kEXPStatementSigningOptionIgnoreProperties;

/**
 According to the Experience API specification, all signatures must have the a usage type of http://adlnet.gov/expapi/attachments/signature.
 */
extern NSString* const KEXPStatementSignatureUsageType;

@class EXPStatement;

/**
 A Statement may include a digital signature to provide strong and durable evidence of the authenticity and integrity of the Statement.
 
 NOTE: Statement signing only works on iOS 6 and later.
 
 Some Statements will have regulatory or legal significance, or otherwise require strong and durable evidence of their authenticity and integrity. It may be necessary to verify these Statements without trusting the system they were first recorded in, or perhaps without access to that system. Digital signatures will enable a third-party system to validate such Statements.
 
 Currently, the xAPI iOS SDK only supports the RS256 signing algorithm. Signing credentials must be provided using a PKCS12 file. In the future, the SDK may allow for signing statements using data from the device's keychain. If this would be useful, let us know.
 
 Regardless if you are including the PKCS12 file in the distributable or downloading the data from a remote server at runtime, it is STRONGLY recommended that the PKCS12 file be protected with a passphrase AND that the passphrase is atleast 20 characters long containing both numbers and symbols. The passphrase is what will protect your PKCS12 from unauthorized parties. Since the PKCS12 file contains your private key, this is imparative to the integrity of the private key. By having a passphrase that is atleast 20 characters long with both numbers and symbols, it greatly reduces (to the point of it being statistically impossible over the course of a lifetime) the chance of your PKCS12 being cracked open.
 
 Note: Although a PKCS12 file can contain multiple items, the SDK will only read the first item.
 
 The signatures are created following the JSON Web Signature (JWS) specification. However, the SDK does all the work. All you need to do is provide the signing credentials.
 
 When signed statements are received from the LRS, the signature will contain the certificateChain data will contain the certificate chain of the signing identity.
 IMPORTANT: The SDK does NOT validate signatures returned from the LRS. It is your responsibility to inspect the certificate chain and determine if the statement is signed by a trusted source.
 
 @since 1.0
 */
@interface EXPStatementSignature : EXPStatementAttachment

/**
 Contains an array of NSData with the certificate chain for the current signature.
 Use the values here to determine whether a signed statement from the LRS is trusted.
 */
@property (nonatomic, strong, readonly) NSArray *certificateChain;

/**
 Creates a new statement signature referencing the provided statement.
 Note: This does not actually compute the signature, it only prepares it for signing.
 To actually sign the statement, you must use signStatementWithPKCS12:usingPassphrase:error:
 
 You cannot change the statement a signature references after it has been created.
 
 @param statement    The statement that should be signed with this signature.
 */
- (id) initWithStatement:(EXPStatement *)statement;

/**
 Computes the signature for the statement.
 
 Note that this signature is generated based the state of the statement at the time of signing. It should be the last thing you do with the statement before persisting to the LRS. If you change the statement after creating the signature, you must invalidate the signature (invalidateSignature) and create it again.
 
 @param p12          The data of a PKCS12 file (http://en.wikipedia.org/wiki/PKCS_♯12) to use for signing. This file should contain the private key and X.509 certificate chain.
 @param passphrase   The passphrase of the PKCS12 file. It is STRONGLY RECOMMENDED that your PKCS12 file be protected by a passphrase and that the passphrase is at least 20 characters long containing both numbers and symbols.
 @param algorithm    The signing algorithm to use when generating the signature. Currently, the xAPI iOS SDK only supports the RS256 algorithm.
 @param options      Adjusts how the statement gets signed. Currently, only the kEXPStatementSigningOptionIgnoreProperties option is available.
 @param error        Contains an error on return if the statement was not generated successfully.
 @return                YES if the signature was generated succesfully.
 */
- (BOOL) signStatementWithPKCS12:(NSData *)p12 usingPassphrase:(NSString *)passphrase withAlgorithm:(EXPStatementSigningAlgorithm)algorithm options:(NSDictionary *)options error:(NSError **)error;

/**
 Removes all computed signature data.
 */
- (void) invalidateSignature;

@end
