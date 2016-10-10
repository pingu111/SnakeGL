#version 330

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inUv;

out vec2 uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main(void)
{
    gl_Position = proj * view * model * vec4(inPosition, 1.0);
    uv = inUv;
}
