#pragma once

#include <QFileSystemWatcher>

#include "model3d.hpp"
#include "node.hpp"

class QOpenGLShaderProgram;

class Player;

class Scene
{
public:
    Scene(const std::string &modelDirectory, Player &player);
    ~Scene();

    void createNodeForModel(const std::string &nodeName, const std::string &modelName);

    void loadModel(const std::string &fileName);
    void loadModels();
    void initializeModels();

    void render(QOpenGLShaderProgram &shaderProgram, const QMatrix4x4 &viewProjectionMatrix);

private:
    void initializeFilesWatcher();
    void onModelChanged(const std::string &fileName);

    Node &createNodeForModel(const std::string &nodeName, Model3D &model);

    void removeAllInstancesOfModel(const Model3D &model);
    void removeModel(const std::string &fileName);
    void removeModels();

    std::map<std::string, Node> _nodes;
    std::map<std::string, Model3D> _models3D;
    QFileSystemWatcher _filesystemWatcher;

    std::string _modelDirectory;

    Player &_player;
};
