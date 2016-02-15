#pragma once
#include "Basic_Shader.h"

class Skybox_Shader :
	public Basic_Shader
{
public:
	Skybox_Shader(const std::string& filePath);
	~Skybox_Shader();

	//void UpdateValues(const Transform& transform, const Camera& camera); Should use Basic_Shaders
};

