#include "inputeventmanager.hpp"
#include "inputeventshandler.hpp"

InputEventsHandler::InputEventsHandler():
    _handler(nullptr),
    _inputEventManager(nullptr)
{
}

InputEventsHandler::InputEventsHandler(const InputEventsHandler &)
{
}

InputEventsHandler::InputEventsHandler(InputEventsHandler &&other):
    _handler(std::move(other._handler)),
    _inputEventManager(other._inputEventManager)
{
    other._handler = nullptr;
    other._inputEventManager = nullptr;
}

InputEventsHandler::InputEventsHandler(const InputEventHandlerFunc &handler, InputEventManager *inputEventManager):
    _handler(handler),
    _inputEventManager(nullptr)
{
    setInputEventManager(inputEventManager);
}

InputEventsHandler::~InputEventsHandler()
{
    if (_inputEventManager != nullptr)
    {
        _inputEventManager->removeInputEventsHandler(*this);
    }
}

void InputEventsHandler::operator()(const InputEvents &inputEvents, float secondsElapsed) const
{
    _handler(inputEvents, secondsElapsed);
}

InputEventsHandler &InputEventsHandler::operator =(const InputEventsHandler &)
{
    return *this;
}

InputEventsHandler &InputEventsHandler::operator =(InputEventsHandler &&other)
{
    setInputEventManager(other._inputEventManager);

    *this = other._handler;

    return *this;
}

InputEventsHandler &InputEventsHandler::operator =(const InputEventHandlerFunc &other)
{
    if (_inputEventManager != nullptr)
    {
        _inputEventManager->removeInputEventsHandler(*this);
    }

    _handler = other;

    if (_inputEventManager != nullptr && _handler != nullptr)
    {
        _inputEventManager->addInputEventsHandler(*this);
    }

    return *this;
}

void InputEventsHandler::setInputEventManager(InputEventManager *inputEventManager)
{
    if (_inputEventManager != nullptr)
    {
        _inputEventManager->removeInputEventsHandler(*this);
    }

    _inputEventManager = inputEventManager;

    if (_inputEventManager != nullptr && _handler != nullptr)
    {
        _inputEventManager->addInputEventsHandler(*this);
    }
}
