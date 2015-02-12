#include <QMouseEvent>
#include <QVector3D>

#include "model/camera.hpp"
#include "model/player.hpp"
#include "inputeventmanager.hpp"

InputEventManager::InputEventManager():
    _player(_player)
{
}

void InputEventManager::onMousePressEvent(QMouseEvent &event)
{
    _inputEvents._lastFrameMousePosition = event.pos();
    _inputEvents._currentMousePosition = event.pos();
}

void InputEventManager::onMouseMoveEvent(QMouseEvent &event)
{
    _inputEvents._currentMousePosition = event.pos();
}

void InputEventManager::onWheelEvent(QWheelEvent &event)
{
    _inputEvents._wheelRotationAngle += event.angleDelta().y();
}

void InputEventManager::addInputEventsHandler(const InputEventsHandler &inputEventHandler)
{
    _inputEventsHandlers.insert(&inputEventHandler);
}

void InputEventManager::removeInputEventsHandler(const InputEventsHandler &inputEventHandler)
{
    _inputEventsHandlers.erase(&inputEventHandler);
}

void InputEventManager::onKeyPressEvent(QKeyEvent &event)
{
    _inputEvents._keysPressed.insert(event.key());
}

void InputEventManager::onKeyReleaseEvent(QKeyEvent &event)
{
    _inputEvents._keysPressed.erase(event.key());
}

void InputEventManager::processEvents(float secondsElapsed)
{
    for (auto &handler : _inputEventsHandlers)
    {
        (*handler)(_inputEvents, secondsElapsed);
    }

    _inputEvents.prepareForNextFrame();
}
