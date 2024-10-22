#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include <unordered_map>
#include "IObserver.hpp"

using std::vector, std::unordered_map;
class Subject
{
protected:
    unordered_map<IObserver*, int> subscribers;
public:
    Subject() = default;
    ~Subject() = default;

    void addSubscriber(IObserver* sub)
    {
        subscribers[sub] = 1; //placeholder, using map for fast lookup
    }
    void removeSubscriber(IObserver* sub)
    {
        subscribers.erase(sub);
    }
    void notifySubscribers()
    {
        for(std::pair<IObserver*, int> sub : subscribers)
            sub.first->update();
    }


};

#endif