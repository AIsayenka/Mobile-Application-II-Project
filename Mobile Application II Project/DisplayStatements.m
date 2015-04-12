//
//  DisplayStatements.m
//  Mobile Application II Project
//
//  Created by Kirill Aliaev on 2015-04-05.
//  Copyright (c) 2015 COMP3097. All rights reserved.
//

#import "DisplayStatements.h"
#import "Statement.h"
#import "Statements.h"
#import "DBManager.h"

@implementation DisplayStatements

DBManager *dbm;

-(void)loadJSON{
    
    NSError *err = nil;
    
    NSString *dataPath = [[NSBundle mainBundle] pathForResource:@"arrayList" ofType:@"json"];
    
    NSLog(@"JSON Path: %@", dataPath);
    
    NSDictionary* json = [NSJSONSerialization JSONObjectWithData:[NSData dataWithContentsOfFile:dataPath] options:kNilOptions error:&err];
    
    NSArray* statements = [json objectForKey:@"statements"];
    _stmnts = [Statements new];
    dbm = [DBManager new];
    
    _stmnts.stm = [[NSMutableArray alloc] init];
    NSMutableArray* temp = [[NSMutableArray alloc] init];
    if([dbm createDB]){
        NSLog(@"Db OK");
    }
    
    for (int i = 0; i < statements.count; i++) {
        NSDictionary* statement = [statements objectAtIndex:i];
        _s = [Statement new];
        for(NSString *key in [statement allKeys]){
            if([key isEqualToString:@"id"]){
                _s._id = [statement objectForKey:key];
            }else if ([key isEqualToString:@"authority"]){
                _s.actor = [[statement objectForKey:@"authority"] objectForKey:@"name"];
            }else if ([key isEqualToString:@"verb"]){
                _s.verb = [[[statement objectForKey:@"verb"] objectForKey:@"display"] objectForKey:@"en-US"];
            }else if ([key isEqualToString:@"object"]){
                _s.object = [[[[statement objectForKey:@"object"] objectForKey:@"definition"] objectForKey:@"description"] objectForKey:@"en-US"];
            }else if ([key isEqualToString:@"location"]){
                _s.longitude = [[statement objectForKey:@"location"] objectForKey:@"longitude"];
                _s.latitude = [[statement objectForKey:@"location"] objectForKey:@"latitude"];
            }
        }
        [temp addObject:_s];
        // NSLog(@"Statement list: %@", statement);
        NSLog(@"Id: %@", _s._id);
        NSLog(@"Actor: %@", _s.actor);
        NSLog(@"Verb: %@", _s.verb);
        NSLog(@"Object: %@", _s.object);
        NSLog(@"Longitude: %@", _s.longitude);
        NSLog(@"Latitude: %@", _s.latitude);
        if ([dbm saveData:_s._id actor:_s.actor verb:_s.verb object:_s.object longitude:_s.longitude
                 latitude:_s.latitude]){
            NSLog(@"Db save success");
        }
        
    }
    [_stmnts setStm:temp];

}

@end
