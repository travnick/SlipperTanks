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

void InputEventHandler::processEvents()
{
    const int speed = 1;
    QVector3D cameraPositionDiff;
    QVector3D playerPositionDiff;

    if (_wheelRotationAngle > 1 || _wheelRotationAngle < -1)
    {
        cameraPositionDiff.setZ(cameraPositionDiff.z() + _wheelRotationAngle/180.f);
        _wheelRotationAngle = 0;
        _camera->move(cameraPositionDiff);
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
                cameraPositionDiff.setZ(speed);
                break;
            case Qt::Key_Down:
                cameraPositionDiff.setZ(-speed);
                break;
            case Qt::Key_Left:
                cameraPositionDiff.setX(speed);
                break;
            case Qt::Key_Right:
                cameraPositionDiff.setX(-speed);
                break;

            case Qt::Key_W:
                playerPositionDiff.setZ(speed);
                break;
            case Qt::Key_S:
                playerPositionDiff.setZ(-speed);
                break;
            case Qt::Key_A:
                playerPositionDiff.setX(speed);
                break;
            case Qt::Key_D:
                playerPositionDiff.setX(-speed);
                break;

            default:
                break;
        }
    }

    _camera->move(cameraPositionDiff);
    _player.move(playerPositionDiff);
}

void InputEventHandler::setCamera(Camera *camera)
{
    _camera = camera;
}
