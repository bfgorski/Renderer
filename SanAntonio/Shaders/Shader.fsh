//
//  Shader.fsh
//  SanAntonio
//
//  Created by Benjamin Gregorski on 9/7/13.
//
//

highp float calcFalloff(highp vec3 pos, highp vec3 N, highp vec3 lightPos, highp vec4 lightingModel) {
    highp vec3 L = (lightPos - pos);
    L = normalize(L);
    
    highp float zeroPoint = lightingModel.x;
    highp float intensity = max(0.0,dot(N,L));
    highp float slope = 1.0/(1.0 - zeroPoint);
    highp float offset = -zeroPoint*slope;
    highp float newIntensity = max(0.0,(intensity*slope + offset));
    
    return newIntensity;
}

highp vec3 calcDiffuseLighting(highp vec3 pos, highp vec3 N, highp vec4 lm) {
    highp vec3 lp0 = vec3(0.0, 0.0, 2.0);
    highp vec3 lp1 = vec3(0.0, 0.0, -2.0);
    highp vec3 lp2 = vec3(2.0, 0.0, 0.0);
    highp vec3 lp3 = vec3(-2.0, 0.0, 0.0);
    highp vec3 lp4 = vec3(0.0, 2.0, 0.0);
    highp vec3 lp5 = vec3(0.0, -2.0, 0.0);
    
    highp float lightIntensity = calcFalloff(pos,N,lp0,lm);
    lightIntensity += calcFalloff(pos,N,lp1,lm);
    lightIntensity += calcFalloff(pos,N,lp2,lm);
    lightIntensity += calcFalloff(pos,N,lp3,lm);
    lightIntensity += calcFalloff(pos,N,lp4,lm);
    lightIntensity += calcFalloff(pos,N,lp5,lm);
    
    return vec3(lightIntensity,lightIntensity,lightIntensity);
}

uniform lowp vec4 lightingModel;

/**
 * X = Standard, Y = DiffuseLighting, Z = Normal
 */
uniform highp vec4 renderingOptions;

varying highp vec4 positionVarying;
varying highp vec3 normalVarying;
varying highp vec3 vertexColor;

void main()
{
    //highp vec4 lightingModel = vec4(0.9,0.0,0.0,0.0);
    highp vec3 N = normalize(normalVarying);
    highp vec3 dl = calcDiffuseLighting(positionVarying.xyz, N, lightingModel);
    
    gl_FragColor = vec4(vertexColor*dl, 1.0);
    gl_FragColor = mix(gl_FragColor, vec4(vertexColor, 1.0), renderingOptions.yyyy);
    gl_FragColor = mix(gl_FragColor, vec4(dl, 1.0), renderingOptions.zzzz);
    gl_FragColor = mix(gl_FragColor, vec4((N*0.5 + 0.5),1.0), renderingOptions.wwww);
}
