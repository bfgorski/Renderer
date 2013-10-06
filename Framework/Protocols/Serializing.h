//
//  Serializing.h
//  Renderer
//
//  Created by Benjamin Gregorski on 10/5/13.
//
//

#import <Foundation/Foundation.h>

@protocol Serializing <NSObject>

- (BOOL) serializeToFile:(NSString*)file;

@end
