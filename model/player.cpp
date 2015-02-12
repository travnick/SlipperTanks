#include "controller/inputevents.hpp"

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
    using namespace std::placeholders;

    _attachedNode = attachedModel;

    InputEventsHandler inputHandler(std::bind(&Player::handleInputEvents, this, _1, _2));

    _attachedNode->setInputEventsHandler(std::move(inputHandler));
}

const Node &Player::getAttachedNode() const
{
    return *_attachedNode;
}

Node &Player::getAttachedNode()
{
    return *_attachedNode;
}

void Player::move(const QVector3D &moveDirection, float secondsElapsed)
{
    _attachedNode->move(moveDirection, secondsElapsed);
}

void Player::rotate(float angle, const QVector3D &axis)
{
    _attachedNode->rotate(angle, axis);
}

void Player::setSpeed(float speed)
{
    _attachedNode->setSpeed(speed);
}

void Player::handleInputEvents(const InputEvents &inputEvents, float secondsElapsed)
{
//    static const QVector3D Xaxis(1, 0, 0);
    static const QVector3D Yaxis(0, 1, 0);
    const int DirectionValue = 1;
    const float RotationSpeed = 45;

    QVector3D moveDirection;
    float yRotation = 0;

    if (inputEvents._keysPressed.empty())
    {
        return;
    }

    for (int key : inputEvents._keysPressed)
    {
        switch (key)
        {
            case Qt::Key_W:
                moveDirection.setZ(DirectionValue);
                break;
            case Qt::Key_S:
                moveDirection.setZ(-DirectionValue);
                break;
            case Qt::Key_A:
                yRotation += RotationSpeed;
//                moveDirection.setX(DirectionValue);
                break;
            case Qt::Key_D:
                yRotation -= RotationSpeed;
//                moveDirection.setX(-DirectionValue);
                break;
            case Qt::Key_E:
                moveDirection.setY(DirectionValue);
                break;
            case Qt::Key_Q:
                moveDirection.setY(-DirectionValue);
                break;

            default:
                break;
        }
    }

    moveDirection.normalize();

    if(!qFuzzyCompare(yRotation, 0.f))
    {
        rotate(yRotation * secondsElapsed, Yaxis);
    }
    move(moveDirection, secondsElapsed);
}
