#pragma once

#include <QVector3D>

class Model3D;

class Node
{
public:
    Node(Model3D &model);
    ~Node();

    void move(const QVector3D &diff);
    void rotate(const QVector3D &diff);

    void initializeModel();
    void renderModel();

protected:
    QVector3D _position;
    QVector3D _rotation;

    Model3D &_model;
};
