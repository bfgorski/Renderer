//
//  SceneObject.cpp
//  Renderer
//
//  Created by Benjamin Gregorski on 11/14/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "SceneObject.h"
#include "Material.h"
#include "PolygonMesh.h"

namespace Framework {
    
SceneObject::SceneObject() : m_name(""), m_pos(), m_material(nullptr), m_polygonMesh(nullptr)
{
}

SceneObject::~SceneObject() {
    if (m_material) {
        delete m_material;
    }
    
    if (m_polygonMesh) {
        delete m_polygonMesh;
    }
}

SceneObject::SceneObject(const SceneObject& s) : m_name(s.m_name), m_pos(s.m_pos) {}

SceneObject::SceneObject(const char * name)
: m_name(name), m_pos(), m_material(nullptr), m_polygonMesh(nullptr)
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
 
void SceneObject::applyTransform(const Math::Transform &t) {
    m_pos = t.applyToPoint(m_pos);
}
    
PolygonMesh& SceneObject::createPolygonMesh() {
    if (m_polygonMesh) {
        delete m_polygonMesh;
    }
    
    m_polygonMesh = new PolygonMesh();
    return (*m_polygonMesh);
}
    
}

