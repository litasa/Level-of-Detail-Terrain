#include "Basic_Shader.h"

Basic_Shader::Basic_Shader()
{

}

Basic_Shader::Basic_Shader(const std::string& filePath)
{
	LoadFromFile(GL_VERTEX_SHADER, filePath + ".vert");
	LoadFromFile(GL_FRAGMENT_SHADER, filePath + ".frag");
	CreateAndLinkProgram();
	Use();
	AddUniform("model");
	AddUniform("view");
	AddUniform("projection");
	UnUse();
}


Basic_Shader::~Basic_Shader()
{
}

void Basic_Shader::UpdateValues(const Transform & transform, const Camera & camera)
{
	glUniformMatrix4fv(UnifLoc("projection"), 1, GL_FALSE, &camera.GetProjectionMatrix()[0][0]);
	glUniformMatrix4fv(UnifLoc("view"), 1, GL_FALSE, &camera.GetViewMatrix()[0][0]);
	glUniformMatrix4fv(UnifLoc("model"), 1, GL_FALSE, &transform.GetMatrix()[0][0]);
}
