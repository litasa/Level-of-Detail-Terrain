#include "Shader.h"
#include <iostream>
#include <fstream>



Shader::Shader()
{
	ShaderType[GL_VERTEX_SHADER] = 0;
	ShaderType[GL_FRAGMENT_SHADER] = 1;
	ShaderType[GL_GEOMETRY_SHADER] = 2;
	ShaderType[GL_TESS_CONTROL_SHADER] = 3;
	ShaderType[GL_TESS_EVALUATION_SHADER] = 4;
	ShaderType[GL_COMPUTE_SHADER] = 5;
	m_totalShaders = 0;
	m_attributeList.clear();
	m_uniformLocationList.clear();
}


Shader::~Shader()
{
	m_attributeList.clear();
	m_uniformLocationList.clear();
}

void Shader::LoadFromString(GLenum type, const std::string& source)
{
	GLuint shader = glCreateShader(type);

	const char* ptmp = source.c_str();
	glShaderSource(shader, 1, &ptmp, NULL);

	glCompileShader(shader);
	PrintError(shader);
	m_shaders[m_totalShaders++] = shader;
}

GLuint Shader::LoadFromStringAndReturn(GLenum type, const std::string& source)
{
	GLuint shader = glCreateShader(type);

	const char* ptmp = source.c_str();
	glShaderSource(shader, 1, &ptmp, NULL);

	glCompileShader(shader);
	Shader::PrintError(shader);
	return shader;
}

void Shader::CreateAndLinkProgram()
{
	m_program = glCreateProgram();
	if (m_shaders[ShaderType[GL_VERTEX_SHADER]] != 0)
	{
		glAttachShader(m_program, m_shaders[ShaderType[GL_VERTEX_SHADER]]);
	}
	if (m_shaders[ShaderType[GL_FRAGMENT_SHADER]] != 0)
	{
		glAttachShader(m_program, m_shaders[ShaderType[GL_FRAGMENT_SHADER]]);
	}
	if (m_shaders[ShaderType[GL_GEOMETRY_SHADER]] != 0)
	{
		glAttachShader(m_program, m_shaders[ShaderType[GL_GEOMETRY_SHADER]]);
	}
	if (m_shaders[ShaderType[GL_TESS_CONTROL_SHADER]] != 0)
	{
		glAttachShader(m_program, m_shaders[ShaderType[GL_TESS_CONTROL_SHADER]]);
	}
	if (m_shaders[ShaderType[GL_TESS_EVALUATION_SHADER]] != 0)
	{
		glAttachShader(m_program, m_shaders[ShaderType[GL_TESS_EVALUATION_SHADER]]);
	}
	if (m_shaders[ShaderType[GL_COMPUTE_SHADER]] != 0)
	{
		glAttachShader(m_program, m_shaders[ShaderType[GL_TESS_EVALUATION_SHADER]]);
	}

	glLinkProgram(m_program);
	PrintError(m_program);

	glDeleteShader(m_shaders[ShaderType[GL_VERTEX_SHADER]]);
	glDeleteShader(m_shaders[ShaderType[GL_FRAGMENT_SHADER]]);
	glDeleteShader(m_shaders[ShaderType[GL_GEOMETRY_SHADER]]);
	glDeleteShader(m_shaders[ShaderType[GL_TESS_CONTROL_SHADER]]);
	glDeleteShader(m_shaders[ShaderType[GL_TESS_EVALUATION_SHADER]]);
	glDeleteShader(m_shaders[ShaderType[GL_TESS_EVALUATION_SHADER]]);
}

void Shader::PrintError(GLuint programOrShader)
{
	GLint status;
	glGetShaderiv(programOrShader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetShaderiv(programOrShader, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar *infoLog = new GLchar[infoLogLength];
		glGetShaderInfoLog(programOrShader, infoLogLength, NULL, infoLog);
		std::cerr << "Compile log: " << infoLog << std::endl;
		delete[] infoLog;
	}
}

void Shader::Use()
{
	glUseProgram(m_program);
}

void Shader::UnUse()
{
	glUseProgram(0);
}

void Shader::AddAttribute(const std::string & attribute)
{
	m_attributeList[attribute];
}

void Shader::AddUniform(const std::string & uniform)
{
	m_uniformLocationList[uniform] = glGetUniformLocation(m_program, uniform.c_str());
}

GLuint Shader::getProgram() const
{
	return m_program;
}

GLuint Shader::operator[](const std::string & attribute)
{
	return AttrList(attribute);
}

GLuint Shader::operator()(const std::string & uniform)
{
	return UnifLoc(uniform);
}

void Shader::DeleteShaderProgram()
{
	glDeleteProgram(m_program);
}

void Shader::LinkProgram()
{
	glLinkProgram(m_program);
	PrintError(m_program);
}

void Shader::LoadFromFile(GLenum whichShader, const std::string & fileName)
{
	std::ifstream fp;
	fp.open(fileName.c_str(), std::ios_base::in);
	if (fp) {
		std::string buffer(std::istreambuf_iterator<char>(fp), (std::istreambuf_iterator<char>()));
		LoadFromString(whichShader, buffer);
	}
	else {
		std::cerr << "Error loading shader: " << fileName << std::endl;
	}

}

GLuint Shader::LoadFromFileAndReturn(GLenum type, const std::string & fileName)
{
	std::ifstream fp;
	fp.open(fileName.c_str(), std::ios_base::in);
	if (fp) {
		std::string buffer(std::istreambuf_iterator<char>(fp), (std::istreambuf_iterator<char>()));
		return LoadFromStringAndReturn(type, buffer);
	}
	else {
		std::cerr << "Error loading shader: " << fileName << std::endl;
	}
	return -1;
}

GLuint Shader::UnifLoc(const std::string& uniform)
{
	return m_uniformLocationList[uniform];
}

GLuint Shader::AttrList(const std::string& attrib)
{
	return m_attributeList[attrib];
}