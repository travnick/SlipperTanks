#include "node.hpp"
#include "player.hpp"

Player::Player():
    _requiredModelName("models/tank.obj"),
    _attachedNode(nullptr)
{
}

Player::~Player()
{
}

const std::string &Player::getRequiredModelName() const
{
    return _requiredModelName;
}

void Player::setAttachedNode(Node *attachedModel)
{
    _attachedNode = attachedModel;
}

const Node &Player::getAttachedNode() const
{
    return *_attachedNode;
}

void Player::move(const QVector3D &diff)
{
    _attachedNode->move(diff);
}

void Player::rotate(float angle, const QVector3D &axis)
{
    _attachedNode->rotate(angle, axis);
}
