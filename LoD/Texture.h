#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H
#define STB_IMAGE_IMPLEMENTATION
#include <string>
#include <GL\glew.h>
#include <vector>
#include <map>

class Texture
{
public:
	Texture();
	Texture(const std::string& fileName, unsigned int unit = 0);

	void Use(unsigned int unit = 0);
	void AddTexture(const std::string& fileName, unsigned int unit);

	GLuint& GetTexture(unsigned int unit = 0) { return m_texture[unit]; }
	~Texture();

protected:

	void Load(const std::string& fileName, unsigned int unit = 0);

private:
	std::vector<GLuint> m_texture;
	std::map<unsigned int, std::string> m_unitBound; //texture unit to filePath
													// size contains number of textures
};

class CubemapTexture
{
public:
	CubemapTexture(
		const std::string& directory,
		const std::string& front,
		const std::string& back,
		const std::string& left,
		const std::string& right,
		const std::string& top,
		const std::string& bottom);
	~CubemapTexture() {};

	bool Load();

	void Bind(GLenum TextureUnit);

private:
	enum
	{
		RIGHT,
		LEFT,
		TOP,
		BOTTOM,
		BACK,
		FRONT,
	};
	std::string m_fileNames[6];
	GLuint m_texObj;
};

#endif //TEXTURE_H
