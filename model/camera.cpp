#include <GL/gl.h>

#include <QtMath>

#include "camera.hpp"
#include "model3d.hpp"

Camera::Camera():
    _near(0),
    _frustumDepth(0),
    _far(0),
    _ratio(0),
    _fov(0),
    _modelAttachedTo(nullptr)
{
}

void Camera::setFOV(u_int16_t fov)
{
    if (fov > 180)
    {
        fov = 180;
    }

    _fov = fov;
    calibrate();
}

void Camera::setSize(GLfloat width, GLfloat height)
{
    _size.setWidth(width);
    _size.setWidth(height);
}

void Camera::setFrustumDepth(GLfloat depth)
{
    _frustumDepth = depth;
}

void Camera::calibrate()
{
    const GLfloat halfSize = _size.width() / 2.0f;

    GLfloat angle = (180 - _fov) / 2.0f;
    GLfloat focalLength = std::tan(qDegreesToRadians(angle)) * halfSize;
    _near = focalLength;
    _far = _near + _frustumDepth;

    //glOrtho(-halfSize, +halfSize, -halfSize, +halfSize, _near, _far);
    glFrustum(-halfSize, halfSize, -halfSize * _ratio, halfSize * _ratio, _near, _far);
}

void Camera::alignWorldToNear() const
{
    glTranslatef(0, -_size.width() / 2.0f, -_near);
}

void Camera::alignToAttachedModel() const
{
    if (_modelAttachedTo != nullptr)
    {
    }
}

void Camera::setRatio(GLfloat ratio)
{
    _ratio = ratio;
}

void Camera::attachToModel(Model3D *model)
{
    _modelAttachedTo = model;
}

GLfloat Camera::getNear() const
{
    return _near;
}

