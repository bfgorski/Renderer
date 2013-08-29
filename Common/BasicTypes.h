//
//  BasicTypes.h
//  Renderer
//
//  Created by Benjamin Gregorski on 11/14/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef Renderer_BasicTypes_h
#define Renderer_BasicTypes_h

#include <math.h>

namespace Framework {
    
class vec3 {
    
public:
    vec3() {}
    vec3(const vec3& v1) { v[0] = v1.v[0]; v[1] = v1.v[1]; v[2] = v1.v[2]; }
    vec3(const float x, const float y, const float z) {v[0] = x; v[1] = y; v[2] = z;}
    
    float length() const { return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]); }
    void scale(const float f) { v[0]*=f; v[1]*=f; v[2]*=f; }
    void increment(const vec3& v1) { v[0] += v1.v[0]; v[1] += v1.v[1]; v[2] += v1.v[2];}
    
    float v[3];
};

enum Axes {
    XAxis = 0,
    X = 0,
    YAxis = 1,
    Y = 1,
    ZAxis = 2,
    Z = 2,
    WAxis = 3,
    W = 3
};

enum {
    Red = 0,
    R = 0,
    Green = 1,
    G = 1,
    Blue = 2,
    B = 2,
    Alpha = 3,
    A = 3
};

struct vec4 {
    float v[4];
};

typedef struct vec4 vec4;

typedef struct vec4 ProjPointF;
typedef vec3 PointF;
typedef vec3 VectorF;
typedef vec3 Normal;

/**
 * RGBA color
 */
struct Color {
    float c[4];
    
    Color() { c[0] = c[1] = c[2] = c[3] = 0; }
    Color(const Color& col) { c[0] = col.c[0]; c[1] = col.c[1]; c[2] = col.c[2]; c[3] = col.c[3]; }
    Color(const float r, const float g, const float b, const float a = 1.0f) {
        c[0] = r; c[1] = g; c[2] = b; c[3] = a;
    }
    
    Color& operator=(const Color& col) {
        if (this == &col) {
            return (*this);
        }
        
        c[0] = col.c[0];
        c[1] = col.c[1];
        c[2] = col.c[2];
        c[3] = col.c[3];
        return (*this);
    }
    
    void scale(const float s) {
        c[0] *= s; c[1] *= 2; c[2] *= s; c[3] *= s;
    }
    
    /**
     * Accumulate color channels only.
     */
    void accumulateColor(const Color& col) {
        c[0] += col.c[0]; c[1] += col.c[1]; c[2] += col.c[2];
    }
};

typedef struct Color Color;

struct Quat {
    float q[4];
};

typedef struct Quat Quat;

struct Ray {
    PointF pos;
    VectorF dir;
    
    Ray() : pos(), dir() {}
    Ray(const PointF& p, const VectorF &d) : pos(p), dir(d) {}
    
    const VectorF& getDir() const { return dir; }
    const PointF& getPos() const { return pos; }
};

typedef struct Ray Ray;

struct Matrix {
    vec4 m[4];
};

typedef struct Matrix Matrix;

struct Pixel {
    // RGBA
    Color c;
};

typedef struct Pixel Pixel;

}

#endif
