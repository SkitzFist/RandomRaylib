#include "FocusManager.h"
#include "Log.h"
#include "EventManager.h"

FocusManager::FocusManager(){
    m_currentlyFocused = nullptr;
    EventManager::addHandler<OnFocus>(this);
}

FocusManager::~FocusManager(){

}

void FocusManager::onEvent(const OnFocus& event){
    if(m_currentlyFocused){
        m_currentlyFocused->setFocus(false);   
    }
    m_currentlyFocused = event.getFocusObject();
    m_currentlyFocused->setFocus(event.getFocus());
}

Focusable* FocusManager::getCurrentFocus() const{
    return m_currentlyFocused;
}