//
//  ConfigManager.h
//  Renderer
//
//  Created by Benjamin Gregorski on 10/5/13.
//
//

#import <Foundation/Foundation.h>

@interface ConfigManager : NSObject

/**
 * Get a global instance of the ConfigManager
 */
+(ConfigManager*) instance;

/**
 * Save config variables:
 *  LiveViewOptions : serialize under "LiveViewOptions" key.
 *
 */
- (BOOL) saveConfigs;

/**
 * Restore config variables;
 *  LiveViewOptions : restore singleton instance.
 */
- (BOOL) loadConfigs;

@end
