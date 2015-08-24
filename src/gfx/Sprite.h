#ifndef SPRITE_H
#define SPRITE_H

#include "./OpenGL/transform.h"
#include "./OpenGL/texture.h"
#include "./OpenGL/mesh.h"

class Sprite
{
    public:
        Sprite(Mesh * mesh, Texture * texture, Transform * transform);
        virtual ~Sprite();
    protected:
    private:
        Mesh * _mesh;
        Texture * _texture;
        Transform * _transform;
};

#endif // SPRITE_H
