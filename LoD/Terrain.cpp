#include "Terrain.h"



Terrain::Terrain(const std::string& filePath)
{
	loadShaders();
	generateVAO(filePath);
}


Terrain::~Terrain()
{
}

void Terrain::loadShaders()
{
	m_shader.LoadFromFile(GL_VERTEX_SHADER, "./shaders/terrain/terrain.vert");
	m_shader.LoadFromFile(GL_FRAGMENT_SHADER, "./shaders/terrain/terrain.frag");
	m_shader.LoadFromFile(GL_TESS_CONTROL_SHADER, "./shaders/terrain/terrain.tesscont");
	m_shader.LoadFromFile(GL_TESS_EVALUATION_SHADER, "./shaders/terrain/terrain.tesseval");

	m_shader.CreateAndLinkProgram();

	m_shader.AddUniform("mv_matrix");
	m_shader.AddUniform("mvp_matrix");
	m_shader.AddUniform("proj_matrix");
	m_shader.AddUniform("dmap_depth");
	m_shader.AddUniform("enable_fog");
}

void Terrain::generateVAO(const std::string& filePath)
{
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glPatchParameteri(GL_PATCH_VERTICES, 4);

	glEnable(GL_CULL_FACE);
	m_heightmap.Load(filePath);
}

void Terrain::Draw(const Transform & transform, const Camera & camera)
{
	m_shader.Use();
	glm::mat4 mv_matrix = transform.GetMatrix()*camera.GetViewMatrix();
	glm::mat4 mvp_matrix = camera.GetProjectionMatrix()*mv_matrix;
	glUniformMatrix4fv(m_shader("mv_matrix"), 1, GL_FALSE, &mv_matrix[0][0]);
	glUniformMatrix4fv(m_shader("proj_matrix"), 1, GL_FALSE, &camera.GetProjectionMatrix()[0][0]);
	glUniformMatrix4fv(m_shader("mvp_matrix"), 1, GL_FALSE, &mvp_matrix[0][0]);

	glUniform1f(glGetUniformLocation(m_shader.getProgram(), "dmap_depth"), 6.0f);
	glUniform1i(glGetUniformLocation(m_shader.getProgram(), "enable_fog"), 0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glDrawArraysInstanced(GL_PATCHES, 0, 4, 64 * 64);
}