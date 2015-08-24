#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "./OpenGL/texture.h"

struct Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal, const glm::vec4& color, const float& tid)
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
		this->color = color;
		this->tid = tid;
	}

	glm::vec3* GetPos() { return &pos; }
	glm::vec2* GetTexCoord() { return &texCoord; }
	glm::vec3* GetNormal() { return &normal; }
	glm::vec4* GetColor() { return &color; }
	float * GetTID() { return &tid; }

	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
	glm::vec4 color;
	float tid;

private:

};

enum VertexBufferPositions
{
	POSITION_VB,
	TEXCOORD_VB,
	NORMAL_VB,
	COLOR_VB,
	TID_VB,
	INDEX_VB,
	NUM_BUFFERS
};

class Renderable
{
public:
	Renderable(std::vector<Vertex *> vertices, Texture * tex);
	virtual ~Renderable();

	std::vector<Vertex *> getVertices() { return _vertices; }
	float getTid() { if (_tex != NULL) return (float)_tex->getTID(); else return 0.0f; }

private:
	std::vector<Vertex *> _vertices;
	Texture * _tex;
};

