#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 textureCoords;

out vec3 fragmentColor;
out vec2 fragmentTextureCoords;

uniform float offset;

void main()
{
    gl_Position = vec4(pos.x + 10, pos.y + 10, pos.z, 1.0f);
    fragmentColor = color;
    fragmentTextureCoords = textureCoords;
}