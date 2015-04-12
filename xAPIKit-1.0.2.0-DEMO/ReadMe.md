Getting Started
==============
The Experience API iOS SDK is (c)2015 [Float Mobile Learning](http://floatlearning.com/)
This demo version of the framework expires on May 29, 2015.

To add the xAPIKit.framework to your project:
--------------------------------------------
1. Drag and drop it into the "Frameworks" folder. Be sure to copy the framework to your projects directory.
2. Add `-ObjC` to Other Linker Flags in the Build Settings for your application.
3. Add `SystemConfiguration.framework` and `Security.framework` to your project.

Configuring xAPIKit:
-------------------
It is recommended to configure xAPIKit in your application:didFinishLaunchingWithOptions: method.

	[EXPAPI configureDefaultAPIWithLRS:[NSURL URLWithString:@"https://cloud.scorm.com/ScormEngineInterface/TCAPI/public/"]
	             authorizationProvider:[[EXPBasicHTTPAuthentication alloc] initWithUsername:@"public" andPassword:@""]];

This will set up the library to work with the public LRS provided by SCORM Cloud.
You'll need to add this import statement to your AppDelegate.m file:

	#import <xAPIKit/xAPIKit.h>

Get Statements from the LRS:
----------------------------
EXPAPI gives you a lot of ways to communicate with the LRS. Probably the most common will be sending/receiving statements.

Import the framework into one of your view controller headers:

	#import <xAPIKit/xAPIKit.h>

Then add the EXPAPIStatementRequestDelegate protocol to the list of protocols your view controller implements. For example:

	@interface ViewController : UIViewController <EXPAPIStatementRequestDelegate>
	...
	@end


Now in your view controller's implementation in the viewDidLoad method, add:

	[[EXPAPI defaultAPI] getStatementsWithQuery:[EXPStatementQuery statementQueryWithLimit:10] delegate:self];

This will get the 10 latest statements from the LRS when the view loads. To see the response from the server, implement the statementsReceived: protocol method:

	- (void) statementsReceived:(EXPStatementsResult *)result
	{
	    NSLog(@"%d statements received.", result.numberOfStatements);
	    NSLog(@"Statements: %@", result.statements);
	}

This will print out to the log the number of statements received (should be 10) and then print out each statement received.

Installing the Documentation
----------------------------
To install the documentation, copy com.floatlearning.xAPIKit.docset to ~/Library/Developer/Shared/Documentation/DocSets. The documentation will now be available in Xcode's Organizer.

Creating a PKCS12 File for Statement Signing:
----------------------------
As of version 1.0.0 of the xAPI specification, you can now sign statements. By specifying a [PKCS12](http://en.wikipedia.org/wiki/PKCS_♯12), the SDK will create the statement signatures for you.

###1. Create a private key
    openssl genrsa 1024 > private.key

###2. Create an X509 certificate
    openssl req -new -x509 -nodes -sha1 -days 73300 -key private.key -outform PEM > x509.crt

Before creating the certificate, it will ask you a number of questions about the meta data to add to the certificate. It is recommended that you fill out these values instead of leaving them blank.

###3. Bundle the key and certificate into a PKCS12 file
    openssl pkcs12 -export -in x509.crt -inkey private.key -out bundle.p12

Before creating the PKCS12 file, it will ask you to set a passphrase. **It is STRONGLY recommended** that you create a passphrase *and* that the passphrase is at least 20 characters long *and* that the passphrase contains both numbers and symbols.

Signing a Statement
----------------------------
*Note: Statement signing requires iOS 6 or newer.*

Once you have your PKCS12 file, you can sign the statement. The data for the file can be loaded in from the app bundle or from a remote server.

    NSError *error = nil;
    NSData *p12 = [NSData dataWithContentsOfFile:@"filename"];
    BOOL result = [statement signStatementWithPKCS12:p12 usingPassphrase:@"passphrase" error:&error];

`result` will be YES if the signature was created and added to the statement successfully. Otherwise `error` will contain the reason the signature could not be created.

**Do not modify the statement after creating the signature.** The signature is calculated based on the current state of the statement. If you modify the statement, the signature will be invalid. If you need to change the statement, invalidate the signature and recreate it:

    [statement invalidateSignature];
    [statement signStatementWithPKCS12:p12 usingPassphrase:@"passphrase" error:&error];

### Notes
By default, the display name of the signature will be "Signature" and the description will be blank. If you wish to change these values, you may do so after signing the statement:

    statement.signature.display = [EXPLanguageMap languageMapForCurrentLanguageWithString:@"New Display Name"];
    statement.signature.description = [EXPLanguageMap languageMapForCurrentLanguageWithString:@"New Description"];

For More Information:
----------------------------
For more information regarding the xAPI, visit [http://tincanapi.com/](http://tincanapi.com/).

For more information about how to incorporate the xAPI iOS SDK into your project, check out our tutorials on our blog: [http://floatlearning.com/tag/tin-can-ios-library/](http://floatlearning.com/tag/tin-can-ios-library/).

If you've encountered a bug or have a suggestion for how we could improve the SDK, please let us know by emailing us at support@floatlearning.com.