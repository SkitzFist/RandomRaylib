#pragma once

#include "Event.h"
#include "Focusable.h"

class OnFocus :
    public Event{
public:
    OnFocus(Focusable* focusObject, bool focus = true);
    Focusable* getFocusObject() const;
    const bool getFocus() const;
private:
    Focusable* m_focusObject;   
    bool m_focus;
};