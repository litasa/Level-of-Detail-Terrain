#include "Phong_Shader.h"
#include "glm\glm.hpp"
#include "glm\gtc\type_ptr.hpp"


Phong_Shader::Phong_Shader(const std::string& filePath)
{
	LoadFromFile(GL_VERTEX_SHADER, filePath + ".vert");
	LoadFromFile(GL_FRAGMENT_SHADER, filePath + ".frag");
	CreateAndLinkProgram();
	Use();
	AddUniform("model");
	AddUniform("view");
	AddUniform("projection");
	AddUniform("u_cameraPosition");

	AddUniform("u_lightPosition");
	AddUniform("u_lightAmbientIntensitys");
	AddUniform("u_lightDiffuseIntensitys");
	AddUniform("u_lightSpecularIntensitys");

	AddUniform("u_matAmbientReflectances");
	AddUniform("u_matDiffuseReflectances");
	AddUniform("u_matSpecularReflectances");
	AddUniform("u_matShininess");

	UnUse();
}


Phong_Shader::~Phong_Shader()
{
}

void Phong_Shader::UpdateValues(const Transform& transform, const Camera& camera)
{
	glUniformMatrix4fv(UnifLoc("projection"), 1, GL_FALSE, &camera.GetProjectionMatrix()[0][0]);
	glUniformMatrix4fv(UnifLoc("view"), 1, GL_FALSE, &camera.GetViewMatrix()[0][0]);
	glUniformMatrix4fv(UnifLoc("model"), 1, GL_FALSE, &transform.GetMatrix()[0][0]);
	glUniform3fv(UnifLoc("u_cameraPosition"), 1, glm::value_ptr(camera.GetPosition()));

	glm::vec3 light_pos = glm::vec3(1, 0, -15);
	glUniform3fv(UnifLoc("u_lightPosition"), 1, glm::value_ptr(light_pos));

	glm::vec3 ambintensity = glm::vec3(255 / 255, 105 / 255, 180 / 255);
	glm::vec3 diffuseintensity = glm::vec3(1, 1, 1);
	glm::vec3 specularintensity = glm::vec3(0, 1, 0);
	glUniform3fv(UnifLoc("u_lightAmbientIntensitys"), 1, glm::value_ptr(ambintensity));
	glUniform3fv(UnifLoc("u_lightDiffuseIntensitys"), 1, glm::value_ptr(diffuseintensity));
	glUniform3fv(UnifLoc("u_lightSpecularIntensitys"), 1, glm::value_ptr(specularintensity));

	glm::vec3 ambreflect = glm::vec3(1, 1, 1);
	glUniform3fv(UnifLoc("u_matAmbientReflectances"), 1, glm::value_ptr(ambreflect));
	glm::vec3 diffusereflect = glm::vec3(1, 1, 1);
	glUniform3fv(UnifLoc("u_matDiffuseReflectances"), 1, glm::value_ptr(diffusereflect));
	glm::vec3 specreflect = glm::vec3(1, 1, 1);
	glUniform3fv(UnifLoc("u_matSpecularReflectances"), 1, glm::value_ptr(specreflect));

	float shininess = 64;
	glUniform1f(UnifLoc("u_matShininess"), shininess);
}