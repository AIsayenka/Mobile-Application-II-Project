//
//  DBManager.h
//  DatabaseApp
//
//  Created by ituser on 4/1/2015.
//  Copyright (c) 2015 GBC. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DBManager : NSObject
@property(strong,nonatomic)NSString* databasePath;

+(DBManager*)getSharedInstance;

-(BOOL)createDB;
-(BOOL)saveData:(NSString*)_id actor:(NSString*)actor verb:(NSString*)verb object:(NSString*)object
      longitude:(NSString*)lon latitude:(NSString*)lat;
-(NSArray*)findById:(NSString*)_id;
-(NSMutableArray*)selectDistinct;

@end
