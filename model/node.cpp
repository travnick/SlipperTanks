#include "controller/inputeventmanager.hpp"

#include "model3d.hpp"

#include "node.hpp"

//Node::Node(const Node &other):
//    _inputEventsHandler(),
//    _model(other._model),
//    _rotation(other._rotation),
//    _translation(other._translation),
//    _speed(other._speed)
//{
//}

Node::Node(Node &&other):
    _rotation(std::move(other._rotation)),
    _translation(std::move(other._translation)),
    _inputEventsHandler(std::move(other._inputEventsHandler)),
    _model(other._model),
    _speed(std::move(other._speed))
{
}

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
    QVector3D tmp = _rotation * moveDirection * (_speed * secondsElapsed);
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

void Node::setInputEventManager(InputEventManager *inputEventManager)
{
    _inputEventsHandler.setInputEventManager(inputEventManager);
}

QMatrix4x4 Node::getModelMatrix() const
{
    QMatrix4x4 modelMatrix;

    modelMatrix.translate(_translation);
    modelMatrix *= _rotation;

    return modelMatrix;
}

const QMatrix4x4 &Node::getRotation() const
{
    return _rotation;
}

const QVector3D &Node::getTranslation() const
{
    return _translation;
}

const InputEventsHandler &Node::getInputEventsHandler() const
{
    return _inputEventsHandler;
}

void Node::setInputEventsHandler(InputEventsHandler &&inputEventsHandler)
{
    _inputEventsHandler = std::move(inputEventsHandler);
}
