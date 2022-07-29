#pragma once
#include "Event.h"

template <class T>
class EventHandler{
public:
    virtual void onEvent(const T& event) = 0;
};