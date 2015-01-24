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

    void move(const QVector3D &diff);
    void rotate(float angle, const QVector3D &axis);

private:
    std::string _requiredModelName;
    Node *_attachedNode;
};
