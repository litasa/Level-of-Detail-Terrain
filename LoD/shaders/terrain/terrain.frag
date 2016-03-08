#version 420 core

out vec4 color;

layout (binding = 1) uniform sampler2D tex_color;

in TES_OUT
{
    vec2 tc;
    vec3 world_coord;
    vec3 eye_coord;
} fs_in;

void main(void)
{
    vec4 landscape = texture(tex_color, fs_in.tc);

    color = landscape;
}
