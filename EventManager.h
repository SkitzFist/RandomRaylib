#pragma once

#include <typeinfo>
#include <vector>
#include <unordered_map>

#include "Object.h"
#include "Log.h"
#include "EventHandler.h"

class Event;

class EventManager{
private: 
    class Registration{
        public:
        Registration(const std::string& eventID);
        std::string m_eventID;
        std::vector<Object*> m_handlers;
    };

public:
    
    static EventManager* getInstance();
    ~EventManager();
    template <typename T> static void const addHandler(Object* handler);
    template <typename T> static void FireEvent(const T& event);
    template <typename T> static void removeHandler(Object* handler);

private:
    EventManager();
    std::unordered_map<std::string, Registration*> eventMap;
    const bool idExists(std::string id) const;
    std::vector<std::string> eventIds;
}; 

EventManager::EventManager(){
    
}

EventManager* EventManager::getInstance(){
    static EventManager instance;
    return &instance;
}

EventManager::~EventManager(){
    for(int i = 0; i < eventIds.size(); ++i){
       delete eventMap[eventIds[i]];
    }
}

template<typename T>
void const EventManager::addHandler(Object* handler){ 
    EventManager* instance = getInstance();
    
    EventHandler<T>* pointer = dynamic_cast<EventHandler<T>*>(handler);
    if(pointer == nullptr){
        Log::warning("Incorrect EventHandler");
        return;
    }

    std::string id = typeid(T).name();
    Registration* reg;
    if(!instance->idExists(id)){
        reg = new Registration(id);
        std::pair<std::string, Registration*> r = {id, reg};
        instance->eventMap.insert(r);
        instance->eventIds.emplace_back(id);
        reg->m_handlers.emplace_back(handler);
        Log::info("Registered new Event + handler");
    }else{
        reg = instance->eventMap[id];
        reg->m_handlers.emplace_back(handler);
        Log::info("Registered handler");
    }
}

template <typename T>
void EventManager::removeHandler(Object* handler){
    EventManager* instance = getInstance();
    Registration* reg = instance->eventMap[typeid(T).name()];
    int index = 0;
    bool isFound = false;
    while ( index < reg->m_handlers.size() && !isFound)
    {
        if(reg->m_handlers[index] == handler){
            isFound = true;
            reg->m_handlers.erase(reg->m_handlers.begin() + index);
        }
        ++index;
    }
}

template <typename T> void 
EventManager::FireEvent(const T& event){
    EventManager* instance = getInstance();
    Registration* reg = instance->eventMap[typeid(T).name()];
    Log::info("So far so good");
    for(int i = 0; i < reg->m_handlers.size(); ++i){
        Object* obj = reg->m_handlers[i];
        EventHandler<T>* handler = dynamic_cast<EventHandler<T>*>(obj);
        Log::info("Still good");
        handler->onEvent(event);
    }
}

const bool EventManager::idExists(std::string id) const{
    if(eventMap.find(id) == eventMap.end()){
        return false;
    }
    return true;
}

EventManager::Registration::Registration(const std::string& eventID){
    m_eventID = eventID;
}