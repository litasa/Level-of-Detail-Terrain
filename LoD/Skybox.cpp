#include "Skybox.h"
#include <iostream>

Skybox::Skybox()
{

}

Skybox::~Skybox()
{
	delete m_cubemap;
	delete m_box;
	delete m_shader;
}

bool Skybox::SkyboxInit(
	const std::string& directory,
	const std::string& front,
	const std::string& back,
	const std::string& left,
	const std::string& right,
	const std::string& top,
	const std::string& bottom)
{
	m_cubemap = new CubemapTexture(
		directory,
		front,
		back,
		left,
		right,
		top,
		bottom);
	if (!m_cubemap->Load())
	{
		return false;
	}
	m_box = new Mesh("./models/box.obj");
	m_shader = new Skybox_Shader("./shaders/skybox");
	return true;

}

void Skybox::Use()
{
	m_cubemap->Bind(GL_TEXTURE0);
}

void Skybox::Draw(Transform& trans, Camera& cam)
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	Use(); //enable cubemap
	m_shader->Use();
	m_shader->UpdateValues(trans, cam);
	m_box->Draw();
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}
