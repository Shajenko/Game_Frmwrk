// Source: https://github.com/BennyQBD/ModernOpenGLTutorial

#ifndef MESH_INCLUDED_H
#define MESH_INCLUDED_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>
#include <vector>
#include "obj_loader.h"

 // needs to be before "SDL_opengl.h
//#include <GL/glu.h>
//#include "SDL_opengl.h"
//#include <GL/glut.h>

enum MeshBufferPositions
{
	POSITION_VB,
	TEXCOORD_VB,
	INDEX_VB,
	NORMAL_VB,
	NUM_BUFFERS
};

class Mesh
{
public:
    Mesh();
    Mesh(const std::string& fileName);
	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);

	void Draw();

	virtual ~Mesh();
protected:
    void loadMesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);

	static const unsigned int NUM_BUFFERS = 4;
	void operator=(const Mesh& mesh) {}
	Mesh(const Mesh& mesh) {}

    void InitMesh(const IndexedModel& model);

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;
	unsigned int m_numIndices;

private:
};

#endif
