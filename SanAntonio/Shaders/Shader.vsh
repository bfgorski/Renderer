//
//  Shader.vsh
//  SanAntonio
//
//  Created by Benjamin Gregorski on 9/7/13.
//
//

attribute vec4 position;
attribute vec3 normal;

varying highp vec3 normalVarying;
varying highp vec4 positionVarying;
varying highp vec3 vertexColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;

void main()
{
    highp vec3 eyeNormal = normalize(normalMatrix * normal);
    normalVarying = eyeNormal;
    positionVarying = position;
    
    // Sample cube is in -0.5,0.5
    vertexColor = position.xyz + vec3(0.5,0.5,0.5);
    
    gl_Position = modelViewProjectionMatrix * position;
}
