//#version 120
#version 330 core
#pragma debug(on)

#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_explicit_uniform_location : enable

#define saturate(a) clamp(a, 0, 1)

//uniform sampler2D qt_Texture0;
//varying vec4 qt_TexCoord0;
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 fwdNormal;
layout(location = 2) in vec3 lightPosition;
layout(location = 20) uniform vec3 cameraPosition;
layout(location = 30) uniform float secElapsed;

out vec3 fragColor;
//varying vec3 fwdNormal;

// functions declarations -->
float getLightIntensity();

vec3 getDiffuseColor();
vec3 getSpecularColor();
// <-- functions

// variables -->
vec3 LightColor = vec3(1, 1, 1);
float LightIntensity = 1;
float LightRange = 100;
float LightRange2 = LightRange * LightRange;

vec3 cameraPos = cameraPosition;
vec3 normal = normalize(fwdNormal);
vec3 lightToPosition = normalize(position - lightPosition);
vec3 cameraToPosition = normalize(position - cameraPos);
vec3 lightToCamera = normalize(cameraPos - lightPosition);

float distanceIntensity = getLightIntensity();
// <-- variables

void main()
{
    vec3 resultColor = vec3(0, 0, 0);
    vec3 ambientColor = vec3(0.1, 0.1, 0.1);

    vec3 diffuseColor = getDiffuseColor();
    vec3 specularColor = getSpecularColor();

//    resultColor += ambientColor;
    resultColor += diffuseColor;
    resultColor += specularColor;
    resultColor = saturate(resultColor);

    fragColor = resultColor;
}

float getLightIntensity()
{
    float intensity = distance(position, lightPosition);
    intensity = saturate(1 - intensity * intensity / LightRange2);
    intensity *= intensity;

    //    intensity = 1 / (1.0 + LightA * intensity + LightB * intensity * intensity);

    return intensity;
}

vec3 getDiffuseColor()
{
    vec3 diffuseColor = vec3(0, 0, 0);

    vec3 MatDiffuseColor = vec3(.7, .7, .7);

    float lightIntensity = LightIntensity * distanceIntensity;
    float dotNormalLight = dot(normal, -lightToPosition);

    float lightDiffusePower = dotNormalLight * lightIntensity;

    diffuseColor = LightColor * MatDiffuseColor * lightDiffusePower;

    diffuseColor = saturate(diffuseColor);

    return diffuseColor;
}

vec3 getSpecularColor()
{
    vec3 specularColor = vec3(0, 0, 0);

    vec3 MatSpecularColor = vec3(.7, .7, .0);
    float MatSpecularHardness = 500;

    vec3 reflectedLight = reflect(lightToPosition, normal);

    float cameraPosition_ReflectedLightToPosition_Dot = -dot(cameraToPosition, reflectedLight);
    cameraPosition_ReflectedLightToPosition_Dot = saturate(cameraPosition_ReflectedLightToPosition_Dot);

    float angle = cameraPosition_ReflectedLightToPosition_Dot;

    float specularPower = pow(angle, MatSpecularHardness);

    specularColor = MatSpecularColor * LightColor;
    specularColor *= specularPower;
    specularColor *= distanceIntensity;

    specularColor = saturate(specularColor);

    return specularColor;
}
