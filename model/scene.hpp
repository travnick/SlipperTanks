#pragma once

#include <QFileSystemWatcher>

#include "model3d.hpp"

class Scene
{
public:
    Scene(const std::string &modelDirectory);
    ~Scene();

    void loadModel(const std::string &fileName);
    void loadModels();
    void initializeModels();

    void render();

private:
    void initializeFilesWatcher();
    void onModelChanged(const std::string &fileName);

    std::map<std::string, Model3D> _models3D;
    QFileSystemWatcher _filesystemWatcher;

    std::string _modelDirectory;
};
