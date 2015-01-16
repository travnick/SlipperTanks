#pragma once

#include <string>
#include <vector>

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>

#include "mesh.hpp"
#include "vertexbufferitem.hpp"

class Model3D
{
public:
    Model3D(const std::string &filename);
    Model3D(Model3D &&other);
    Model3D(const Model3D &other);

    ~Model3D();

    void initialize();
    void render();

private:
    void loadFromFile(const std::string &filename);

    void prepareVertexArrayObject();

    std::vector<Mesh> _meshes;
    std::vector<VertexBufferItem> _vertexBufferItems;

    QOpenGLVertexArrayObject _vertexArrayObject;
    QOpenGLBuffer _vertexBuffer;
    QOpenGLFunctions *gl;

    bool _isInitialized;
};
