#include <GL/gl.h>

#include <QtMath>

#include "camera.hpp"
#include "emptymodel3d.hpp"
#include "model3d.hpp"

const u_int16_t FOVmin = 1;
const u_int16_t FOVmax = 180;

Camera::Camera():
    Node(EmptyModel3D::getStaticGlobalInstance()),
    _near(0),
    _frustumDepth(0),
    _far(0),
    _fov(0),
    _modelAttachedTo(nullptr)
{
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
    const GLfloat halfSize = _nearSize._width / 2.0f;

    GLfloat angle = (180 - _fov) / 2.0f;
    GLfloat focalLength = std::tan(qDegreesToRadians(angle)) * halfSize;
    _near = focalLength;
    _far = _near + _frustumDepth;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    auto aspectRatio = _viewPortSize.getAspectRatio();
    //glOrtho(-halfSize, +halfSize, -halfSize, +halfSize, _near, _far);
    glFrustum(-halfSize * aspectRatio, halfSize * aspectRatio, -halfSize, halfSize, _near, _far);

    glMatrixMode(GL_MODELVIEW);

    glViewport(0, 0, _viewPortSize._width, _viewPortSize._height);
}

void Camera::adjustWorld() const
{
    transformGl();
}

void Camera::alignToAttachedModel() const
{
    if (_modelAttachedTo != nullptr)
    {
    }
}

void Camera::setViewPortSize(const SizeGL &size)
{
    _viewPortSize = size;
}

void Camera::attachToModel(Model3D *model)
{
    _modelAttachedTo = model;
}

GLfloat Camera::getNear() const
{
    return _near;
}

const SizeGL &Camera::getViewPortSize() const
{
    return _viewPortSize;
}
