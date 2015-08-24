// Source: https://github.com/BennyQBD/ModernOpenGLTutorial

#ifndef SHADER_INCLUDED_H
#define SHADER_INCLUDED_H

#include <string>
#include <GL/glew.h>
#include "transform.h"

class Shader
{
public:
	GLuint _shaderID;
	Shader(const std::string& fileName);

	void Bind();
	void Update(const Transform& transform);

	virtual ~Shader();

	void setUniform1f(const GLchar * name, float value);
	void setUniform1fv(const GLchar * name, int count, float * value);
	void setUniform1i(const GLchar * name, int value);
	void setUniform1iv(const GLchar * name, int count, int * value);
	void setUniform2f(const GLchar * name, const glm::vec2& vector);
	void setUniform3f(const GLchar * name, const glm::vec3& vector);
	void setUniform4f(const GLchar * name, const glm::vec4& vector);
	//void setUniformMat4(const GLchar * name, const glm::mat4& matrix);
protected:
	GLint getUniformLocation(const GLchar* name);
private:
	static const unsigned int NUM_SHADERS = 2;

	void operator=(const Shader& shader) {}
	Shader(const Shader& shader) {}

	enum
	{
	    TRANSFORM_U,
        PROJECTION_U,
	    NUM_UNIFORMS
	};

	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, unsigned int type);

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];
};

#endif
