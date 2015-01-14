#include <QDebug>
#include <QMouseEvent>

#include "model3d.hpp"
#include "openglwidget.hpp"

OpenGLWidget::OpenGLWidget(QWidget *parent, Qt::WindowFlags f):
    QOpenGLWidget(parent, f),
    xRot(0),
    yRot(0),
    zRot(0)
{
}

OpenGLWidget::~OpenGLWidget()
{
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    initializeOpenGLDebugging();

    qDebug() << context()->format();
    qDebug() << "";
    qDebug() << context()->extensions();
    qDebug() << "";

    glClearColor(0.5f, 0.5f, 0.f, 0.f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    static GLfloat lightPosition[4] = { 0, 2, 10, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    loadModels();
//    prepareShaders();
}

void OpenGLWidget::resizeGL(int width, int height)
{
    const float ratio = static_cast<float>(height) / width;
    const float halfSize = 2;
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //glOrtho(-2, +2, -2, +2, 0.0, 100.0);
    glFrustum(-halfSize, halfSize, -halfSize * ratio, halfSize * ratio, 5.0, 200.0);

    glMatrixMode(GL_MODELVIEW);
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -20.0);
    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);

    for (Model3D &model : _models3D)
    {
        model.render();
    }
}
void OpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    lastMousePosition = event->pos();
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    QPoint positionDiff = lastMousePosition - event->pos();

    yRot -= positionDiff.x();
    xRot -= positionDiff.y();

    lastMousePosition = event->pos();
}

void OpenGLWidget::initializeOpenGLDebugging()
{
    connect(&_debugLogger, &QOpenGLDebugLogger::messageLogged, [](const QOpenGLDebugMessage & message)
    {
        qDebug() << message;
    });

    _debugLogger.initialize();
    _debugLogger.enableMessages();
    _debugLogger.startLogging(QOpenGLDebugLogger::SynchronousLogging);
}

void OpenGLWidget::loadModels()
{
    _models3D.emplace_back(Model3D::fromFile("tank.dae"));

    for (Model3D &model : _models3D)
    {
        model.initialize();
    }
}

void OpenGLWidget::prepareShaders()
{
    _shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, "base.vert");
    qDebug() << _shaderProgram.log();

    _shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, "base.frag");
    qDebug() << _shaderProgram.log();

    _shaderProgram.link();
    qDebug() << _shaderProgram.log();

    _shaderProgram.bind();
}
