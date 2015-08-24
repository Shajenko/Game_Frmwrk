#include "Sprite.h"

Sprite::Sprite(Mesh * mesh, Texture * texture, Transform * transform)
: _mesh(mesh), _texture(texture), _transform(transform)
{

}

Sprite::~Sprite()
{
    delete _mesh;
    delete _texture;
    delete _transform;
}
