#pragma once

#include <QMatrix4x4>

class Model3D;

class Node
{
public:
    Node(Model3D &model);
    ~Node();

    void move(const QVector3D &moveDirection, float seconds);
    void rotate(float angle, const QVector3D &axis);

    void initializeModel();
    void renderModel();

    const Model3D &getModel() const;

    void setSpeed(float speed);
    QMatrix4x4 getModelMatrix() const;
    const QVector3D &getPosition() const;

protected:
    Model3D &_model;

private:
    void transformGl() const;

    QMatrix4x4 _rotation;
    QVector3D _translation;

    float _speed;
};
