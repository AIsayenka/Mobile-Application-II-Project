//
//  StatementsTVC.m
//  Mobile Application II Project
//
//  Created by Kirill Aliaev on 2015-04-09.
//  Copyright (c) 2015 COMP3097. All rights reserved.
//

#import "StatementsTVC.h"
#import "DBManager.h"
#import "StatementViewController.h"

@interface StatementsTVC ()

@end

@implementation StatementsTVC

DBManager *dbm;

- (void)viewDidLoad {
    [super viewDidLoad];
    self.title = @"Statements";
    // Uncomment the following line to preserve selection between presentations.
    //self.clearsSelectionOnViewWillAppear = YES;
    
   
    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
    // self.navigationItem.rightBarButtonItem = self.editButtonItem;
    
}


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
#warning Incomplete method implementation.
    // Return the number of rows in the section.
    dbm = [DBManager new];
    _list = [dbm selectDistinct];
    return [_list count];
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *CellIdentifier = @"Cell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier forIndexPath:indexPath];
    // Configure the cell...
    
    self.statement = [self.list objectAtIndex:[indexPath row]];
    
    [cell.textLabel setText:[self.statement objectAtIndex:1]];
    cell.textLabel.font = [UIFont italicSystemFontOfSize:12.0f];
    cell.detailTextLabel.font = [UIFont boldSystemFontOfSize:10.0f];
    [cell.detailTextLabel setText:[self.statement objectAtIndex:3]];
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    self.desc = [[_list objectAtIndex:[indexPath row]] objectAtIndex:0];
    
    // Perform Segue
    [self performSegueWithIdentifier:@"Statement" sender:self];
}

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender{
    if ([segue.destinationViewController isKindOfClass:[StatementViewController class]]) {
        [(StatementViewController*)segue.destinationViewController setDesc:self.desc];
    }
}


@end
