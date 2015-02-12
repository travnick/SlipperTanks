#include <utility>

#include <QDebug>
#include <QMouseEvent>

#include "controller/inputeventmanager.hpp"
#include "model/player.hpp"
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

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    initializeOpenGLDebugging();

    _camera.calibrate();

    glClearColor(77 / 256.f, 153 / 256.f, 228 / 256.f, 0.f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(1);
    glShadeModel(GL_SMOOTH);

    prepareShaders();

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

//    _camera.alignToAttachedModel();
    _shaderProgram.bind();

    _shaderProgram.setUniformValue(20, _camera.getTranslation());

    _scene->render(_shaderProgram, _camera.getViewProjectionMatrix());
}

void OpenGLWidget::mousePressEvent(QMouseEvent *event_)
{
    _inputEventManager->onMousePressEvent(*event_);
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event_)
{
    _inputEventManager->onMouseMoveEvent(*event_);
}

void OpenGLWidget::wheelEvent(QWheelEvent *event_)
{
    _inputEventManager->onWheelEvent(*event_);
}

void OpenGLWidget::keyPressEvent(QKeyEvent *event_)
{
    _inputEventManager->onKeyPressEvent(*event_);
}

void OpenGLWidget::keyReleaseEvent(QKeyEvent *event_)
{
    _inputEventManager->onKeyReleaseEvent(*event_);
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
}

void OpenGLWidget::prepareShaders()
{
    QObject::connect(&_filesystemWatcher, &QFileSystemWatcher::fileChanged, [this](const QString & path)
    {
        //needed because some editors removes and creates new file so file watcher stops working.
        _filesystemWatcher.removePath(path);
        _filesystemWatcher.addPath(path);

        qDebug() << "file watch: " << path;
        std::string filePath = path.toStdString();

        std::unique_ptr<QOpenGLShader> &oldShader = this->_shaders.at(filePath);
        std::unique_ptr<QOpenGLShader> newShader;
        newShader.reset(new QOpenGLShader(oldShader->shaderType()));
        bool compiled = newShader->compileSourceFile(path);

        if (compiled)
        {
            this->_shaderProgram.removeShader(oldShader.get());
            this->_shaderProgram.addShader(newShader.get());

            oldShader.swap(newShader);

            this->_shaderProgram.link();
            qDebug() << "link log: " << this->_shaderProgram.log();
        }
    });

    {
        std::unique_ptr<QOpenGLShader>shader;
        shader.reset(new QOpenGLShader(QOpenGLShader::Vertex));

        auto vertexShaderIt = _shaders.emplace("base.vert", std::move(shader)).first;

        shader.reset(new QOpenGLShader(QOpenGLShader::Fragment));
        auto fragmentShaderIt = _shaders.emplace("base.frag", std::move(shader)).first;

        _filesystemWatcher.addPath(QString::fromStdString(vertexShaderIt->first));
        _filesystemWatcher.addPath(QString::fromStdString(fragmentShaderIt->first));
    }

    for (auto &shader : _shaders)
    {
        bool compiled = shader.second->compileSourceFile(QString::fromStdString(shader.first));
        qDebug() << shader.second->log();

        if (compiled)
        {
            _shaderProgram.addShader(shader.second.get());
        }
    }

    _shaderProgram.link();
    qDebug() << _shaderProgram.log();
}

void OpenGLWidget::setScene(Scene *scene)
{
    _scene = scene;
}

void OpenGLWidget::setInputEventHandler(InputEventManager *inputEventHandler)
{
    _inputEventManager = inputEventHandler;
    _camera.setInputEventManager(_inputEventManager);
}

void OpenGLWidget::attachCameraToPlayer(Player &player)
{
    _camera.attachToNode(&player.getAttachedNode());
}
