#pragma once

#include <string>
#include <vector>

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>

#include <assimp/vector2.h>
#include <assimp/vector3.h>

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

class Model3D
{
public:
    Model3D(Model3D &&other);
    Model3D(const Model3D &other);

    virtual ~Model3D();

    void initialize();
    void render();

    static Model3D fromFile(const std::string &filename);

private:
    Model3D();

    void prepareVertexArrayObject();

    std::vector<Mesh> _meshes;
    std::vector<VertexBufferItem> _vertexBufferItems;

    QOpenGLVertexArrayObject _vertexArrayObject;
    QOpenGLBuffer _vertexBuffer;
    QOpenGLFunctions &gl;

    bool _isInitialized;
};
