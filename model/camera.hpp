#pragma once

#include <GL/gl.h>

#include <QMatrix4x4>

#include "cameraconfig.hpp"
#include "node.hpp"
#include "size.hpp"

class Model3D;

class Camera: public Node
{
public:
    Camera(const CameraConfig &config = CameraConfig());

    void calibrate();
    void adjustWorld() const;
    void alignToAttachedModel() const;

    void setConfig(const CameraConfig &config);
    void setSize(const SizeGL &size);
    void setViewPortSize(const SizeGL &size);
    void setFOV(u_int16_t fov);
    void setFrustumDepth(GLfloat depth);

    void attachToNode(const Node *node);

    QMatrix4x4 getViewProjectionMatrix() const;
    QMatrix4x4 getViewMatrix() const;
    GLfloat getNear() const;
    const SizeGL &getViewPortSize() const;

private:
    QMatrix4x4 _projectionMatrix;
    SizeGL _nearSize;
    SizeGL _viewPortSize;

    GLfloat _near;
    GLfloat _frustumDepth;
    GLfloat _far;
    u_int16_t _fov;

    const Node *_nodeAttachedTo;
};
