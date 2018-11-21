#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include <memory>
#include <vector>

namespace SGE{

class Event{
public:
    std::shared_ptr<int> EntityId;

    enum EventTypes{
        StartTurn,
        EndTurn,
        DrawCard,
        ShuffleDeck,
        AddEnergy,
        DiscardCard,
        ExhaustCard
    };

    EventTypes EventType;
};

class EventQueue;

class Listener{
public:
    int ListenerId;
    void Process(Event& event, EventQueue& eventQueue){};
};

class EventQueue{
public:
    EventQueue();
    virtual ~EventQueue();

    int AddListener(); // returns the listenerid
    void RemoveListener(int listenerId);

    void AddEvent(Event event){
        _eventStack.push_back(event);
    }

    std::vector<Event> GetEvents(){
        return _eventStack;
    }

    void ProcessEvents(){
        while(!_eventStack.empty()){
            Event event = _eventStack.back();
            _eventStack.pop_back();

            if (_listeners.empty() == false){
                for(auto listener : _listeners){
                    listener.Process(event, *this);
                }
            }
        }
    }

private:
    std::vector<Listener> _listeners;
    std::vector<Event> _eventStack;
};



}

#endif // EVENTQUEUE_H
