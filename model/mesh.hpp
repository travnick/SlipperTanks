#pragma once

#include <string>
#include <vector>

#include <GL/gl.h>

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
    GLint _startVertexIndex;
    GLsizei _vertexCount;
    int32_t _material;
};

struct Meshes
{
    void addNext(std::string &&name, GLint startIndex, GLsizei vertexCount, int32_t material)
    {
        _name.push_back(std::move(name));
        _startVertexIndex.push_back(startIndex);
        _vertexCount.push_back(vertexCount);
        _material.push_back(material);
    }

    size_t size() const
    {
        return _startVertexIndex.size();
    }

    void reserve(size_t count)
    {
        _name.reserve(count);
        _startVertexIndex.reserve(count);
        _vertexCount.reserve(count);
        _material.reserve(count);
    }

    std::vector<std::string> _name;
    std::vector<GLint> _startVertexIndex;
    std::vector<GLsizei> _vertexCount;
    std::vector<int32_t> _material;
};
