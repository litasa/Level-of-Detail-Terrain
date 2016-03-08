#version 420 core

out VS_OUT
{
    vec2 tc;
} vs_out;

uniform int numPatches = 64;
uniform int patchesPowof2 = 6;
 
void main(void)
{
    const vec4 vertices[] = vec4[](vec4(-0.5, 0.0, -0.5, 1.0),
                                   vec4( 0.5, 0.0, -0.5, 1.0),
                                   vec4(-0.5, 0.0,  0.5, 1.0),
                                   vec4( 0.5, 0.0,  0.5, 1.0));

    int x = gl_InstanceID & (numPatches -1); // only returns the rest term when divided with 63. example: 66 & 63 = 2 NOTE: when gl_instance is a number multiplied with 64 result is 0
    int y = gl_InstanceID >> patchesPowof2; //right shift, returns the y component with same idea as above (ish)
    vec2 offs = vec2(x, y);
 
    vs_out.tc = (vertices[gl_VertexID].xz + offs + vec2(0.5)) / numPatches;
    gl_Position = vertices[gl_VertexID] + vec4( float(x - 32),
												0.0,
                                                float(y - 32),
												0.0);
}