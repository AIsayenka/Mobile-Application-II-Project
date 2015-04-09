//
//  DBManager.m
//  DatabaseApp
//
//  Created by ituser on 4/1/2015.
//  Copyright (c) 2015 GBC. All rights reserved.
//

#import "DBManager.h"
#import <sqlite3.h>
static DBManager* sharedInstance = nil;
static sqlite3 *database = nil;
static sqlite3_stmt *statement = nil;

@implementation DBManager

+(DBManager*)getSharedInstance{
    
    if (!sharedInstance) {
        sharedInstance = [[super allocWithZone:NULL]init];
        [sharedInstance createDB];
    }
    
    return sharedInstance;
}

-(BOOL)createDB{
    
    NSString* docDir;
    NSArray* dirPaths;
    
    dirPaths = NSSearchPathForDirectoriesInDomains(NSDocumentationDirectory, NSUserDomainMask, YES);
    docDir = dirPaths[0];
    
    self.databasePath = [[NSString alloc]initWithString:[docDir stringByAppendingString:@"statements.db"]];
    BOOL isSuccess = YES;
    const char* dbp = [self.databasePath UTF8String];
    NSFileManager *filemgr = [NSFileManager defaultManager];
    if ([filemgr fileExistsAtPath:self.databasePath]==NO) {
        char* errMsg;
        
        if (sqlite3_open(dbp, &database)==SQLITE_OK) {
            const char* stmt = "create table if not exists statements(_id text primary key, actor text, verb text, object text, lon text, lat text)";
            if (sqlite3_exec(database, stmt, NULL, NULL, &errMsg)!=SQLITE_OK) {
                isSuccess = NO;
                NSLog(@"Failed to create table");
            }
            sqlite3_close(database);
        }else{
            isSuccess = NO;
            NSLog(@"Failed to create database");
        }
    }
    
    return isSuccess;
    
}
-(BOOL)saveData:(NSString*)_id actor:(NSString*)actor verb:(NSString*)verb object:(NSString*)object
      longitude:(NSString*)lon latitude:(NSString*)lat{
    NSString* docDir;
    NSArray* dirPaths;
    
    dirPaths = NSSearchPathForDirectoriesInDomains(NSDocumentationDirectory, NSUserDomainMask, YES);
    docDir = dirPaths[0];
    
    self.databasePath = [[NSString alloc]initWithString:[docDir stringByAppendingString:@"statements.db"]];
    
    const char* dbpath = [self.databasePath UTF8String];
    BOOL isSuccess = YES;
    if (sqlite3_open(dbpath, &database)==SQLITE_OK) {
        
        NSString* insertSQL = [NSString stringWithFormat:@"insert into statements(_id, actor, verb, object, lon, lat) values (\"%@\", \"%@\", \"%@\", \"%@\", \"%@\", \"%@\")",_id , actor, verb, object, lon, lat];
        
        const char* sql_stmt = [insertSQL UTF8String];
        
        if(sqlite3_prepare_v2(database, sql_stmt, -1, &statement,NULL)==SQLITE_OK){
            if (sqlite3_step(statement)==SQLITE_DONE) {
                isSuccess = YES;
            }else{
                isSuccess = NO;
                NSLog(@"Failed to execute query");
            }
            
        }else{
            isSuccess = NO;
            NSLog(@"Could not parse the query: %@\n", insertSQL);
        }
        
    }else{
        isSuccess=NO;
        NSLog(@"Failed to open database");
    }
    
    sqlite3_reset(statement);
    sqlite3_close(database);
    return isSuccess;
}
-(NSMutableArray*)selectDistinct{
    BOOL isSuccess = YES;
    NSMutableArray* result = nil;
    NSMutableArray* distinctResult = nil;
    NSString* docDir;
    NSArray* dirPaths;
    
    dirPaths = NSSearchPathForDirectoriesInDomains(NSDocumentationDirectory, NSUserDomainMask, YES);
    docDir = dirPaths[0];
    
    self.databasePath = [[NSString alloc]initWithString:[docDir stringByAppendingString:@"statements.db"]];
    
    const char* dbpath = [self.databasePath UTF8String];
    
    if (sqlite3_open(dbpath, &database)==SQLITE_OK) {
        
        NSString* query = [NSString stringWithFormat:@"select * from statements"];
        
        const char* sql_stmt = [query UTF8String];
        if (sqlite3_prepare_v2(database, sql_stmt, -1, &statement, NULL)==SQLITE_OK) {
            if (sqlite3_step(statement)==SQLITE_ROW) {
                distinctResult = [NSMutableArray new];
                for(int i = 0; i< sqlite3_column_count(statement);i++)
                {
                    result = [NSMutableArray new];
                    NSString* col = [[NSString alloc]
                                     initWithUTF8String:(const char*)sqlite3_column_text(statement, i)];
                    [result addObject:col];
                }
                [distinctResult addObject:result];
            }else{
                isSuccess=NO;
                NSLog(@"Not found");
            }
        }else{
            isSuccess=NO;
            NSLog(@"Failed to parse query: %@", query);
        }
        
        
    }else{
        isSuccess=NO;
        NSLog(@"Failed to open database");
    }
    sqlite3_reset(statement);
    sqlite3_close(database);
    return distinctResult;
    
}

-(NSArray*)findById:(NSString*)_id{
    BOOL isSuccess = YES;
    NSMutableArray* result = nil;
    
    const char* dbpath = [self.databasePath UTF8String];
    
    if (sqlite3_open(dbpath, &database)==SQLITE_OK) {
        
        NSString* query = [NSString stringWithFormat:@"select id, verb, object from statements where id=\"%@\"", _id];
        
        const char* sql_stmt = [query UTF8String];
        if (sqlite3_prepare_v2(database, sql_stmt, -1, &statement, NULL)==SQLITE_OK) {
            if (sqlite3_step(statement)==SQLITE_ROW) {
                
                result = [NSMutableArray new];
                NSString* actor = [[NSString alloc]initWithUTF8String:(const char*)sqlite3_column_text(statement, 0)];
                NSString* verb = [[NSString alloc]initWithUTF8String:(const char*)sqlite3_column_text(statement, 1)];
                NSString* object = [[NSString alloc]initWithUTF8String:(const char*)sqlite3_column_text(statement, 2)];
                
                [result addObject:actor];
                [result addObject:verb];
                [result addObject:object];
                
            }else{
                isSuccess=NO;
                NSLog(@"Not found");
            }
        }else{
            isSuccess=NO;
            NSLog(@"Failed to parse query: %@", query);
        }
        
        
    }else{
        isSuccess=NO;
        NSLog(@"Failed to open database");
    }
    
    sqlite3_reset(statement);
    sqlite3_close(database);
    return result;
}

@end
