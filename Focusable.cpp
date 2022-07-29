#include "Focusable.h"

Focusable::Focusable(){
    m_isFocused = false;
}

const bool Focusable::isFocused() const{
    return m_isFocused;
}

void Focusable::setFocus(const bool focus){
    m_isFocused = focus;
}