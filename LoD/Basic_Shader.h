#pragma once
#include "Shader.h"

class Basic_Shader :
	public Shader
{
public:
	Basic_Shader(const std::string& filePath);
	~Basic_Shader();
	void UpdateValues(const Transform & transform, const Camera & camera) override;
};

