// Source: https://github.com/BennyQBD/ModernOpenGLTutorial

#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/glew.h>

class Texture
{
public:
	Texture(std::string fileName, GLuint pixelFormat);
	Texture(unsigned char * data, int width, int height, GLuint pixelFormat);
	Texture(GLuint ID);

    void loadFromFile8(std::string fileName );
    void loadFromFile32(std::string fileName );
    void loadFromData8(unsigned char * data, int width, int height);
    void loadFromData32(unsigned char * data, int width, int height);
	void loadFromID(GLuint ID);
	void Bind(unsigned int unit);

	GLuint getTID() { if (this == NULL) return -1; else return m_texture; }

	virtual ~Texture();
protected:
private:
	Texture(const Texture& texture) {}
	void operator=(const Texture& texture) {}

	GLuint m_texture;
	GLuint m_pixelFormat;
};

#endif
