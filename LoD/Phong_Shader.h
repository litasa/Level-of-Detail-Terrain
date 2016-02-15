#pragma once
#include "Basic_Shader.h"

class Phong_Shader :
	public Basic_Shader
{
public:
	Phong_Shader(const std::string& filePath = "./shaders/phong");
	~Phong_Shader();

	void UpdateValues(const Transform& transform, const Camera& camera) override;
};

