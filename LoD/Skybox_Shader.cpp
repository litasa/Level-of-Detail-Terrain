#include "Skybox_Shader.h"

Skybox_Shader::Skybox_Shader(const std::string & filePath) : Basic_Shader(filePath)
{
	Use();
	AddUniform("cubeMap");
	glUniform1i(UnifLoc("cubeMap"), 0);
	UnUse();
}

Skybox_Shader::~Skybox_Shader()
{
}