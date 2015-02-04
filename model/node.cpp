#include "model3d.hpp"

#include "node.hpp"

Node::Node(Model3D &model):
    _model(model),
    _speed(0)
{
}

Node::~Node()
{
}

void Node::move(const QVector3D &moveDirection, float secondsElapsed)
{
    QVector3D tmp = moveDirection * _rotation * _speed * secondsElapsed;
    _translation += tmp;
}

void Node::rotate(float angle, const QVector3D &axis)
{
    QVector3D rotatedAxis = axis;

    //if not rotation about yaw axis then rotate vector
    if (!qFuzzyCompare(axis.y(), 1.f))
    {
        rotatedAxis = rotatedAxis * _rotation;
    }

    _rotation.rotate(angle, rotatedAxis);
}

void Node::initializeModel()
{
    _model.initialize();
}

void Node::renderModel()
{
    _model.render();
}

const Model3D &Node::getModel() const
{
    return _model;
}

void Node::setSpeed(float speed)
{
    _speed = speed;
}

void Node::transformGl() const
{
    glMultMatrixf(_rotation.data());
}

QMatrix4x4 Node::getModelMatrix() const
{
    QMatrix4x4 modelMatrix;

    modelMatrix *= _rotation;
    modelMatrix.translate(_translation);

    return modelMatrix;
}

const QVector3D &Node::getPosition() const
{
    return _translation;
}
