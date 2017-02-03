#version 420 core

layout (triangles) in;
layout (line_strip, max_vertices = 3) out;

uniform sampler2D tex_displacement;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;
uniform float dmap_depth;

in TES_OUT
{
    vec2 tc;
    vec3 world_coord;
    vec3 eye_coord;
} geom_in[];

void main(void)
{
	for(int i = 0; i < 3;i++)
	{
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}
	EndPrimitive();
}