#pragma once

#include <set>

#include <QPoint>

class QKeyEvent;
class QMouseEvent;

class Camera;
class Node;

class InputEventHandler
{
public:
    InputEventHandler();

    void processEvents();

    void onKeyPressEvent(QKeyEvent &event);
    void onKeyReleaseEvent(QKeyEvent &event);
    void onMousePressEvent(QMouseEvent &event);
    void onMouseMoveEvent(QMouseEvent &event);

    void setCamera(Camera *camera);
    void setPlayer(Node *player);

private:
    std::set<int> _keysPressed;
    QPoint _lastMousePosition;

    Camera *_camera;
    Node *_player;
};
