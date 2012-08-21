//
//  Sphere.cpp
//  Renderer
//
//  Created by Benjamin Gregorski on 6/23/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Sphere.h"

using namespace Framework;

Sphere::Sphere() : m_radius(1.0)
{
    m_pos[0] = m_pos[1] = m_pos[2] = 0;
}

Sphere::Sphere(const Sphere& s) : m_radius(s.m_radius), m_pos(s.m_pos)
{
}

Sphere& Sphere::operator=(<#const Framework::Sphere &#>s)
{
    if (this == &s) {
        return (*this);
    }
    m_radius = s.m_radius;
    m_pos = s.m_pos;
    return (*this);
}
                          

Sphere::~Sphere()
{
}