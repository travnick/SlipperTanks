#pragma once

#include <set>

#include <QPoint>

#include "utils/commontypedefs.hpp"

struct InputEvents
{
    typedef std::set<int> KeysPressed;

    InputEvents();

    void prepareForNextFrame();
    QPoint getMousePositionDiff() const;

    QPoint _lastFrameMousePosition;
    QPoint _currentMousePosition;
    KeysPressed _keysPressed;
    float _wheelRotationAngle;
};
