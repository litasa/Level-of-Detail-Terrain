#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;


uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

//position of light and camera
uniform vec3 u_lightPosition;
uniform vec3 u_cameraPosition;

//output to fragment shader
out vec3 o_normal;
out vec3 o_toLight;
out vec3 o_toCamera;
out vec2 o_texCoords;

void main(void)
{
	mat4 MVP = projection * view * model;
	gl_Position = MVP * vec4(position, 1.0);
	//world position
	vec4 worldPosition = vec4(position,1);
	
	//normal in world space
	o_normal = normalize(normal);
	o_toLight = normalize(u_lightPosition - worldPosition.xyz);
	o_toCamera = normalize(u_cameraPosition - worldPosition.xyz);
	o_texCoords = texCoord;
//	mat4 MVP = u_projection * u_view * u_model;
//	gl_Position = MVP * vec4(position, 1.0);
}