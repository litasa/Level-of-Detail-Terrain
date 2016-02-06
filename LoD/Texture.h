#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H
#define STB_IMAGE_IMPLEMENTATION
#include <string>
#include <GL\glew.h>
#include <vector>

class Texture
{
public:
	Texture();
	Texture(const std::string& fileName);

	void Use(unsigned int unit = 0);

	GLuint& GetTexture() { return m_texture; }
	~Texture();

protected:

private:
	GLuint m_texture;
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
