#pragma once

#include <GL/gl.h>

#include <QRect>

#include "node.hpp"

class Model3D;

class Camera: public Node
{
public:
    Camera();

    void calibrate();
    void adjustWorld() const;
    void alignToAttachedModel() const;

    void setFOV(u_int16_t fov);
    void setSize(GLfloat width, GLfloat height);
    void setFrustumDepth(GLfloat depth);
    void setAspectRatio(GLfloat aspectRatio);

    void attachToModel(Model3D *model);

    GLfloat getNear() const;

private:
    QRect _size;

    GLfloat _near;
    GLfloat _frustumDepth;
    GLfloat _far;
    GLfloat _aspectRatio;
    u_int16_t _fov;

    Model3D *_modelAttachedTo;
};
