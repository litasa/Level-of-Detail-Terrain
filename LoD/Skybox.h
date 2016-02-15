#pragma once
#ifndef SKYBOX_H
#define SKYBOX_H

#include <string>
#include "Texture.h"
#include "Mesh.h"
#include "Skybox_Shader.h"

class Skybox : public Mesh
{
public:
	Skybox();
	~Skybox();

	bool SkyboxInit(
		const std::string& directory,
		const std::string& front,
		const std::string& back,
		const std::string& left,
		const std::string& right,
		const std::string& top,
		const std::string& bottom);

	void Use();

	void Draw(Transform& trans, Camera& cam);

private:
	CubemapTexture* m_cubemap;
	Mesh* m_box;
	Skybox_Shader* m_shader;
};
#endif //SKYBOX_H

