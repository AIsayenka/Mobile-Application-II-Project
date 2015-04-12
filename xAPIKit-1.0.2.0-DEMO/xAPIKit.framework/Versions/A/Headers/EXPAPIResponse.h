//
//  EXPAPIResponse.h
//  xAPI SDK
//
//  Copyright (c) 2013 Float Mobile Learning. All rights reserved.
//  http://floatlearning.com/
//
//  Project assistance from Rustici Software.
//  http://scorm.com/
//


#import <Foundation/Foundation.h>

/**
 Represents a response from the LRS.
 This is primarily used when parsing through multipart/mixed responses.
 
 @warning There is a limitation in EXPAPIResponse that all responses are assumed to use the 1.1 HTTP version.
 */
@interface EXPAPIResponse : NSHTTPURLResponse

/**
 The content type of the response (e.g. application/json).
 Strips off any data after the semi-colon.
 */
@property (weak, nonatomic, readonly) NSString *contentType;

/**
 The data of the response body.
 */
@property (nonatomic, strong, readonly) NSData *responseData;

/**
 Convenience property to fetch the body response as a string.
 */
@property (weak, nonatomic, readonly) NSString *responseString;

/**
 Convenience property to fetch the body response as JSON.
 */
@property (weak, nonatomic, readonly) id responseJSON;

/**
 Initializes the response with the key data from the LRS.
 
 @param url             The URL that was requested.
 @param statusCode      The HTTP status code that was returned from the server (e.g. 200 OK).
 @param HTTPVersion     The HTTP version of the server (note: this is always 1.1 due to a limitation in this class).
 @param headerFields    The headers of the response.
 @param responseData    The data from the body of the response.
 */
- (id) initWithURL:(NSURL *)url statusCode:(NSInteger)statusCode HTTPVersion:(NSString *)HTTPVersion headerFields:(NSDictionary *)headerFields responseData:(NSData *)responseData;

/**
 Creates a response object using key details from the LRS response.
 
 @param statusCode      The HTTP status code that was returned from teh server (e.g. 200 OK).
 @param headerFields    The headers of the response.
 @param responseData    The data from the body of the response.
 @param url             The URL that was requested.
 @return                    A EXPAPIResponse object.
 */
+ (EXPAPIResponse *) responseWithStatusCode:(NSInteger)statusCode headerFields:(NSDictionary *)headerFields responseData:(NSData *)responseData fromURL:(NSURL *)url;

/**
 Converts an NSHTTPURLResponse into a EXPAPIResponse.
 
 @param response        The raw NSHTTPURLResponse received from NSURLConnection.
 @param responseData    The data from the body of the response.
 @return                    A EXPAPIResponse object.
 */
+ (EXPAPIResponse *) responseWithHTTPResponse:(NSHTTPURLResponse *)response andResponseData:(NSData *)responseData;

/**
 Takes a multipart/mixed response from the server and the response data and splits it into multiple responses
 as required by the SDK.
 
 @param response         The main response headers.
 @param responseData     The entire response data.
 @param error            On return contains the error (if any) that was encountered.
 @return                    An array of EXPAPIResponse containing the proper data for each response.
 */
+ (NSArray *) responsesFromResponse:(NSHTTPURLResponse *)response andResponseData:(NSData *)responseData error:(NSError **)error;

@end
