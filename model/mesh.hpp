#pragma once

struct Mesh
{
    Mesh(int32_t startIndex, int32_t size, int32_t material):
        _startVertexIndex(startIndex),
        _vertexCount(size),
        _material(material)
    {
    }

    int32_t _startVertexIndex;
    int32_t _vertexCount;
    int32_t _material;
};
