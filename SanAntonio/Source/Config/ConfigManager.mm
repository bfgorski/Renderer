//
//  ConfigManager.m
//  Renderer
//
//  Created by Benjamin Gregorski on 10/5/13.
//
//

#import "ConfigManager.h"
#import "LiveViewOptions.h"

static NSString * CONFIG_FILE = @"Configuration";
static NSString * LIVE_VIEW_OPTIONS = @"LiveViewOptions";

@implementation ConfigManager

+(ConfigManager*) instance {
    static ConfigManager * configManager;
    static dispatch_once_t once;
    
    dispatch_once(&once, ^{
        configManager = [[ConfigManager alloc] init];
    });
    return configManager;
}

/**
 * Initialize a new Config
 */
- (ConfigManager*) init {
    self = [super init];
    return self;
}

- (NSURL*)getOrCreateFileURL {
    NSFileManager*fm = [NSFileManager defaultManager];
    NSArray *dirUrls = [fm URLsForDirectory:NSApplicationSupportDirectory inDomains:NSUserDomainMask];
    
    if (0 == [dirUrls count]) {
        return nil;
    }
    
    NSURL *baseURL = [dirUrls objectAtIndex:0];
    NSString* appBundleID = [[NSBundle mainBundle] bundleIdentifier];
    NSURL *appDirectory = [baseURL URLByAppendingPathComponent:appBundleID];
    NSURL *finalURL = [appDirectory URLByAppendingPathComponent:CONFIG_FILE isDirectory:NO];
    NSString *finalPath = [finalURL path];
    NSError *error;
    
    if (![fm fileExistsAtPath:finalPath]) {
        BOOL dirCreateResult = [fm createDirectoryAtURL:appDirectory withIntermediateDirectories:YES attributes:nil error:&error];
        BOOL fileCreateResult = [fm createFileAtPath:[finalURL path] contents:[NSData data] attributes:nil];
        
        if (!dirCreateResult || !fileCreateResult || error) {
            return nil;
        }
    }
   
    return finalURL;
}

- (BOOL) saveConfigs {
    NSURL *url = [self getOrCreateFileURL];
    
    if (url) {
        /*
         * Archive user settings and store in Application Support.
         */
        NSMutableData *data = [NSMutableData data];
        NSKeyedArchiver *archiver = [[NSKeyedArchiver alloc] initForWritingWithMutableData:data];
        
        [archiver encodeObject:[LiveViewOptions instance] forKey:LIVE_VIEW_OPTIONS];
        [archiver finishEncoding];
        
        NSError *error;
        BOOL result = [data writeToURL:url options:NSDataWritingAtomic error:&error];
        return (result && !error);
        
        /*NSLog(@"%@ %d %d %d %d %@\n",
              [finalURL description],
              [finalURL isFileURL],
              [fm fileExistsAtPath:[finalURL path]],
              result, createResult,
              [error description]
              );*/
    }
    return NO;
}

- (BOOL) loadConfigs {
    NSURL *url = [self getOrCreateFileURL];
    
    if (url) {
        NSData *data = [[NSFileManager defaultManager] contentsAtPath:[url path]];
        
        if (data && [data isKindOfClass:[NSData class]] && ([data length] > 0)) {
            NSKeyedUnarchiver *unArchiver = [[NSKeyedUnarchiver alloc] initForReadingWithData:data];
            
            id liveOptions = [unArchiver decodeObjectForKey:LIVE_VIEW_OPTIONS];
            
            if ([liveOptions isKindOfClass:[LiveViewOptions class]]) {
                [[LiveViewOptions instance] initWithViewOptions:liveOptions];
            } else {
                NSLog(@"Object Type %@\n", [[liveOptions class] description]);
            }
        }
        
        return YES;
    }
    return NO;
}


@end
