//
//  Shader.fsh
//  SanAntonio
//
//  Created by Benjamin Gregorski on 9/7/13.
//
//

varying lowp vec4 colorVarying;

void main()
{
    gl_FragColor = colorVarying;
}
