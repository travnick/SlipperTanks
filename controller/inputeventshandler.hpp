#pragma once

#include "utils/commontypedefs.hpp"

class InputEventsHandler
{
public:
    InputEventsHandler();
    InputEventsHandler(InputEventsHandler &&other);
    InputEventsHandler(const InputEventHandlerFunc &handler, InputEventManager *inputEventManager = nullptr);
    ~InputEventsHandler();

    void operator()(const InputEvents &inputEvents, float secondsElapsed) const;

    InputEventsHandler &operator =(InputEventsHandler &&other);
    InputEventsHandler &operator =(const InputEventHandlerFunc &other);

    void setInputEventManager(InputEventManager *inputEventManager);

private:
    InputEventsHandler(const InputEventsHandler &other);
    InputEventsHandler &operator =(const InputEventsHandler &other);

    InputEventHandlerFunc _handler;
    InputEventManager *_inputEventManager;
};
