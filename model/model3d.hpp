#pragma once

#include <string>
#include <vector>

#include <QOpenGLBuffer>
#include <QOpenGLFunctions_2_1>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLVertexArrayObject>

#include "mesh.hpp"
#include "vertexbufferitem.hpp"

class Model3D
{
public:
    Model3D(const std::string &filename);
    Model3D(Model3D &&other);
    Model3D(const Model3D &other);

    virtual ~Model3D();

    virtual void initialize();
    virtual void render();

protected:
    Model3D();

private:
    void loadFromFile(const std::string &filename);

    void prepareVertexArrayObject();

    Meshes _meshes;
    std::vector<VertexBufferItem> _vertexBufferItems;

    QOpenGLVertexArrayObject _vertexArrayObject;
    QOpenGLBuffer _vertexBuffer;
    QOpenGLFunctions_3_3_Core *gl;

    bool _isInitialized;
};
