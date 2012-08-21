//
//  BasicTypes.h
//  Renderer
//
//  Created by Benjamin Gregorski on 11/14/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef Renderer_BasicTypes_h
#define Renderer_BasicTypes_h

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

struct vec3 {
    float v[3];
};

typedef struct vec3 vec3;
typedef struct vec4 ProjPointF;
typedef struct vec3 PointF;
typedef struct vec3 VectorF;

struct Color {
    float c[4];
};

typedef struct Color Color;

struct Quat {
    float q[4];
};

typedef struct Quat Quat;

struct Ray {
    PointF pos;
    VectorF dir;
};

typedef struct Ray Ray;

struct Matrix {
    vec4 m[4];
};

typedef struct Matrix Matrix;

struct Pixel {
    float p[4];
};

typedef struct Pixel Pixel;


#endif
