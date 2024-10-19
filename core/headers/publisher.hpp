#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <vector>
#include <unordered_map>
#include "ISubscriber.hpp"

using std::vector, std::unordered_map;
class Publisher
{
protected:
    unordered_map<ISubscriber*, int> subscribers;
public:
    Publisher() = default;
    ~Publisher() = default;

    void addSubscriber(ISubscriber* sub)
    {
        subscribers[sub] = 1; //placeholder, using map for fast lookup
    }
    void removeSubscriber(ISubscriber* sub)
    {
        subscribers.erase(sub);
    }
    void notifySubscribers()
    {
        for(std::pair<ISubscriber*, int> sub : subscribers)
            sub.first->update();
    }


};

#endif