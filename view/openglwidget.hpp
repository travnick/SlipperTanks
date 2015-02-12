#pragma once

#include <map>
#include <memory>
#include <set>

#include <QFileSystemWatcher>
#include <QOpenGLDebugLogger>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>

#include "model/camera.hpp"

class InputEventManager;
class Player;
class Scene;

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    explicit OpenGLWidget(QWidget *parent = nullptr, Qt::WindowFlags f = 0);
    virtual ~OpenGLWidget();

    void setScene(Scene *scene);
    void setInputEventManager(InputEventManager *inputEventManager);
    void attachCameraToPlayer(Player &player);

public slots:
    void toggleWireFrameMode(bool wireframe);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    void initializeOpenGLDebugging();
    void prepareShaders();
    void setPolygonDrawMode();

    Camera _camera;
    QOpenGLShaderProgram _shaderProgram;
    QOpenGLDebugLogger _debugLogger;
    QFileSystemWatcher _filesystemWatcher;
    std::map<std::string, std::unique_ptr<QOpenGLShader>> _shaders;

    Scene *_scene;
    InputEventManager *_inputEventManager;
    bool _wireFrameMode;
};
