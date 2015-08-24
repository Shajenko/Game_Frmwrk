#pragma once
#include "RenderEngine.h"

const unsigned int MAX_VERTS = 40000;
const unsigned int MAX_INDICES = 60000;
const unsigned int MAX_TEXTURES = 32;

class BatchRenderEngine :
	public RenderEngine
{
public:
	BatchRenderEngine(int width, int height);
	virtual ~BatchRenderEngine();
	virtual void render();
protected:
	virtual void init();
	virtual void enqueue(Renderable r, GLuint * indices);
	virtual void startBatch();
	virtual void flush();
	virtual void endBatch();

	Vertex * _vertices;
	GLuint * _indices;

	int _texIDs[MAX_TEXTURES];

	GLuint _indBuffer;

	float _textures[MAX_TEXTURES];

	unsigned int _currVerts;
	unsigned int _currInds;
	unsigned int _currTextures;

	GLuint _VBO, _VAO;

};

