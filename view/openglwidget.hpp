#pragma once

#include <QOpenGLDebugLogger>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>

#include "model3d.hpp"

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    explicit OpenGLWidget(QWidget *parent = 0, Qt::WindowFlags f = 0);
    virtual ~OpenGLWidget();

    void animate()
    {
        xRot+=10;
    }

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    void initializeOpenGLDebugging();
    void loadModels();
    void prepareShaders();

    std::vector<Model3D> _models3D;
    QOpenGLShaderProgram _shaderProgram;
    QOpenGLDebugLogger _debugLogger;
    QPoint lastMousePosition;

    int64_t xRot;
    int64_t yRot;
    int64_t zRot;
};
