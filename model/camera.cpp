#include <GL/gl.h>

#include <QtMath>

#include "controller/inputevents.hpp"

#include "camera.hpp"
#include "cameraconfig.hpp"
#include "emptymodel3d.hpp"
#include "model3d.hpp"

namespace
{
const u_int16_t FOVmin = 1;
const u_int16_t FOVmax = 180;
}

Camera::Camera(const CameraConfig &config):
    Node(EmptyModel3D::getStaticGlobalInstance()),
    _nearSize(config._nearSize),
    _near(0),
    _frustumDepth(config._frustumDepth),
    _far(_near + _frustumDepth),
    _fov(config.FOV),
    _nodeAttachedTo(nullptr)
{
    using namespace std::placeholders;

    setSpeed(config._speed);

    _inputEventsHandler = std::bind(&Camera::handleInputEvents, this, _1, _2);
}

void Camera::move(const QVector3D &moveDirection, float secondsElapsed)
{
    QVector3D tmp = moveDirection * _rotation * (_speed * secondsElapsed);
    _translation += tmp;
}

void Camera::setFOV(u_int16_t fov)
{
    if (fov > FOVmax)
    {
        fov = FOVmax;
    }
    else if (fov < FOVmin)
    {
        fov = FOVmin;
    }

    _fov = fov;
}

void Camera::setSize(const SizeGL &size)
{
    _nearSize = size;
}

void Camera::setFrustumDepth(GLfloat depth)
{
    _frustumDepth = depth;
}

void Camera::calibrate()
{
    const GLfloat halfwidth = _nearSize._width / 2.0f;
    const GLfloat halfHeight = _nearSize._height / 2.0f;

    const GLfloat angle = static_cast<float>(180 - _fov) / 2.0f;
    const GLfloat focalLength = std::tan(qDegreesToRadians(angle)) * halfwidth;
    _near = focalLength;
    _far = _near + _frustumDepth;

    _projectionMatrix.setToIdentity();
    _projectionMatrix.frustum(-halfwidth, halfwidth, -halfHeight, halfHeight, _near, _far);

    glViewport(0, 0, _viewPortSize._width, _viewPortSize._height);
}

void Camera::setViewPortSize(const SizeGL &size)
{
    _viewPortSize = size;
    _nearSize.setAspectRatio(_viewPortSize.getAspectRatio());
}

void Camera::attachToNode(const Node *node)
{
    _nodeAttachedTo = node;

    _attachedNodeTranslation = QVector3D(0, -3, 0);
    _attachedNodeRotation.setToIdentity();
    _attachedNodeRotation.rotate(180, 0, 1);
}

QMatrix4x4 Camera::getViewProjectionMatrix() const
{
    return _projectionMatrix * getViewMatrix();
}

QMatrix4x4 Camera::getViewMatrix() const
{
    QMatrix4x4 modelMatrix;

    if (_nodeAttachedTo != nullptr)
    {
        QVector3D translation = _nodeAttachedTo->getTranslation();
        translation.setY(-translation.y());

        modelMatrix *= _rotation;
        modelMatrix.translate(translation);
        modelMatrix *= _attachedNodeRotation;
        modelMatrix.translate(_attachedNodeTranslation);
    }
    else
    {
        modelMatrix *= _rotation;
        modelMatrix.translate(_translation);
    }

    return modelMatrix;
}

GLfloat Camera::getNear() const
{
    return _near;
}

const SizeGL &Camera::getViewPortSize() const
{
    return _viewPortSize;
}

QVector3D Camera::getTranslation() const
{
    if (_nodeAttachedTo != nullptr)
    {
        return _nodeAttachedTo->getTranslation() - _attachedNodeTranslation;
    }
    else
    {
        return _translation;
    }
}

void Camera::handleInputEvents(const InputEvents &inputEvents, float secondsElapsed)
{
    static const QVector3D Xaxis(1, 0, 0);
    static const QVector3D Yaxis(0, 1, 0);
    const int DirectionValue = 1;

    QVector3D moveDirection;

    QPoint positionDiff = inputEvents.getMousePositionDiff();
    float yRotation = positionDiff.x() / 3.6f;
    float xRotation = positionDiff.y() / 3.6f;

    this->rotate(-xRotation, Xaxis);
    this->rotate(-yRotation, Yaxis);

    if (inputEvents._wheelRotationAngle > 1 || inputEvents._wheelRotationAngle < -1)
    {
        moveDirection.setZ(moveDirection.z() + inputEvents._wheelRotationAngle / 180.f);
        this->move(moveDirection, secondsElapsed);
    }

    if (inputEvents._keysPressed.empty())
    {
        return;
    }

    for (int key : inputEvents._keysPressed)
    {
        switch (key)
        {
            case Qt::Key_Up:
                moveDirection.setZ(DirectionValue);
                break;
            case Qt::Key_Down:
                moveDirection.setZ(-DirectionValue);
                break;
            case Qt::Key_Left:
                moveDirection.setX(DirectionValue);
                break;
            case Qt::Key_Right:
                moveDirection.setX(-DirectionValue);
                break;

            default:
                break;
        }
    }

    moveDirection.normalize();

    move(moveDirection, secondsElapsed);
}
