#pragma once

#include <QMatrix4x4>

class Model3D;

class Node
{
public:
    Node(Model3D &model);
    ~Node();

    void move(const QVector3D &diff);
    void rotate(float angle, const QVector3D &axis);

    void initializeModel();
    void renderModel();

    const Model3D &getModel() const;

protected:
    void transformGl() const;

    QMatrix4x4 _translation;
    QMatrix4x4 _rotation;

    Model3D &_model;
};
