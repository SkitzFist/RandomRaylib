#include "OnFocus.h"

OnFocus::OnFocus(Focusable* focusObject, bool focus){
    m_focusObject = focusObject;
    m_focus = focus;
}

Focusable* OnFocus::getFocusObject() const{
    return m_focusObject;
}

const bool OnFocus::getFocus() const{
    return m_focus;
}