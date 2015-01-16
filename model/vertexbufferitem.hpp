#pragma once

#include <assimp/vector2.h>
#include <assimp/vector3.h>

struct VertexBufferItem
{
    VertexBufferItem(aiVector3D position, aiVector3D normal, aiVector3D uv):
        _position(position),
        _normal(normal),
        _uv(uv.x, uv.y)
    {
    }

    aiVector3D _position;
    aiVector3D _normal;
    aiVector2D _uv;
};
