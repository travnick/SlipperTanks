#pragma once

#include <set>

#include <QOpenGLDebugLogger>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>

#include "model/camera.hpp"

class Scene;

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    explicit OpenGLWidget(QWidget *parent = nullptr, Qt::WindowFlags f = 0);
    virtual ~OpenGLWidget();

    void processInput();
    void setScene(Scene *scene);
protected:
    void initializeGL();
    void initializeLights();
    void paintGL();
    void resizeGL(int width, int height);

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    void initializeOpenGLDebugging();
    void prepareShaders();

    Camera _camera;
    QOpenGLShaderProgram _shaderProgram;
    QOpenGLDebugLogger _debugLogger;
    QPoint _lastMousePosition;

    QVector3D _position;
    QVector3D _rotation;

    std::set<int> _keysPressed;
    Scene *_scene;
};
