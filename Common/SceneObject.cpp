//
//  SceneObject.cpp
//  Renderer
//
//  Created by Benjamin Gregorski on 11/14/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "SceneObject.h"

namespace Framework {
    
SceneObject::SceneObject() : m_name("")
{
}

SceneObject::~SceneObject() {}

SceneObject::SceneObject(const SceneObject& s) : m_name(s.m_name), m_pos(s.m_pos) {}

SceneObject::SceneObject(const char * name)
: m_name(name)
{
}

SceneObject& SceneObject::operator=(const Framework::SceneObject & s) {
    if (this == &s) {
        return (*this);
    }
    
    m_name = s.m_name;
    m_pos = s.m_pos;
    return (*this);
}
    
}

