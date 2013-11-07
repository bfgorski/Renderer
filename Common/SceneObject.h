//
//  SceneObject.h
//  Renderer
//
//  Created by Benjamin Gregorski on 11/14/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef Renderer_SceneObject_h
#define Renderer_SceneObject_h

#include <string>
#include "SOIntersection.h"
#include "Transform.h"
#include "PolygonMesh.h"

namespace Framework {

    
class Material;
class SOCreateGeoArgs;
    
class SceneObject {
    
public:
    SceneObject();
    virtual ~SceneObject();
    SceneObject(const char * name);
    
    void setName(const char * s) { m_name = s; }
    void setName(const std::string& s) { m_name = s; }
    
    /**
     * Position in 3-space.
     */
    void setPos(const PointF& p) { m_pos = p; }
    
    void setMaterial(Material* m) { m_material = m; }
    
    const std::string& getName() const { return m_name; }
    const PointF& getPos() const { return m_pos; }
    const Material* getMaterial() const { return m_material; }
    
    /**
     * Transform a SceneObject by transforming its position.
     * Object should override this and
     */
    virtual void applyTransform(const Math::Transform& t);
    
    /**
     * Determine if the indicated Ray intersects the object.
     */
    virtual SOIntersectionType intersect(const Ray& r, SOIntersection* intersectionInfo) const = 0;
    
    /**
     * Determine if the indicated Ray intersects the object
     * and get the intersection point only.
     *
     * This is intended to be a fast check for intersection.
     */
    virtual SOIntersectionType intersect(const Ray& r, PointF& intersectionPoint) const = 0;
    
    /**
     * SceneObjects that are described analytically, e.g. Box, Sphere etc. 
     * can create their own geometry for rendering, intersection etc. that
     * is stored as part of the SceneObject.
     *
     * @param args  Optional parameters for creating geometry
     */
    virtual void createGeo(const SOCreateGeoArgs* args = nullptr) {};
    
    PolygonMesh * getPolygonMesh() const { return m_polygonMesh; }
    
protected:
    
    /**
     * Delete an existing PolygonMesh and return a reference to a new one.
     */
    PolygonMesh& createPolygonMesh();
    
    std::string m_name;
    
    PointF m_pos;
    
    Material * m_material;
    
    // Bounding Box
private :

    SceneObject(const SceneObject&);
    SceneObject& operator=(const SceneObject&);
    
    /**
     * SceneObjects can create a polygon mesh (a list of triangles)
     * that represents their geometry.
     */
    PolygonMesh * m_polygonMesh;

};
    
}
#endif
