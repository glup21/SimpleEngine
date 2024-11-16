#ifndef IOBSERVER_H
#define IOBSERVER_H

//#include "subject.hpp"

class Subject;

class IObserver
{
public:
    IObserver() = default;
    virtual void update(Subject* subject) = 0;
    virtual ~IObserver() = default; 
};

#endif 