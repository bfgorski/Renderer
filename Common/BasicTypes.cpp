//
//  BasicTypes.cpp
//  Renderer
//
//  Created by Benjamin Gregorski on 11/18/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "BasicTypesImpl.h"
#include <math.h>

void vec4_Normalize3(vec4& v)
{
    float len = sqrt(v.v[X]*v.v[X] + v.v[Y]*v.v[Y] + v.v[Z]*v.v[Z]);
    len = 1.0f/len;
    v.v[X] *= len;
    v.v[Y] *= len;
    v.v[Z] *= len;
}