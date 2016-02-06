#version 330 core

layout( location = 0) out vec4 vFragColor;

uniform samplerCube cubeMap;

//input from vertex shader
smooth in vec3 uv;

void main()
{
	vFragColor = texture(cubeMap,uv);
}