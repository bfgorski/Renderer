//
//  Camera.m
//  Renderer
//
//  Created by Benjamin Gregorski on 11/15/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import "Camera.h"
#import "BasicTypes.h"
#import "BasicTypesImpl.h"
#import "Transform.h"

using namespace Framework;

static const float DEFAULT_FOCAL_LENGTH = 10.0f;

/**
 * NSString object for encoding/decoding Camera using NSCoding
 */
static NSString *CAMERA_NAME = @"Name";
static NSString *NEAR_PLANE = @"NearPlane";
static NSString *FAR_PLANE = @"FarPlane";
static NSString *FIELD_OF_VIEW = @"FOV";
static NSString *ASPECT_RATIO = @"AspectRatio";
static NSString *POS_DIR = @"PosDir";
static NSString *UP = @"Up";
static NSString *FOCAL_POINT = @"FocalPoint";

@implementation Camera
{
}

@synthesize posDir = m_posDir;
@synthesize focalPoint = m_focalPoint;
@synthesize up = m_up;

-(void) setDefaultFocalPoint
{
    // set focal point in front of positions along view direction.
    m_focalPoint = Math::vec3AXPlusB(self.posDir.dir, DEFAULT_FOCAL_LENGTH, self.posDir.pos);
}

-(Camera*) init
{
    self = [super init];
    
    if (!self) {
        return self;
    }
    
    [self setFov:45];
    [self setAspectRatio:(1920.0f/1080.0f)];
   
    PointF p(0,0,0);
    VectorF v; 
    v.v[0] = v.v[1] = 0;
    v.v[2] = 1;
    
    Ray r;
    r.pos = p;
    r.dir = v;
    [self setPosDir:r];
    
    [self setDefaultFocalPoint];
    return self;
}

-(Camera*) initWithRay:(Ray)r upV:(VectorF)upV Fov:(float)fov AspectRatio:(float)ar nearPlane:(float)nearPlane farPlane:(float)farPlane
{
    self = [super init];
    
    if (!self) {
        return self;
    }
    
    [self setPosDir:r];
    self.up = upV;
    [self setAspectRatio:ar];
    [self setFov:fov];
    self.nearPlane = nearPlane;
    self.farPlane = farPlane;
    [self setDefaultFocalPoint];
    
    return self;
}

- (void) copyFromCamera:(Camera *)c
{
    self.nearPlane = c.nearPlane;
    self.farPlane = c.farPlane;
    self.fov = c.fov;
    self.aspectRatio = c.aspectRatio;
    self.posDir = c.posDir;
    self.up = c.up;
    self.focalPoint = c.focalPoint;
    self.up = c.up;
}

-(void) setPos: (PointF) p
{
    m_posDir.pos = p;
}

-(PointF) getPos
{
    return self.posDir.pos;
}

-(void) setDir: (VectorF) v
{
    m_posDir.dir = v;
}

-(VectorF) getDir
{
    return self.posDir.dir;
}

-(void) setPosDir: (PointF) p Dir: (VectorF) v
{
    [self setPos:p];
    [self setDir:v];
}

- (Rectangle) getNearPlane {
    // Get a quad that describes the near plane
    PointF camPos = [self getPos] ;
    
    // determine the lower left point and the scales
    // These are half angle height and width
    float height = tan(self.fov * M_PI/360.0) * self.nearPlane ;
    float width = height * self.aspectRatio;
    
    // the center of the near plane
    // the x and y increment directions
    VectorF lookAt = (self.posDir.dir);
    Math::vec3Normalize(lookAt);
    PointF center = Math::vec3AXPlusB(lookAt, self.nearPlane, camPos);
    
    VectorF yDir = self.up;
    Math::vec3Normalize(yDir);
    
    VectorF xDir = Math::cross(lookAt, self.up);
    Math::vec3Normalize(xDir);
    
    PointF lowerLeft =  Math::vec3AMinusB(center, Math::vec3AXPlusBY(xDir, width, yDir, height));
    
    Rectangle r;
    r.bottomLeft = lowerLeft;
    r.upV = yDir;
    r.rightV = xDir;
    r.upLen = height*2;
    r.rightLen = width*2;
    return r;
}

- (void) applyTransform:(Math::Transform *)t {
    self.up = t->applyToVector(self.up);
    self.focalPoint = t->applyToPoint(self.focalPoint);
    self.posDir = t->applyToRay(self.posDir);
}

- (void)encodeWithCoder:(NSCoder *)encoder {
    [encoder encodeObject:self.name forKey:CAMERA_NAME];
    [encoder encodeFloat:self.nearPlane forKey:NEAR_PLANE];
    [encoder encodeFloat:self.farPlane forKey:FAR_PLANE];
    [encoder encodeFloat:self.aspectRatio forKey:ASPECT_RATIO];
    [encoder encodeFloat:self.fov forKey:FIELD_OF_VIEW];
   
    const uint8_t *d = (const uint8_t*)&m_posDir;
    [encoder encodeBytes:d length:sizeof(Ray) forKey:POS_DIR];
    
    d = (const uint8_t*)&m_up;
    [encoder encodeBytes:d length:sizeof(VectorF) forKey:UP];
    
    d = (const uint8_t*)&m_focalPoint;
    [encoder encodeBytes:d length:sizeof(PointF) forKey:FOCAL_POINT];
    
    return;
}

- (id)initWithCoder:(NSCoder *)decoder {
    self.name = [decoder decodeObjectForKey:CAMERA_NAME];
    self.nearPlane = [decoder decodeFloatForKey:NEAR_PLANE];
    self.farPlane = [decoder decodeFloatForKey:FAR_PLANE];
    self.aspectRatio = [decoder decodeFloatForKey:ASPECT_RATIO];
    self.fov = [decoder decodeFloatForKey:FIELD_OF_VIEW];
    
    NSUInteger length;
    const uint8_t *d = [decoder decodeBytesForKey:POS_DIR returnedLength:&length];
    memcpy(&self->m_posDir, d, sizeof(Ray));
    
    d = [decoder decodeBytesForKey:UP returnedLength:&length];
    memcpy(&self->m_up, d, sizeof(VectorF));
    
    d = [decoder decodeBytesForKey:FOCAL_POINT returnedLength:&length];
    memcpy(&self->m_focalPoint, d, sizeof(PointF));
    
    return self;
}
























@end
