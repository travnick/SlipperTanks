#include "inputevents.hpp"

InputEvents::InputEvents():
    _wheelRotationAngle(0)
{
}

void InputEvents::prepareForNextFrame()
{
    _lastFrameMousePosition = _currentMousePosition;
    _wheelRotationAngle = 0;
}

QPoint InputEvents::getMousePositionDiff() const
{
    return _lastFrameMousePosition - _currentMousePosition;
}
