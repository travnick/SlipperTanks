#include <QDebug>

#include <QDir>
#include <QOpenGLShaderProgram>
#include <QString>
#include <QStringList>

#include "emptymodel3d.hpp"
#include "player.hpp"
#include "scene.hpp"

Node dummyNode(EmptyModel3D::getStaticGlobalInstance());

Scene::Scene(const std::string &modelDirectory, Player &player):
    _modelDirectory(modelDirectory),
    _player(player)
{
    initializeFilesWatcher();
}

Scene::~Scene()
{
}

void Scene::initializeFilesWatcher()
{
    _filesystemWatcher.addPath(QString::fromStdString(_modelDirectory));

    QObject::connect(&_filesystemWatcher, &QFileSystemWatcher::fileChanged, [this](const QString &path)
    {
        qDebug() << "file watch: " << path;
        std::string filePath = path.toStdString();

        this->removeModel(filePath);

        if (QFile::exists(path))
        {
            this->loadModel(filePath);
        }
    });

    QObject::connect(&_filesystemWatcher, &QFileSystemWatcher::directoryChanged, [this](const QString &path)
    {
        qDebug() << "dir watch: " << path;

        if (!QFile::exists(path))
        {
            this->removeModels();
        }
        else
        {
            this->loadModels();
        }
    });
}

void Scene::loadModel(const std::string &fileName)
{
    _models3D.emplace(fileName, fileName);
}

void Scene::loadModels()
{
    QDir modelDirectory(QString::fromStdString(_modelDirectory));

    for (const QString &entry : modelDirectory.entryList(QDir::Files | QDir::Readable))
    {
        _filesystemWatcher.addPath(modelDirectory.filePath(entry));
        loadModel(modelDirectory.filePath(entry).toStdString());
    }

    auto found = _models3D.find(_player.getRequiredModelName());
    if (found != _models3D.end())
    {
        _player.setAttachedNode(&createNodeForModel("player", found->second));
    }
}

void Scene::initializeModels()
{
    for (auto &node : _nodes)
    {
        node.second.initializeModel();
    }
}

void Scene::render(QOpenGLShaderProgram &shaderProgram, const QMatrix4x4 &viewProjectionMatrix)
{
//    shaderProgram.setUniformValue(10, viewProjectionMatrix);

    for (auto &pair : _nodes)
    {
        Node &node = pair.second;
        QMatrix4x4 modelMatrix = node.getModelMatrix();
        QMatrix4x4 modelViewProjectionMatrix = viewProjectionMatrix * modelMatrix;

        shaderProgram.setUniformValue(11, modelMatrix);
        shaderProgram.setUniformValue(12, modelViewProjectionMatrix);

        node.renderModel();
    }
}

void Scene::removeModels()
{
    _player.setAttachedNode(nullptr);

    _nodes.clear();
    _models3D.clear();
}

void Scene::createNodeForModel(const std::string &nodeName, const std::string &modelName)
{
    auto found = _models3D.find(modelName);
    if (found != _models3D.end())
    {
        createNodeForModel(nodeName, found->second);
    }
}

Node &Scene::createNodeForModel(const std::string &nodeName, Model3D &model)
{
    auto pair = _nodes.emplace(nodeName, model);

    return pair.first->second;
}

void Scene::removeModel(const std::string &fileName)
{
    auto modelFound = _models3D.find(fileName);
    if (modelFound != _models3D.end())
    {
        if (&modelFound->second == &_player.getAttachedNode().getModel())
        {
            _player.setAttachedNode(nullptr);
        }

        removeAllInstancesOfModel(modelFound->second);

        _models3D.erase(modelFound);
    }
}

void Scene::removeAllInstancesOfModel(const Model3D &model)
{
    auto end = _nodes.end();
    for (auto it = _nodes.begin(); it != end; ++it)
    {
        if (&it->second.getModel() == &model)
        {
            it = _nodes.erase(it);
        }
    }
}
