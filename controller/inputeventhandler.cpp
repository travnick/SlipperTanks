#include <QMouseEvent>
#include <QVector3D>

#include "model/camera.hpp"
#include "model/player.hpp"
#include "inputeventhandler.hpp"

InputEventHandler::InputEventHandler(Player &player):
    _camera(nullptr),
    _player(player),
    _wheelRotationAngle(0)
{
}

void InputEventHandler::onMousePressEvent(QMouseEvent &event)
{
    _lastMousePosition = event.pos();
}

void InputEventHandler::onMouseMoveEvent(QMouseEvent &event)
{
    static const QVector3D Xaxis(1, 0, 0);
    static const QVector3D Yaxis(0, 1, 0);

    QPoint positionDiff = _lastMousePosition - event.pos();
    float yRotation = positionDiff.x() / 3.6f;
    float xRotation = positionDiff.y() / 3.6f;

    _camera->rotate(-xRotation, Xaxis);
    _camera->rotate(-yRotation, Yaxis);

    _lastMousePosition = event.pos();
}

void InputEventHandler::onWheelEvent(QWheelEvent &event)
{
    _wheelRotationAngle += event.angleDelta().y();
}

void InputEventHandler::onKeyPressEvent(QKeyEvent &event)
{
    _keysPressed.insert(event.key());
}

void InputEventHandler::onKeyReleaseEvent(QKeyEvent &event)
{
    _keysPressed.erase(event.key());
}

void InputEventHandler::processEvents(float secondsElapsed)
{
    const int DirectionValue = 1;
    QVector3D cameraMoveDirection;
    QVector3D playerMoveDirection;

    if (_wheelRotationAngle > 1 || _wheelRotationAngle < -1)
    {
        cameraMoveDirection.setZ(cameraMoveDirection.z() + _wheelRotationAngle / 180.f);
        _wheelRotationAngle = 0;
        _camera->move(cameraMoveDirection, secondsElapsed);
    }

    if (_keysPressed.empty())
    {
        return;
    }

    for (int key : _keysPressed)
    {
        switch (key)
        {
            case Qt::Key_Up:
                cameraMoveDirection.setZ(DirectionValue);
                break;
            case Qt::Key_Down:
                cameraMoveDirection.setZ(-DirectionValue);
                break;
            case Qt::Key_Left:
                cameraMoveDirection.setX(DirectionValue);
                break;
            case Qt::Key_Right:
                cameraMoveDirection.setX(-DirectionValue);
                break;

            case Qt::Key_W:
                playerMoveDirection.setZ(DirectionValue);
                break;
            case Qt::Key_S:
                playerMoveDirection.setZ(-DirectionValue);
                break;
            case Qt::Key_A:
                playerMoveDirection.setX(DirectionValue);
                break;
            case Qt::Key_D:
                playerMoveDirection.setX(-DirectionValue);
                break;
            case Qt::Key_E:
                playerMoveDirection.setY(DirectionValue);
                break;
            case Qt::Key_Q:
                playerMoveDirection.setY(-DirectionValue);
                break;

            default:
                break;
        }
    }

    cameraMoveDirection.normalize();
    playerMoveDirection.normalize();

    _camera->move(cameraMoveDirection, secondsElapsed);
    _player.move(playerMoveDirection, secondsElapsed);
}

void InputEventHandler::setCamera(Camera *camera)
{
    _camera = camera;
}
