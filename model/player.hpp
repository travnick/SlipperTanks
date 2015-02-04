#pragma once

#include <string>

class QVector3D;

class Node;

class Player
{
public:
    Player();
    ~Player();

    const std::string &getRequiredModelName() const;
    void setAttachedNode(Node *attachedModel);

    const Node &getAttachedNode() const;

    void move(const QVector3D &moveDirection, float seconds);
    void rotate(float angle, const QVector3D &axis);

    void setSpeed(float speed);

private:
    std::string _requiredModelName;
    Node *_attachedNode;
};
