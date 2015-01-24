#include "model3d.hpp"

#include "node.hpp"

Node::Node(Model3D &model):
    _model(model)
{
}

Node::~Node()
{
}

void Node::move(const QVector3D &diff)
{
    QVector3D tmp = diff * _rotation;
    _translation.translate(tmp);
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
    glPushMatrix();

    transformGl();

    _model.render();

    glPopMatrix();
}

const Model3D &Node::getModel() const
{
    return _model;
}

void Node::transformGl() const
{
    glMultMatrixf(_rotation.data());
    glMultMatrixf(_translation.data());
}
