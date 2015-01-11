#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

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
    QPoint lastMousePosition;

    int64_t xRot;
    int64_t yRot;
    int64_t zRot;
};
