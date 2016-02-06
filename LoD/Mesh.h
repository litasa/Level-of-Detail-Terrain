#pragma once
#ifndef MESH_H
#define MESH_H

#include "glm\glm.hpp"
#include <GL\glew.h>
#include "obj_loader.h"

class Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal = glm::vec3(0, 0, 0))
	{
		this->m_pos = pos;
		this->m_texCoord = texCoord;
		this->m_normal = normal;
	}

	glm::vec3* GetPos() { return &m_pos; }
	glm::vec2* GetTexCoord() { return &m_texCoord; }
	glm::vec3* GetNormal() { return &m_normal; }
protected:

private:
	glm::vec3 m_pos;
	glm::vec2 m_texCoord;
	glm::vec3 m_normal;
};


class Mesh
{
public:
	Mesh() {};
	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	Mesh(Vertex* vertices, unsigned int numVertices);
	Mesh(const std::string& fileName);
	~Mesh();

	void Draw();
	void Draw() const;
protected:

private:
	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		INDEX_VB,
		NORMAL_VB,

		NUM_BUFFERS
	};

	void InitMesh(const IndexedModel& model);

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;
};

#endif //MESH_H