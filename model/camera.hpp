#pragma once

#include <GL/gl.h>

#include <QRect>

class Model3D;

class Camera
{
public:
    Camera();

    void calibrate();
    void alignWorldToNear() const;
    void alignToAttachedModel() const;

    void setFOV(u_int16_t fov);
    void setSize(GLfloat width, GLfloat height);
    void setFrustumDepth(GLfloat depth);
    void setRatio(GLfloat ratio);

    void attachToModel(Model3D *model);

    GLfloat getNear() const;

private:
    QRect _size;
    GLfloat _near;
    GLfloat _frustumDepth;
    GLfloat _far;
    GLfloat _ratio;
    u_int16_t _fov;

    Model3D *_modelAttachedTo;
};
