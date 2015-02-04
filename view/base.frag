//#version 120
#version 330 core
#pragma debug(on)

#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_explicit_uniform_location : enable

#define saturate(a) clamp(a, 0, 1)
#define saturateNegative(a) clamp(a, 0, 1000000000)

//uniform sampler2D qt_Texture0;
//varying vec4 qt_TexCoord0;
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 fwdNormal;
layout(location = 2) in vec3 lighPosition;
layout(location = 20) uniform vec3 cameraPosition;

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

vec3 normal = normalize(fwdNormal);
vec3 lightToPosition = normalize(position - lighPosition);
vec3 cameraToPosition = normalize(-cameraPosition - position);

float distanceIntensity = getLightIntensity();
// <-- variables

void main()
{
    float floatToVec3 = 0;

    vec3 resultColor = vec3(0, 0, 0);
    vec3 ambientColor = vec3(0, 0, 0);

    vec3 diffuseColor = getDiffuseColor();
    vec3 specularColor = getSpecularColor();

    resultColor += diffuseColor;
    resultColor += specularColor;
    resultColor = saturate(resultColor);

    fragColor = resultColor;
}

float getLightIntensity()
{
    float distanceIntensity = distance(position, lighPosition);
    distanceIntensity = saturate(1 - distanceIntensity * distanceIntensity / LightRange2);
    distanceIntensity *= distanceIntensity;

    //    distanceIntensity = 1 / (1.0 + LightA * distanceIntensity + LightB * distanceIntensity * distanceIntensity);

    return distanceIntensity;
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
    float MatSpecularPower = 0.002;

    vec3 reflected = reflect(lightToPosition, normal);

    float rayLigthRayAngleCos = dot(cameraToPosition, reflected);
    rayLigthRayAngleCos = saturate(rayLigthRayAngleCos);

    float specularPower = pow(rayLigthRayAngleCos, 1/MatSpecularPower);

    specularColor = MatSpecularColor * LightColor;
    specularColor *= specularPower;
    specularColor *= distanceIntensity;

    specularColor = saturate(specularColor);

    return specularColor;
}
