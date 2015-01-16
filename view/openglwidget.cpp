#include <QDebug>
#include <QMouseEvent>

#include "model/scene.hpp"
#include "openglwidget.hpp"

OpenGLWidget::OpenGLWidget(QWidget *parent_, Qt::WindowFlags f):
    QOpenGLWidget(parent_, f),
    _scene(nullptr)
{
}

OpenGLWidget::~OpenGLWidget()
{
}

void OpenGLWidget::processInput()
{
    const int speed = 1;

    for (int key : _keysPressed)
    {
        switch (key)
        {
            case Qt::Key_W:
                _position.setZ(_position.z() - speed);
                break;
            case Qt::Key_S:
                _position.setZ(_position.z() + speed);
                break;
            case Qt::Key_A:
                _position.setX(_position.x() - speed);
                break;
            case Qt::Key_D:
                _position.setX(_position.x() + speed);
                break;
            default:
                break;
        }
    }
}

void OpenGLWidget::initializeLights()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    static GLfloat lightPosition[4] = { 0, 2, 10, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    initializeOpenGLDebugging();

    _camera.setFOV(90);
    _camera.setSize(2, 2);
    _camera.setFrustumDepth(1000);

    glClearColor(0.5f, 0.5f, 0.f, 0.f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);

    initializeLights();

    //    prepareShaders();

    _scene->initializeModels();
}

void OpenGLWidget::resizeGL(int width_, int height_)
{
    const float ratio = static_cast<float>(height_) / width_;
    glViewport(0, 0, width_, height_);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    _camera.setRatio(ratio);
    _camera.calibrate();

    glMatrixMode(GL_MODELVIEW);
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    _camera.alignWorldToNear();
    _camera.alignToAttachedModel();
    glTranslatef(-_position.x(), -_position.y(), -_position.z());

    glRotatef(_rotation.x() / 4, 1.0, 0.0, 0.0);
    glRotatef(_rotation.y() / 4, 0.0, 1.0, 0.0);
    glRotatef(_rotation.z() / 4, 0.0, 0.0, 1.0);

    _scene->render();
}

void OpenGLWidget::mousePressEvent(QMouseEvent *event_)
{
    _lastMousePosition = event_->pos();
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event_)
{
    QPoint positionDiff = _lastMousePosition - event_->pos();

    _rotation.setY(_rotation.y() - positionDiff.x());
    _rotation.setX(_rotation.x() - positionDiff.y());

    _lastMousePosition = event_->pos();
}

void OpenGLWidget::keyPressEvent(QKeyEvent *event_)
{
    _keysPressed.insert(event_->key());
}

void OpenGLWidget::keyReleaseEvent(QKeyEvent *event_)
{
    _keysPressed.erase(event_->key());
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
