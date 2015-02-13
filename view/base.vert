//#version 150 core
//#version 120
#version 330 core
#pragma debug(on)

#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_explicit_uniform_location : enable

//attribute vec3 position;
//attribute vec3 normal;
//attribute vec2 uv;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

//layout(location = 10) uniform mat4 viewProjectionMatrix;
layout(location = 11) uniform mat4 modelMatrix;
layout(location = 12) uniform mat4 modelViewProjectionMatrix;
//layout(location = 20) uniform vec3 cameraPosition;
layout(location = 30) uniform float secElapsed;
//varying vec4 qt_TexCoord0;

//uniform mat4 projection;
//uniform mat4 view;
//uniform mat4 model;

//varying vec3 fwdNormals;
layout(location = 0) out vec3 fwdPosition;
layout(location = 1) out vec3 fwdNormal;
//layout(location = 1) out vec3 cameraPosition;
layout(location = 2) out vec3 fwdLightPosition;

float lightRadius = 10;
vec4 lightPosition = vec4(lightRadius * cos(secElapsed), 10, lightRadius * sin(secElapsed), 0);

void main()
{
    gl_Position = modelViewProjectionMatrix * vec4(position, 1);

    fwdNormal = (modelMatrix * vec4(normal, 0)).xyz;
    fwdPosition = (modelMatrix * vec4(position, 1)).xyz;
    fwdLightPosition = lightPosition.xyz;
}
