#include "Renderable.h"


Renderable::Renderable(std::vector<Vertex *> vertices,  Texture * tex)
	: _tex(tex)
{
	_vertices = vertices;
}


Renderable::~Renderable()
{
}
