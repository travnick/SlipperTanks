#pragma once

#include <string>

struct Mesh
{
    Mesh(const std::string &name, int32_t startIndex, int32_t size, int32_t material):
        _name(name),
        _startVertexIndex(startIndex),
        _vertexCount(size),
        _material(material)
    {
    }

    std::string _name;
    int32_t _startVertexIndex;
    int32_t _vertexCount;
    int32_t _material;
};
