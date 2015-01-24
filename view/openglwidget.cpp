#include <QDebug>
#include <QMouseEvent>

#include "controller/inputeventhandler.hpp"
#include "model/scene.hpp"
#include "openglwidget.hpp"

const float CameraSize = 1.f;
const uint16_t CameraFOV = 60;
const float CameraFrustumDepth = 1000.f;

OpenGLWidget::OpenGLWidget(QWidget *parent_, Qt::WindowFlags f):
    QOpenGLWidget(parent_, f),
    _scene(nullptr)
{
}

OpenGLWidget::~OpenGLWidget()
{
}

void OpenGLWidget::initializeLights()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    static GLfloat lightPosition[4] = { 0, 2, 10, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void OpenGLWidget::enableFog()
{
    GLfloat density = 0.02;
    GLfloat fogColor[4] = {0.5, 0.5, 0.5, 1.0};
    GLfloat start = 1000;
    GLfloat end = 5000;

    glEnable(GL_FOG);
    glFogi(GL_FOG_MODE, GL_EXP2);
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogf(GL_FOG_START, start);
    glFogf(GL_FOG_END, end);
    glFogf(GL_FOG_DENSITY, density);
    glHint(GL_FOG_HINT, GL_NICEST);
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    initializeOpenGLDebugging();

    _camera.setFOV(CameraFOV);
    _camera.setSize(SizeGL(CameraSize, CameraSize));
    _camera.setFrustumDepth(CameraFrustumDepth);
    _camera.calibrate();

    glClearColor(77/256.f, 153/256.f, 228/256.f, 0.f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);

    enableFog();

    initializeLights();

    //    prepareShaders();

    _scene->initializeModels();
}

void OpenGLWidget::resizeGL(int width_, int height_)
{
    _camera.setViewPortSize(SizeGL(width_, height_));
    _camera.calibrate();
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    _camera.adjustWorld();
//    _camera.alignToAttachedModel();

    _scene->render();
}

void OpenGLWidget::mousePressEvent(QMouseEvent *event_)
{
    _inputEventHandler->onMousePressEvent(*event_);
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event_)
{
    _inputEventHandler->onMouseMoveEvent(*event_);
}

void OpenGLWidget::wheelEvent(QWheelEvent *event_)
{
    _inputEventHandler->onWheelEvent(*event_);
}

void OpenGLWidget::keyPressEvent(QKeyEvent *event_)
{
    _inputEventHandler->onKeyPressEvent(*event_);
}

void OpenGLWidget::keyReleaseEvent(QKeyEvent *event_)
{
    _inputEventHandler->onKeyReleaseEvent(*event_);
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

    qDebug() << context()->format();
    qDebug() << "";
    qDebug() << context()->extensions();
    qDebug() << "";
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

void OpenGLWidget::setScene(Scene *scene)
{
    _scene = scene;
}

void OpenGLWidget::setInputEventHandler(InputEventHandler *inputEventHandler)
{
    _inputEventHandler = inputEventHandler;
    _inputEventHandler->setCamera(&_camera);
}
