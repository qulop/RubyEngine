#version 330 core

in vec3 fragmentColor;
in vec2 fragmentTextureCoords;

out vec4 fragColor;

uniform sampler2D resTexture;
uniform vec3 col;

void main()
{
    // fragColor = texture(resTexture, fragmentTextureCoords);
    fragColor = vec4(col, 1.0f);
}