#pragma once

#include <set>

#include <QPoint>

class QKeyEvent;
class QMouseEvent;
class QWheelEvent;

class Camera;
class Player;

class InputEventHandler
{
public:
    InputEventHandler(Player &player);

    void processEvents(float secondsElapsed);

    void onKeyPressEvent(QKeyEvent &event);
    void onKeyReleaseEvent(QKeyEvent &event);
    void onMousePressEvent(QMouseEvent &event);
    void onMouseMoveEvent(QMouseEvent &event);
    void onWheelEvent(QWheelEvent &event);

    void setCamera(Camera *camera);

private:
    std::set<int> _keysPressed;
    QPoint _lastMousePosition;

    Camera *_camera;
    Player &_player;
    float _wheelRotationAngle;
};
