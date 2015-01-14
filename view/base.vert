//#version 150 core
#version 120
#pragma debug(on)
//#extension GL_ARB_separate_shader_objects : enable
//#extension GL_ARB_vertex_buffer_object : enable
//#extension GL_ARB_shader_objects : enable

attribute vec3 position;
//layout(location = 0) in vec3 vPosition;
attribute vec3 normal;
attribute vec2 uv;
//uniform mat4 modelViewProjectionMatrix;
//varying vec4 qt_TexCoord0;

//varying vec3 fwdNormal;

void main()
{
//    gl_Position = vec4(position, 1);
    gl_Position = gl_ModelViewProjectionMatrix * vec4(position, 1);
//    fwdNormal = gl_NormalMatrix * normal;
//    fwdNormal = normal;
    //gl_Color = position;
//    gl_Position = vec4(position, 0);
//    qt_TexCoord0 = qt_MultiTexCoord0;
}

//#version 150 core
//#extension GL_ARB_separate_shader_objects : enable
////#extension GL_ARB_explicit_attrib_location : require

//layout(location = 0) in vec3 position;
////layout(location = 0) in vec4 position;
