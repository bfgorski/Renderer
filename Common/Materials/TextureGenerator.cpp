//
//  TextureGenerator.cpp
//  Renderer
//
//  Created by Benjamin Gregorski on 10/24/13.
//
//

#include "TextureGenerator.h"

namespace Framework { namespace Texture {
    
    void genCheckerColorTexture(
        const Framework::Color& c0,
        const Framework::Color& c1,
        const int textureWidth,
        const int textureHeight,
        const int widthTileSize,
        const int heightTileSize,
        void * buffer,
        const TextureFormat format
    ) {
        char * pixels = reinterpret_cast<char*>(buffer);
        
        for (int row = 0; row < textureWidth; ++row) {
            // integer divide, even is c0, odd is c1
            int rowBlock = (row/heightTileSize) & 0x1;
            
            for (int col = 0; col < textureHeight; ++col, (pixels += 4)) {
                // determine color of pixel
                int colBlock = (col/widthTileSize) & 0x1;
                
                // (rowBlock,colBlock) can be 00, 01, 10, 11
                // 00 = c0, 01 = c1, 10 = c1, 11 = c0
                // exclusive or to determne color
                if ((rowBlock ^ colBlock)) {
                    c0.toBytes(pixels);
                } else {
                    c1.toBytes(pixels);
                }
            }
        }
        
    }
}
}
