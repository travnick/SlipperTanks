#pragma once

#include <set>

#include <QOpenGLDebugLogger>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>

#include "model/camera.hpp"

class InputEventHandler;
class Scene;

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    explicit OpenGLWidget(QWidget *parent = nullptr, Qt::WindowFlags f = 0);
    virtual ~OpenGLWidget();

    void setScene(Scene *scene);
    void setInputEventHandler(InputEventHandler *inputEventHandler);

    void enableFog();

protected:
    void initializeGL();
    void initializeLights();
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

    Camera _camera;
    QOpenGLShaderProgram _shaderProgram;
    QOpenGLDebugLogger _debugLogger;

    Scene *_scene;
    InputEventHandler *_inputEventHandler;
};
