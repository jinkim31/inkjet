#ifndef INKJET_STATE_MACHINE_H
#define INKJET_STATE_MACHINE_H

#include <unordered_map>
#include <iostream>
#include <functional>

namespace InkJet
{
struct Transition
{
    int startState;
    int event;

    bool operator==(const Transition &other) const
    {
        return (startState == other.startState && event == other.event);
    }
};
}

namespace std
{
template<>
struct std::hash<InkJet::Transition>
{
    size_t operator()(const InkJet::Transition &key) const
    {
        return key.startState;
    }
};
}

namespace InkJet
{
class StateMachine
{
public:

    StateMachine()
    {
        mVerbose = false;
    }

    void setVerbose(bool verbose)
    {
        mVerbose = verbose;
    }
    void setState(const int& state){mCurrentState = state;}

    StateMachine& addTransition(int sourceState, int event, int destinationState, const std::function<void(void)>& handler=NULL)
    {
        mTransitions.insert({{sourceState, event}, {destinationState, handler}});
        mChainingState = destinationState;
        return *this;
    }

    StateMachine& chainTransition(int event, int destinationState, const std::function<void(void)>& handler=NULL)
    {
        mTransitions.insert({{mChainingState, event}, {destinationState, handler}});
        mChainingState = destinationState;
        return *this;
    }


    int currentState()
    {
        return mCurrentState;
    }
    void notifyEvent(int event)
    {
        Transition t{};
        t.startState = mCurrentState;
        t.event = event;
        const auto& iter = mTransitions.find(t);
        if(iter == mTransitions.end())
            return;

        if(mVerbose)
            std::cout<<"statemachine "<<mCurrentState<<">"<<event<<">"<<iter->second.first<<std::endl;
        const auto& handler = iter->second.second;
        if(handler)
            handler();
        mCurrentState = iter->second.first;

        if(mReservedEvent.has_value())
        {
            int reservedEvent = mReservedEvent.value();
            mReservedEvent = std::nullopt;
            notifyEvent(reservedEvent);
        }
    }

    void reserveEvent(int event)
    {
        mReservedEvent = event;
    }

private:
    int mCurrentState;
    int mChainingState;
    bool mVerbose;
    std::optional<int> mReservedEvent;
    std::unordered_map<Transition, std::pair<int, std::function<void(void)>>> mTransitions;
};
}

#endif