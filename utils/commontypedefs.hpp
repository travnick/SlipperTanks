#pragma once

#include <functional>
#include <set>
#include <vector>

class InputEventsHandler;
class InputEventManager;

struct InputEvents;
typedef std::function<void(const InputEvents &inputEvents, float secondsElapsed)> InputEventHandlerFunc;

//typedef std::function<void(const InputEvents &inputEvents, float secondsElapsed)> InputEventHandler;
typedef std::set<const InputEventsHandler *> InputEventsHandlers;
