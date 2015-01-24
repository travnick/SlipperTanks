#pragma once

#include <GL/gl.h>

#include "node.hpp"
#include "size.hpp"

class Model3D;

typedef Size<GLfloat> SizeGL;

class Camera: public Node
{
public:
    Camera();

    void calibrate();
    void adjustWorld() const;
    void alignToAttachedModel() const;

    void setSize(const SizeGL &size);
    void setViewPortSize(const SizeGL &size);
    void setFOV(u_int16_t fov);
    void setFrustumDepth(GLfloat depth);

    void attachToModel(Model3D *model);

    GLfloat getNear() const;
    const SizeGL &getViewPortSize() const;

private:
    SizeGL _nearSize;
    SizeGL _viewPortSize;

    GLfloat _near;
    GLfloat _frustumDepth;
    GLfloat _far;
    u_int16_t _fov;

    Model3D *_modelAttachedTo;
};
