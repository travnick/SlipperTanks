#include <GL/gl.h>

#include <QtMath>

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
    setSpeed(config._speed);
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

void Camera::adjustWorld() const
{
}

void Camera::alignToAttachedModel() const
{
    if (_nodeAttachedTo != nullptr)
    {
    }
}

void Camera::setViewPortSize(const SizeGL &size)
{
    _viewPortSize = size;
    _nearSize.setAspectRatio(_viewPortSize.getAspectRatio());
}

void Camera::attachToNode(const Node *node)
{
    _nodeAttachedTo = node;
}

QMatrix4x4 Camera::getViewProjectionMatrix() const
{
    return _projectionMatrix * getModelMatrix();
}

QMatrix4x4 Camera::getViewMatrix() const
{
    return getModelMatrix();
}

GLfloat Camera::getNear() const
{
    return _near;
}

const SizeGL &Camera::getViewPortSize() const
{
    return _viewPortSize;
}
