#version 420 core

out vec4 color;

layout (binding = 1) uniform sampler2D tex_color;

void main(void)
{
    color = vec4(1,1,1,0.5);
}
