#pragma once

#include <functional>
#include <map>
#include <set>

#include <QMatrix4x4>

#include "controller/inputeventshandler.hpp"
#include "utils/commontypedefs.hpp"

class InputEventManager;
class Model3D;

class Node
{
public:
    //    Node(const Node &other);
    Node(Node &&other);
    Node(Model3D &model);
    ~Node();

    void move(const QVector3D &moveDirection, float seconds);
    void rotate(float angle, const QVector3D &axis);

    void initializeModel();
    void renderModel();

    const Model3D &getModel() const;

    void setSpeed(float speed);
    QMatrix4x4 getModelMatrix() const;
    const QMatrix4x4 &getRotation() const;
    const QVector3D &getTranslation() const;

    void setInputEventManager(InputEventManager *inputEventManager);
    void setInputEventsHandler(InputEventsHandler &&inputEventsHandler);

protected:
    const InputEventsHandler &getInputEventsHandler() const;

    QMatrix4x4 _rotation;
    QVector3D _translation;

    InputEventsHandler _inputEventsHandler;
    Model3D &_model;
    float _speed;
};
