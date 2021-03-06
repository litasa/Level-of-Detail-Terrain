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

	m_meshDisplay.LoadFromFile(GL_VERTEX_SHADER, "./shaders/terrain/terrain.vert");
	m_meshDisplay.LoadFromFile(GL_FRAGMENT_SHADER, "./shaders/terrain/grid_mesh.frag");
	m_meshDisplay.LoadFromFile(GL_TESS_CONTROL_SHADER, "./shaders/terrain/terrain.tesscont");
	m_meshDisplay.LoadFromFile(GL_TESS_EVALUATION_SHADER, "./shaders/terrain/terrain.tesseval");
	m_meshDisplay.LoadFromFile(GL_GEOMETRY_SHADER, "./shaders/terrain/grid_mesh.geom");

	m_meshDisplay.CreateAndLinkProgram();
	m_shader.CreateAndLinkProgram();

	m_shader.AddUniform("mv_matrix");
	m_shader.AddUniform("LOD_mvp_matrix");
	m_shader.AddUniform("proj_matrix");
	m_shader.AddUniform("dmap_depth");

	m_meshDisplay.AddUniform("mv_matrix");
	m_meshDisplay.AddUniform("LOD_mvp_matrix");
	m_meshDisplay.AddUniform("proj_matrix");
	m_meshDisplay.AddUniform("dmap_depth");
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

void Terrain::Draw(const Transform & transform, const Camera & camera, bool lock, bool wireframe)
{
	glBindVertexArray(m_vao);
	m_shader.Use();
	glm::mat4 mv_matrix = transform.GetMatrix()*camera.GetViewMatrix();
	if (!lock)
	{
		LOD_mvp_matrix = camera.GetProjectionMatrix()*mv_matrix;
	}
	glUniformMatrix4fv(m_shader("mv_matrix"), 1, GL_FALSE, &mv_matrix[0][0]);
	glUniformMatrix4fv(m_shader("proj_matrix"), 1, GL_FALSE, &camera.GetProjectionMatrix()[0][0]);
	glUniformMatrix4fv(m_shader("LOD_mvp_matrix"), 1, GL_FALSE, &LOD_mvp_matrix[0][0]);

	glUniform1f(glGetUniformLocation(m_shader.getProgram(), "dmap_depth"), 3.0f);
	glDrawArraysInstanced(GL_PATCHES, 0, 4, 64 * 64);
	m_shader.UnUse();
	if (wireframe)
	{
		//save our incomming depthfunction
		GLint incDepthFunc;
		glGetIntegerv(GL_DEPTH_FUNC, &incDepthFunc);
		//now draw the mesh
		glDepthFunc(GL_LEQUAL);
		m_meshDisplay.Use();
		glUniformMatrix4fv(m_meshDisplay("mv_matrix"), 1, GL_FALSE, &mv_matrix[0][0]);
		glUniformMatrix4fv(m_meshDisplay("proj_matrix"), 1, GL_FALSE, &camera.GetProjectionMatrix()[0][0]);
		glUniformMatrix4fv(m_meshDisplay("LOD_mvp_matrix"), 1, GL_FALSE, &LOD_mvp_matrix[0][0]);

		glUniform1f(glGetUniformLocation(m_meshDisplay.getProgram(), "dmap_depth"), 3.0f);
		glDrawArraysInstanced(GL_PATCHES, 0, 4, 64 * 64);
		glDepthFunc(incDepthFunc); //default value
		m_meshDisplay.UnUse();
	}
	

	glBindVertexArray(0);
}
/* NOT WORKING */
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