#include "Renderable.h"

Renderable::Renderable()
{
	_vertices.clear();
	_tex = nullptr;
}

Renderable::Renderable(std::vector<Vertex *> vertices,  Texture * tex)
{
	copyRenderable(vertices, tex);
}


Renderable::~Renderable()
{
}

void Renderable::copyRenderable(std::vector<Vertex *> vertices, Texture * tex)
{
	_tex = tex;
	_vertices = vertices;
}