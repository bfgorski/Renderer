//
//  Rectangle.h
//  Renderer
//
//  Created by Benjamin Gregorski on 7/31/13.
//
//

#ifndef Renderer_Rectangle_h
#define Renderer_Rectangle_h

#include "BasicTypes.h"

namespace Framework {
    
/*
 * A Rectangle defined by a point, two vectors and two lengths
 *
    BL + upV*upLen;
 
 
 
    BL  .....  BL+rightV*topLength
 */
struct Rectangle {
    PointF bottomLeft;
    VectorF rightV;
    VectorF upV;
    float rightLen;
    float upLen;
};

}

#endif
