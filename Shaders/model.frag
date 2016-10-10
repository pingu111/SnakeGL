#version 330

in vec2 uv;

uniform int useTexture;
uniform vec3 color;
uniform sampler2D tex;

layout(location = 0) out vec3 outColor;

void main(void)
{
    if(useTexture == 1)
        outColor = texture(tex, uv).rgb;

    else
        outColor = color;
}
