//
//  SOCreateGeoArgs.cpp
//  Renderer
//
//  Created by Benjamin Gregorski on 10/27/13.
//
//

#include "SOCreateGeoArgs.h"

namespace Framework {
    SOCreateGeoArgs::SOCreateGeoArgs() : m_flags() {
        for (int i = 0; i < NUM_CREATE_GEO_TESS_FACTORS; ++i) {
            m_tessFactors[i] = 1;
        }
    }
    
    SOCreateGeoArgs::~SOCreateGeoArgs() {}
    
    unsigned int SOCreateGeoArgs::getTessFactor(const Framework::SOCreateGeoTessFactor tessFactor) const {
        return m_tessFactors[int(tessFactor)];
    }
    
    void SOCreateGeoArgs::setTessFactors(const unsigned int uTess,  const unsigned int vTess, const unsigned int wTess) {
        m_tessFactors[int(CREATE_GEO_TESS_FACTOR_U)] = uTess;
        m_tessFactors[int(CREATE_GEO_TESS_FACTOR_V)] = vTess;
        m_tessFactors[int(CREATE_GEO_TESS_FACTOR_W)] = wTess;
    }
}