#include "Terrain.h"



Terrain::Terrain(const std::string& heightMap, const std::string& terrainTexture)
{
	loadShaders();
	generateVAO(heightMap, terrainTexture);
	loadHeightDataToCPU();
}


Terrain::~Terrain()
{
	glDeleteVertexArrays(1, &m_vao);
}

void Terrain::loadShaders()
{
	m_shader.LoadFromFile(GL_VERTEX_SHADER, "./shaders/terrain/terrain.vert");
	m_shader.LoadFromFile(GL_FRAGMENT_SHADER, "./shaders/terrain/terrain.frag");
	m_shader.LoadFromFile(GL_TESS_CONTROL_SHADER, "./shaders/terrain/terrain.tesscont");
	m_shader.LoadFromFile(GL_TESS_EVALUATION_SHADER, "./shaders/terrain/terrain.tesseval");
	//m_shader.LoadFromFile(GL_GEOMETRY_SHADER, "./shaders/terrain/normal.geom");

	m_shader.CreateAndLinkProgram();

	m_shader.AddUniform("mv_matrix");
	m_shader.AddUniform("mvp_matrix");
	m_shader.AddUniform("proj_matrix");
	m_shader.AddUniform("dmap_depth");
}

void Terrain::generateVAO(const std::string& heightMap, const std::string& terrainTexture)
{
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glPatchParameteri(GL_PATCH_VERTICES, 4);

	glEnable(GL_CULL_FACE);
	m_heightmap.AddTexture(heightMap, 0);
	m_heightmap.AddTexture(terrainTexture, 1);
}

void Terrain::Draw(const Transform & transform, const Camera & camera)
{
	glBindVertexArray(m_vao);
	m_shader.Use();
	glm::mat4 mv_matrix = transform.GetMatrix()*camera.GetViewMatrix();
	glm::mat4 mvp_matrix = camera.GetProjectionMatrix()*mv_matrix;
	glUniformMatrix4fv(m_shader("mv_matrix"), 1, GL_FALSE, &mv_matrix[0][0]);
	glUniformMatrix4fv(m_shader("proj_matrix"), 1, GL_FALSE, &camera.GetProjectionMatrix()[0][0]);
	glUniformMatrix4fv(m_shader("mvp_matrix"), 1, GL_FALSE, &mvp_matrix[0][0]);

	glUniform1f(glGetUniformLocation(m_shader.getProgram(), "dmap_depth"), 3.0f);

	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LEQUAL);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//glDrawArraysInstanced(GL_PATCHES, 0, 4, 64 * 64);
	glDrawArraysInstanced(GL_PATCHES, 0, 4, 64 * 64);
	glBindVertexArray(0);
}

float Terrain::GetHeightAt(glm::vec3& position)
{
	//convert middle of texture into world coordinates
	glm::ivec2 tex_pos((int)(m_heightmap.Width()/2), (int)(m_heightmap.Height()/2));
	//converting to closest texture coordinate
	glm::ivec2 pos = glm::ivec2((int)position.x + tex_pos.x, (int)position.z + tex_pos.y);
	//now get the index into the texture array
	int index = pos.x + m_heightmap.Width()*pos.y;
	if (index >= 0 &&
		index < m_heightmap.Width()*m_heightmap.Height()
		)
	{
		return m_heightData[index];
	}
	return -300;
}

void Terrain::loadHeightDataToCPU()
{
	unsigned char* heightData = Texture::GetTextureData(m_heightmap);
	unsigned int index = 0;
	for (unsigned int y = 0; y < m_heightmap.Height(); y++)
	{
		for (unsigned int x = 0; x < m_heightmap.Width(); x++)
		{
			unsigned int index = x + y*m_heightmap.Width();
			float temp = (float)(heightData[index] / 255.0f);
			index += m_heightmap.NumComponents();
			m_heightData.push_back(temp);
		}
	}
	free(heightData);
}