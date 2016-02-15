#pragma once
#ifndef TERRAIN_H
#define TERRAIN_H

#include <string>
#include "Texture.h"
#include "Basic_Shader.h"

class Terrain
{
public:
	Terrain(const std::string& filePath);
	~Terrain();

	void Draw(const Transform & transform, const Camera & camera);

private:
	Texture m_heightmap;
	void loadShaders();
	void generateVAO(const std::string& filePath);

	GLuint m_vao;

	Basic_Shader m_shader;
};

#endif //TERRAIN_H