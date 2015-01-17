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
    _position += diff;
}

void Node::rotate(const QVector3D &diff)
{
    _rotation += diff;
}

void Node::initializeModel()
{
    _model.initialize();
}

void Node::renderModel()
{
    _model.render();
}
