#pragma once

#include <string>

class QVector3D;

struct InputEvents;
class Node;

class Player
{
public:
    Player();
    ~Player();

    const std::string &getRequiredModelName() const;
    void setAttachedNode(Node *attachedModel);

    const Node &getAttachedNode() const;
    Node &getAttachedNode();

    void move(const QVector3D &moveDirection, float seconds);
    void rotate(float angle, const QVector3D &axis);

    void setSpeed(float speed);

private:
    void handleInputEvents(const InputEvents & inputEvents, float secondsElapsed);

    std::string _requiredModelName;
    Node *_attachedNode;
};
