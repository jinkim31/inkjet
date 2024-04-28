#ifndef INKJET_STATE_MACHINE_H
#define INKJET_STATE_MACHINE_H

#define ENUM_STR_PAIR(x) {x, #x}

#include <unordered_map>
#include <iostream>
#include <functional>

namespace inkjet
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
struct std::hash<inkjet::Transition>
{
    size_t operator()(const inkjet::Transition &key) const
    {
        return key.startState;
    }
};
}

namespace inkjet
{
class StateMachine
{
public:

    StateMachine()
    {
        mName = "unnamed state machine";
        mVerbose = false;
    }

    void setVerbose(bool verbose)
    {
        mVerbose = verbose;
    }
    void setState(const int& state){mCurrentState = state;}

    void setName(const std::string& name);

    void setStateNameMap(const std::unordered_map<int, std::string>& stateNameMap){mStateNameMap = stateNameMap;}
    void setEventNameMap(const std::unordered_map<int, std::string>& eventNameMap){mEventNameMap = eventNameMap;}

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
        const auto &iter = mTransitions.find(t);
        if (iter == mTransitions.end())
        {
            if(mVerbose)
                std::cerr<<mName<<": "
                                <<getNameFromMap(mStateNameMap, mCurrentState)
                                <<" > "
                                <<getNameFromMap(mEventNameMap, event)
                                <<" > [NONE]"<<std::endl;
            return;
        }

        if(mVerbose)
            std::cout<<mName<<": "
                     <<getNameFromMap(mStateNameMap, mCurrentState)
                     <<" > "
                     <<getNameFromMap(mEventNameMap, event)
                     <<" > "
                     <<getNameFromMap(mStateNameMap, iter->second.first)
                     <<std::endl;

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
    std::string getNameFromMap(const std::unordered_map<int, std::string>& map, const int& index)
    {
        auto itr = map.find(index);
        if(itr == map.end())
            return "[" + std::to_string(index) + "]";
        return itr->second;
    }

    int mCurrentState;
    int mChainingState;
    bool mVerbose;
    std::string mName;
    std::optional<int> mReservedEvent;
    std::unordered_map<int, std::string> mStateNameMap, mEventNameMap;
    std::unordered_map<Transition, std::pair<int, std::function<void(void)>>> mTransitions;
};
}

#endif