#include "Texture.h"

#include "stb_image.h"
#include <cassert>
#include <iostream>


Texture::Texture(const std::string& fileName, unsigned int unit)
{
	m_texture.resize(32);
	Load(fileName, unit);
}

Texture::Texture()
{
	//no texture binded
	m_texture.clear();
}

Texture::~Texture()
{
	for (auto it = m_unitBound.cbegin(); it != m_unitBound.cend(); ++it)
	{
		glDeleteTextures(1, &(*it).first);
	}
}

void Texture::Load(const std::string& fileName, unsigned int unit)
{
	int width, height, numComponent;

	unsigned char* imageData = stbi_load((fileName).c_str(), &width, &height, &numComponent, 4);

	if (imageData == nullptr)
	{
		std::cerr << "Texture loading failed for texture " << fileName << std::endl;
	}

	m_width = width;
	m_height = height;
	m_numComponents = numComponent;
	m_memSize = width*height*m_numComponents;

	GLuint texture;
	m_texture.push_back(texture);
	m_unitBound[unit] = fileName;
	glActiveTexture(GL_TEXTURE0 + unit);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //if texture is too large
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //if texture is too small

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	stbi_image_free(imageData);
}


void Texture::Use(unsigned int unit)
{
	//crash program if too many units or texture not initialized
	assert(unit >= 0 && unit <= 31 && m_texture.size() > 0);
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_texture[unit]);
}

void Texture::AddTexture(const std::string & fileName, unsigned int unit)
{
	Load(fileName, unit);
}

unsigned char* Texture::GetTextureData(Texture & texture)
{
	std::string fileName = texture.m_unitBound[0];
	int width = texture.Width();
	int height = texture.Height();
	int numComponent = texture.m_numComponents;
	return stbi_load((fileName).c_str(), &width, &height, &numComponent, 4);
}

CubemapTexture::CubemapTexture(
	const std::string& directory,
	const std::string& front,
	const std::string& back,
	const std::string& left,
	const std::string& right,
	const std::string& top,
	const std::string& bottom)
{
	m_fileNames[FRONT] = directory + front;
	m_fileNames[BACK] = directory + back;
	m_fileNames[LEFT] = directory + left;
	m_fileNames[RIGHT] = directory + right;
	m_fileNames[TOP] = directory + top;
	m_fileNames[BOTTOM] = directory + bottom;
}

bool CubemapTexture::Load()
{
	glGenTextures(1, &m_texObj);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texObj);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, 0);

	int width, height, numComponent;
	//ignore first position, the directory
	for (unsigned int i = 0; i < 6; i++)
	{
		
		unsigned char* imageData = stbi_load((m_fileNames[i]).c_str(), &width, &height, &numComponent, 4);
		if (imageData == NULL)
		{
			std::cerr << "Textureloading in CubemapTexture::Load\n";
			std::cerr << "Trying to load " << m_fileNames[i] << " : Failed" << std::endl;
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

		stbi_image_free(imageData);
	}

	return true;
	
}

void CubemapTexture::Bind(GLenum textureUnit)
{
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texObj);
}