

#ifndef LIGHTING_FSH
#define LIGHTING_FSH

struct Light {
    vec4 pos;
    vec4 color;
};

Light m_lights[4];

vec3 calcDiffuseLighting(vec3 pos, vec3 normal) {
    vec3 lp0 = vec3(0.0, 0.0, 10.0);
    vec3 lp1 = vec3(0.0, 0.0, -10.0);
    vec3 lp2 = vec3(10.0, 0.0, 0.0);
    vec3 lp3 = vec3(-10.0, 0.0, 0.0);
    
    vec3 L = normalize(lp0 - pos);
    float lightIntensity = max(0.0, dot(N,L));
    
    L = normalize(lp1 - pos);
    lightIntensity += max(0.0, dot(N,L));
    
    L = normalize(lp2 - pos);
    lightIntensity += max(0.0, dot(N,L));
    
    L = normalize(lp3 - pos);
    lightIntensity += max(0.0, dot(N,L));
    
    return vec3(lightIntensity,lightIntensity, lightIntensity);
}


#endif // LIGHTING_FSH