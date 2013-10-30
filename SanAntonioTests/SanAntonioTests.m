//
//  SanAntonioTests.m
//  SanAntonioTests
//
//  Created by Benjamin Gregorski on 9/7/13.
//
//

#import "SanAntonioTests.h"

@implementation SanAntonioTests

- (void)setUp
{
    [super setUp];
    
    // Set-up code here.
}

- (void)tearDown
{
    // Tear-down code here.
    
    [super tearDown];
}

- (void)testExample
{
    //STFail(@"Unit tests are not implemented yet in SanAntonioTests");
}

- (void)testURL
{
    NSURL *url = [NSURL URLWithString:@"http://google.com"];
    NSURLRequest *request = [NSURLRequest requestWithURL:url];
    
    NSURLResponse *response;
    NSError *error;
    [NSURLConnection sendSynchronousRequest:request returningResponse:&response error:&error];
    
    NSOperationQueue *q = [[NSOperationQueue alloc] init];
    NSBlockOperation *op = [NSBlockOperation blockOperationWithBlock:^() {
        NSURL *url = [NSURL URLWithString:@"http://google.com"];
        NSURLRequest *request = [NSURLRequest requestWithURL:url];
        
        NSURLResponse *response;
        NSError *error;
        NSData * d = [NSURLConnection sendSynchronousRequest:request returningResponse:&response error:&error];
        NSLog(@"Synchronous Request response: %@ error %@ %@ %lu\n", [response description], [error description], [q description], (unsigned long)[d length]);
    }];
   
    //https://www.google.com/search?q=c%2B%2B&oq=c%2B%2B&aqs=chrome..69i57j69i59j69i61l2j0l2.1359j0j7&sourceid=chrome&espv=210&es_sm=91&ie=UTF-8
    [op addExecutionBlock:^{
        NSURL *url = [NSURL URLWithString:@"https://www.google.com/search?q=c%2B%2B&oq=c%2B%2B&aqs=chrome..69i57j69i59j69i61l2j0l2.1359j0j7&sourceid=chrome&espv=210&es_sm=91&ie=UTF-8"];
        
        NSURLRequest *request = [NSURLRequest requestWithURL:url];
        [NSURLConnection sendAsynchronousRequest:request queue:[NSOperationQueue currentQueue] completionHandler:^(NSURLResponse *response, NSData *data, NSError *connectionError) {
             NSLog(@"Async Request response: %@ error %@ %lu\n", [response description], [connectionError description], (unsigned long)[data length]);
            
            char * d = (char*)[data bytes];
            NSLog(@"%s\n", d);
        }];
    }];
    
    [q addOperation:op];
    
    /*[NSURLConnection sendAsynchronousRequest:request
                                       queue:q
                           completionHandler:^(NSURLResponse *response, NSData *data, NSError *connectionError)
    {
        NSLog(@"Goodbye response: %@ error %@\n", [response description], [connectionError description]);
    }];*/
    
    
    sleep(60);
}

@end
