#pragma once

#include "Object.h"
#include "Focusable.h"
#include "EventHandler.h"
#include "OnFocus.h"

class FocusManager : 
    public EventHandler<OnFocus>, public Object{
public:
    FocusManager();
    ~FocusManager();
    void onEvent(const OnFocus& event);
    Focusable* getCurrentFocus() const;
private:
    Focusable* m_currentlyFocused;
};