//
//  SOCreateGeoArgs.h
//  Renderer
//
//  Created by Benjamin Gregorski on 10/27/13.
//
//

#ifndef __Renderer__SOCreateGeoArgs__
#define __Renderer__SOCreateGeoArgs__

#include <unordered_map>
#include <bitset>

namespace Framework {
    
    enum SOCreateGeoFlags {
        CREATE_GEO_TEX_COORD = 0,   // Basic (u,v)
        CREATE_GEO_NORMALS,         // (x,y,z) normal
        CREATE_GEO_SHARED_NORMALS,  // One normal per-vertex instead of
        CREATE_GEO_TANGENTS,
        CREATE_GEO_SHARED_TANGENTS,
        
        TESSELATION_STYLE_UNIFORM,
        TESSELATION_STYLE_ADAPTIVE,
    };
    
    enum SOCreateGeoTessFactor {
        CREATE_GEO_TESS_FACTOR_U = 0,
        CREATE_GEO_TESS_FACTOR_V = 1,
        CREATE_GEO_TESS_FACTOR_W = 2,
        
        NUM_CREATE_GEO_TESS_FACTORS
    };
    
    /**
     * The SOCreateGeoArgs is used to control how a SceneObject
     * creates its own geometry when SceneObject::createGeo is called.
     *
     * The parameters can be object-specific so consult the documentation for
     * an object's createGeo() method.
     *
     */
    class SOCreateGeoArgs {
        
    public:
        SOCreateGeoArgs();
        ~SOCreateGeoArgs();
        
        bool getFlag(const SOCreateGeoFlags f) const { return m_flags.test(int(f)); }
        
        void setFlag(const SOCreateGeoFlags f) { m_flags.set(int(f), true); }
        void unsetFlag(const SOCreateGeoFlags f) { m_flags.set(int(f), false); }
        
        unsigned int getTessFactor(const SOCreateGeoTessFactor tessFactor) const;
        
        /**
         * For parameerized objects, set the tesselation in the (u,v,w) directions.
         */
        void setTessFactors(const unsigned int uTess, const unsigned int vTess = 1, const unsigned int wTess = 1);
        
    private:
        std::bitset<32> m_flags;
        
        unsigned int m_tessFactors[NUM_CREATE_GEO_TESS_FACTORS];
    };
    
}

#endif /* defined(__Renderer__SOCreateGeoArgs__) */
