// Source: https://github.com/BennyQBD/ModernOpenGLTutorial

#include "texture.h"
#include "stb_image.h"
#include <iostream>
#include <cassert>

Texture::Texture(std::string fileName, GLuint pixelFormat)
{
	m_texture = 0;

    if(pixelFormat == GL_ALPHA)
        loadFromFile8(fileName);
    else if(pixelFormat == GL_RGBA)
        loadFromFile32(fileName);
}

Texture::Texture(unsigned char * data, int width, int height, GLuint pixelFormat)
{
	m_texture = 0;

    if(pixelFormat == GL_ALPHA)
        loadFromData8(data, width, height);
    else if(pixelFormat == GL_RGBA)
        loadFromData32(data, width, height);
}

Texture::Texture(GLuint ID)
{
	m_texture = 0;

	loadFromID(ID);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_texture);
}

void Texture::loadFromFile8(std::string fileName)
{
	int width, height, numComponents;
    unsigned char* data = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4);

	if (data == NULL)
	{
		std::cout << "Error - stbi_load failed.\n";
		return;
	}

    loadFromData8(data, width, height);

    stbi_image_free(data);
}

void Texture::loadFromFile32(std::string fileName)
{
	int width, height, numComponents;
    unsigned char* data = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4);

	if (data == NULL)
	{
		std::cout << "Error - stbi_load failed.\n";
		return;
	}

    loadFromData32(data, width, height);

    stbi_image_free(data);
}


void Texture::loadFromData8(unsigned char * data, int width, int height)
{
    if(data == NULL)
		std::cerr << "Unable to load texture! " << std::endl;

    glGenTextures(1, &m_texture); // Generates space for a texture, puts handle in m_texture
    glBindTexture(GL_TEXTURE_2D, m_texture);

    // Makes the texture wrap around the mesh that is drawn
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Interpolation based on rotated mesh
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Copy data to GPU
    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, width, height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, data);
//    glTexImage2D()
}

void Texture::loadFromData32(unsigned char * data, int width, int height)
{
    if(data == NULL)
		std::cerr << "Unable to load texture! " << std::endl;

    glGenTextures(1, &m_texture); // Generates space for a texture, puts handle in m_texture
    glBindTexture(GL_TEXTURE_2D, m_texture);

    // Makes the texture wrap around the mesh that is drawn
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Interpolation based on rotated mesh
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Copy data to GPU
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//    glTexImage2D()
}

void Texture::loadFromID(GLuint ID)
{
	m_texture = ID;
}


void Texture::Bind(unsigned int unit)
{
    assert(unit >=0 && unit <= 31);

    glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_texture);

}
