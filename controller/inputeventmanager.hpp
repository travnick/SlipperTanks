#pragma once

#include <QPoint>

#include "utils/commontypedefs.hpp"

#include "inputevents.hpp"

class QKeyEvent;
class QMouseEvent;
class QWheelEvent;

class Camera;
class Player;

class InputEventManager
{
public:
    InputEventManager();

    void processEvents(float secondsElapsed);

    void onKeyPressEvent(QKeyEvent &event);
    void onKeyReleaseEvent(QKeyEvent &event);
    void onMousePressEvent(QMouseEvent &event);
    void onMouseMoveEvent(QMouseEvent &event);
    void onWheelEvent(QWheelEvent &event);

    void addInputEventsHandler(const InputEventsHandler &inputEventHandler);
    void removeInputEventsHandler(const InputEventsHandler &inputEventHandler);

private:
    InputEvents _inputEvents;
    InputEventsHandlers _inputEventsHandlers;

    Player &_player;
};
