// Source: https://github.com/BennyQBD/ModernOpenGLTutorial

#include "shader.h"
#include <iostream>
#include <fstream>

Shader::Shader(const std::string& fileName)
{
	m_program = glCreateProgram();
	m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

	for(unsigned int i = 0; i < NUM_SHADERS; i++)
		glAttachShader(m_program, m_shaders[i]);

	glBindAttribLocation(m_program, 0, "position");
	glBindAttribLocation(m_program, 1, "texCoord");
	glBindAttribLocation(m_program, 2, "normal");
	glBindAttribLocation(m_program, 3, "color");
	glBindAttribLocation(m_program, 4, "tid");

	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error linking shader program");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Invalid shader program");

	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
	m_uniforms[PROJECTION_U] = glGetUniformLocation(m_program, "projection");
}

Shader::~Shader()
{
	for(unsigned int i = 0; i < NUM_SHADERS; i++)
    {
        glDetachShader(m_program, m_shaders[i]);
        glDeleteShader(m_shaders[i]);
    }

	glDeleteProgram(m_program);
}

void Shader::Bind()
{
	glUseProgram(m_program);
}

GLint Shader::getUniformLocation(const GLchar* name)
{
	return glGetUniformLocation(m_program, name);
}

void Shader::setUniform1f(const GLchar * name, float value)
{
	glUniform1f(getUniformLocation(name), value);
}

void Shader::setUniform1fv(const GLchar * name, int count, float * value)
{
	glUniform1fv(getUniformLocation(name), count, value);
}

void Shader::setUniform1i(const GLchar * name, int value)
{
	glUniform1i(getUniformLocation(name), value);
}

void Shader::setUniform1iv(const GLchar * name, int count, int * value)
{
	glUniform1iv(getUniformLocation(name), count, value);
}

void Shader::setUniform2f(const GLchar * name, const glm::vec2& vector)
{
	glUniform2f(getUniformLocation(name), vector.x, vector.y);
}

void Shader::setUniform3f(const GLchar * name, const glm::vec3& vector)
{
	glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
}

void Shader::setUniform4f(const GLchar * name, const glm::vec4& vector)
{
	glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
}

/*
void Shader::setUniformMat4(const GLchar * name, const glm::mat4& matrix)
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
}*/


void Shader::Update(const Transform& transform)
{
    glm::mat4 model = transform.GetModel();
    glm::mat4 ortho = transform.GetProjection();

    glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(m_uniforms[PROJECTION_U], 1, GL_FALSE, &ortho[0][0]);
}

std::string Shader::LoadShader(const std::string& fileName)
{
    std::ifstream file;
    file.open((fileName).c_str());

    std::string output;
    std::string line;

    if(file.is_open())
    {
        while(file.good())
        {
            getline(file, line);
			output.append(line + "\n");
        }
    }
    else
    {
		std::cerr << "Unable to load shader: " << fileName << std::endl;
    }

    return output;
}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
    GLint success = 0;
    GLchar error[1024] = { 0 };

    if(isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if(success == GL_FALSE)
    {
        if(isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);

        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}

GLuint Shader::CreateShader(const std::string& text, unsigned int type)
{
    GLuint shader = glCreateShader(type);

    if(shader == 0)
		std::cerr << "Error compiling shader type " << type  << std::endl;

    const GLchar* p[1];
    p[0] = text.c_str();
    GLint lengths[1];
    lengths[0] = text.length();

    glShaderSource(shader, 1, p, lengths);
    glCompileShader(shader);

    CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!");

    return shader;
}
