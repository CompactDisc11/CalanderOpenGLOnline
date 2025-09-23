#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 Norm;

layout (location = 2) in vec2 aTexCoord;
out vec2 TexCoord;

uniform mat4 transform;
uniform int Index;

void main()
    {
       gl_Position = transform*(vec4(aPos, 1.0));
       TexCoord = aTexCoord;
    }