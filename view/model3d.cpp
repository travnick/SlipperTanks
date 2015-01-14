#include <vector>

#include <QDebug>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "model3d.hpp"
#include "openglwidget.hpp"
#include "utils/openglhelpers.hpp"

Model3D::Model3D():
    _meshes(),
    _vertexBufferItems(),
    _vertexArrayObject(QOpenGLContext::currentContext()),
    _vertexBuffer(QOpenGLBuffer::Type::VertexBuffer),
    gl(*QOpenGLContext::currentContext()->functions()),
    _isInitialized(false)
{
}

Model3D::Model3D(Model3D &&other):
    _meshes(std::move(other._meshes)),
    _vertexBufferItems(std::move(other._vertexBufferItems)),
    _vertexArrayObject(QOpenGLContext::currentContext()),
    _vertexBuffer(std::move(other._vertexBuffer)),
    gl(*QOpenGLContext::currentContext()->functions())
{
    if (other._isInitialized)
    {
        initialize();
    }
}

Model3D::Model3D(const Model3D &other):
    _meshes(other._meshes),
    _vertexBufferItems(other._vertexBufferItems),
    _vertexArrayObject(nullptr),
    _vertexBuffer(other._vertexBuffer),
    gl(*QOpenGLContext::currentContext()->functions())
{
    if (other._isInitialized)
    {
        initialize();
    }
}

Model3D::~Model3D()
{
}

void Model3D::render()
{
    _vertexArrayObject.bind();

    for (const Mesh &mesh : _meshes)
    {
//        gl.
                glDrawArrays(GL_TRIANGLES, mesh._startVertexIndex, mesh._vertexCount);
    }

    _vertexArrayObject.release();
}

Model3D Model3D::fromFile(const std::string &filename)
{
    using namespace Assimp;
    const int verticesPerFace = 3;

    Model3D model;

    Importer importer;
    const aiScene *pScene = importer.ReadFile(filename,
                                              aiProcess_Triangulate |
                                              aiProcess_JoinIdenticalVertices);

    if (!pScene)
    {
        qWarning() << "Couldn't load model " << filename.c_str();
        return model;
    }

    const aiScene &scene = *pScene;

    model._meshes.reserve(scene.mNumMeshes);

    for (uint i = 0; i < scene.mNumMeshes; ++i)
    {
        aiMesh &mesh = *scene.mMeshes[i];
        const int meshSize = mesh.mNumFaces * verticesPerFace;

        qDebug() << mesh.mName.C_Str();

        model._meshes.emplace_back(model._vertexBufferItems.size(), meshSize, mesh.mMaterialIndex);
        model._vertexBufferItems.reserve(model._vertexBufferItems.capacity() + meshSize);

        for (uint f = 0; f < mesh.mNumFaces; ++f)
        {
            const aiFace &face = mesh.mFaces[f];

            for (uint k = 0; k < verticesPerFace; ++k)
            {
                aiVector3D position = mesh.mVertices[face.mIndices[k]];
                aiVector3D normal = mesh.mNormals[face.mIndices[k]];
                aiVector3D uv = mesh.mTextureCoords[0][face.mIndices[k]];

                model._vertexBufferItems.emplace_back(position, normal, uv);
            }
        }
    }

    return model;
}

void Model3D::initialize()
{
    prepareVertexArrayObject();

    _isInitialized = true;
}

void Model3D::prepareVertexArrayObject()
{
    using namespace utils;

    _vertexArrayObject.create();
    _vertexArrayObject.bind();

    _vertexBuffer.create();
    _vertexBuffer.bind();

    _vertexBuffer.allocate(_vertexBufferItems.data(), _vertexBufferItems.size() * sizeof(VertexBufferItem));

    enableVertaxAttribPointer(0,
                              sizeof(VertexBufferItem::_position) / sizeof(GLfloat),
                              GL_FLOAT, GL_FALSE,
                              sizeof(VertexBufferItem),
                              offsetof(VertexBufferItem, _position));

    enableVertaxAttribPointer(1,
                              sizeof(VertexBufferItem::_uv) / sizeof(GLfloat),
                              GL_FLOAT, GL_FALSE,
                              sizeof(VertexBufferItem),
                              offsetof(VertexBufferItem, _uv));

    enableVertaxAttribPointer(2,
                              sizeof(VertexBufferItem::_normal) / sizeof(GLfloat),
                              GL_FLOAT, GL_FALSE,
                              sizeof(VertexBufferItem),
                              offsetof(VertexBufferItem, _normal));

    _vertexBuffer.release();
    _vertexArrayObject.release();
}
