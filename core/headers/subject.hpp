#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
//#include "IObserver.hpp"

class IObserver;

class Subject
{
private:
    std::vector<IObserver*> observers;

public:
    Subject() = default;
    virtual ~Subject() = default;

    void addObserver(IObserver* observer)
    {
        observers.push_back(observer);
    }

    void notifyObservers()
    {
        for (IObserver* observer : observers)
        {
            observer->update(this);
        }
    }
};

#endif // SUBJECT_H