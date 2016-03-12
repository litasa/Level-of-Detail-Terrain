#pragma once
#ifndef TERRAIN_H
#define TERRAIN_H

#include <string>
#include "Texture.h"
#include "Basic_Shader.h"

class Terrain
{
public:
	Terrain(const std::string& heightMap, const std::string& terrainTexture);
	~Terrain();

	void Draw(const Transform & transform, const Camera & camera, bool lock, bool wireframe);

	float GetHeightAt(glm::vec3& position);

private:
	Texture m_heightmap;
	void loadShaders();
	void generateVAO(const std::string& heightMap, const std::string& terrainTexture);
	void loadHeightDataToCPU();

	GLuint m_vao; //vertex array object
	GLuint m_buffer; //trial buffer to extract data

	Basic_Shader m_shader;
	Basic_Shader m_meshDisplay;

	unsigned int m_2Dwidth;
	unsigned int m_2Dheight; //z component

	std::vector<float> m_heightData;

	glm::mat4 LOD_mvp_matrix;
};

#endif //TERRAIN_H