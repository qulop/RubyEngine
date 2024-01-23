#version 330 core

in vec2 texCoord;
out vec4 color;

uniform sampler2D tex;
uniform vec3 texColor;

void main()
{
    vec4 sampled = vec4(1.0f, 1.0f, 1.0f, texture(tex, texCoord).r);
    color = vec4(texColor, 1.0f) * sampled;
}