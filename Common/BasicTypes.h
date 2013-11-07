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
#include "MathUtils.h"

namespace Framework {
    
class vec3 {
    
public:
    vec3() { v[0] = v[1] = v[2] = 0; }
    vec3(const vec3& v1) { v[0] = v1.v[0]; v[1] = v1.v[1]; v[2] = v1.v[2]; }
    vec3(const float x, const float y, const float z) {v[0] = x; v[1] = y; v[2] = z;}
    
    void set(const float x, const float y, const float z) {
        v[0] = x; v[1] = y; v[2] = z;
    }
    
    float x() const { return v[0]; }
    float y() const { return v[1]; }
    float z() const { return v[2]; }
    
    float length() const { return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]); }
    void scale(const float f) { v[0]*=f; v[1]*=f; v[2]*=f; }
    void increment(const vec3& v1) { v[0] += v1.v[0]; v[1] += v1.v[1]; v[2] += v1.v[2];}
    
    void normalize() {
        float l = 1.0/length();
        scale(l);
    }
    
    void clamp(const float f) {
        for (int i = 0; i < 3; ++i) {
            if (fabs(v[i]) < f) {
                v[i] = 0;
            }
        }
    }
    
    bool isZero() const { return (0.0 == v[0] && 0.0 == v[1] && 0.0 == v[2]); }
    
    float v[3];
};

enum AngleType {
    RADIANS = 0,
    DEGREES = 1,
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

struct vec2 {
    float v[2];
};
    
typedef struct vec2 vec2;
    
struct vec4 {
    void set(const float x, const float y, const float z, const float w) {
        v[0] = x; v[1] = y; v[2] = z; v[3] = w;
    }
    
    float v[4];
};

typedef struct vec4 vec4;
    
typedef vec4 ProjPointF;
typedef vec3 PointF;
typedef vec2 Point2F;
typedef vec3 VectorF;
typedef vec3 Normal;
typedef vec3 Tangent;
typedef vec2 TexCoord2;
typedef vec3 TexCoord3;
typedef vec4 TexCoord4;
    
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
    
    /**
     * Scale RGB not A.
     * 
     * @param float s Scale factor for RGB components.
     */
    void scale(const float scale) {
        c[0] *= scale; c[1] *= scale; c[2] *= scale;
    }
    
    /**
     * Accumulate color channels only.
     */
    void accumulateColor(const Color& col) {
        c[0] += col.c[0]; c[1] += col.c[1]; c[2] += col.c[2];
    }
    
    /**
     * Convert color range from [0,1] to [0,255]
     */
    void toBytes(char * b) const {
        b[0] = Math::toByte(c[0], 0.0, 1.0);
        b[1] = Math::toByte(c[1], 0.0, 1.0);
        b[2] = Math::toByte(c[2], 0.0, 1.0);
        b[3] = Math::toByte(c[3], 0.0, 1.0);
    }
};

typedef struct Color Color;

struct Ray {
    PointF pos;
    VectorF dir;
    
    Ray() : pos(), dir() {}
    Ray(const Ray& r) : pos(r.pos), dir(r.dir) {}
    Ray(const PointF& p, const VectorF &d) : pos(p), dir(d) {}
    
    const VectorF& getDir() const { return dir; }
    const PointF& getPos() const { return pos; }
};

typedef struct Ray Ray;
  
struct Pixel {
    // RGBA
    Color c;
};

typedef struct Pixel Pixel;

/**
 * Coordinate Frame defined by 3 vectors and a point.
 */
struct Frame {
    enum Axes { UAxis = 0, VAxis = 1, WAxis = 2 };
    
    VectorF m_u, m_v, m_w;
    PointF m_origin;
    
    Frame() : m_u(), m_v(), m_w(), m_origin() {}
    Frame(const PointF& o, const VectorF& u, const VectorF& v, const VectorF& w) : m_u(u), m_v(v), m_w(w), m_origin(o) {}
    Frame(const Frame& f) : m_u(f.m_u), m_v(f.m_v), m_w(f.m_w), m_origin(f.m_origin) {}
    
    const PointF& origin() const { return m_origin; }
    const VectorF& u() const { return m_u; }
    const VectorF& v() const { return m_v; }
    const VectorF& w() const { return m_w; }
    
    void setOrigin(const PointF& p) { m_origin = p; }
    void setU(const VectorF& u) { m_u = u; }
    void setV(const VectorF& v) { m_v = v; }
    void setW(const VectorF& w) { m_w = w; }
    
};
    
typedef struct Frame Frame;
    
}

extern const Framework::vec3 VZero;
 
#endif
