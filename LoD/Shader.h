#pragma once
#include <map>
#include <string>
#include "GL\glew.h"
#include "Transform.h"
#include "Camera.h"

class Shader
{
public:
	Shader();
	virtual ~Shader() = 0;

	virtual void UpdateValues(const Transform & transform, const Camera & camera);

	void LoadFromString(GLenum type, const std::string& source);

	void CreateAndLinkProgram();
	void Use();
	void UnUse();
	void AddAttribute(const std::string& attribute);
	void AddUniform(const std::string& uniform);
	GLuint getProgram() const;

	GLuint operator[](const std::string& attribute);
	GLuint operator()(const std::string& uniform);
	void DeleteShaderProgram();

	void LoadFromFile(GLenum whichShader, const std::string& fileName);
protected:
	void PrintError(GLuint programOrShader);

	enum ShaderType {
		VERTEX_SHADER, FRAGMENT_SHADER, GEOMETRY_SHADER
	};
	GLuint m_program;
	int m_totalShaders;
	GLuint m_shaders[3];
	std::map<std::string, GLuint> m_attributeList;
	std::map<std::string, GLuint> m_uniformLocationList;

	GLuint UnifLoc(const std::string& uniform);
	GLuint AttrList(const std::string& attrib);
private:


};

