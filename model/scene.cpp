#include <QDebug>

#include <QDir>
#include <QString>
#include <QStringList>

#include "scene.hpp"

Scene::Scene(const std::string &modelDirectory):
    _modelDirectory(modelDirectory)
{
    initializeFilesWatcher();
}

Scene::~Scene()
{
}

void Scene::initializeFilesWatcher()
{
    _filesystemWatcher.addPath(QString::fromStdString(_modelDirectory));

    QObject::connect(&_filesystemWatcher, &QFileSystemWatcher::fileChanged,[this](const QString path)
    {
        qDebug() << "file watch: " << path;
        std::string filePath = path.toStdString();

        this->_models3D.erase(_models3D.find(filePath));

        if (QFile::exists(path))
        {
            this->loadModel(filePath);
        }
    });

    QObject::connect(&_filesystemWatcher, &QFileSystemWatcher::directoryChanged,[this](const QString path)
    {
        qDebug() << "dir watch: " << path;
        std::string filePath = path.toStdString();

        if (!QFile::exists(path))
        {
            this->_models3D.clear();
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
}

void Scene::initializeModels()
{
    for (auto &model : _models3D)
    {
        model.second.initialize();
    }
}

void Scene::render()
{
    for (auto &model : _models3D)
    {
        model.second.render();
    }
}
