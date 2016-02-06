#version 330 core

layout(location = 0) out vec4 vFragColor;

uniform sampler2D sampler;

//input from vertex shader
smooth in vec3 uv;

void main()
{
	vFragColor = texture2D(sampler, uv.st);
}