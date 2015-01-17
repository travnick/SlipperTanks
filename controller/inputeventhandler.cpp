#include <QMouseEvent>
#include <QVector3D>

#include "model/camera.hpp"
#include "inputeventhandler.hpp"

InputEventHandler::InputEventHandler()
{
}

void InputEventHandler::onMousePressEvent(QMouseEvent &event)
{
    _lastMousePosition = event.pos();
}

void InputEventHandler::onMouseMoveEvent(QMouseEvent &event)
{
    QPoint positionDiff = _lastMousePosition - event.pos();

    QVector3D rotationDiff(positionDiff.y(), positionDiff.x(), 0);
    _camera->rotate(rotationDiff);

    _lastMousePosition = event.pos();
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
    QVector3D positionDiff;

    for (int key : _keysPressed)
    {
        switch (key)
        {
            case Qt::Key_Up:
                positionDiff.setZ(-speed);
                break;
            case Qt::Key_Down:
                positionDiff.setZ(speed);
                break;
            case Qt::Key_Left:
                positionDiff.setX(-speed);
                break;
            case Qt::Key_Right:
                positionDiff.setX(speed);
                break;
            default:
                break;
        }
    }

    _camera->move(positionDiff);
}

void InputEventHandler::setCamera(Camera *camera)
{
    _camera = camera;
}

void InputEventHandler::setPlayer(Node *player)
{
    _player = player;
}
