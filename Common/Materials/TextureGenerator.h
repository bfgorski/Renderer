//
//  TextureGenerator.h
//  Renderer
//
//  Created by Benjamin Gregorski on 10/24/13.
//
//

#ifndef __Renderer__TextureGenerator__
#define __Renderer__TextureGenerator__

#include <iostream>
#include "BasicTypes.h"

namespace Framework { namespace Texture {
    enum class TextureFormat { RGBA8 };
    
    /**
     * Generate a texture with a checker pattern,
     */
    void genCheckerColorTexture(
        const Framework::Color& c0,
        const Framework::Color& c1,
        const int textureWidth,
        const int textureHeight,
        const int widthTileSize,
        const int heightTileSize,
        void * buffer,
        const TextureFormat = TextureFormat::RGBA8
    );
}
}

#endif /* defined(__Renderer__TextureGenerator__) */
