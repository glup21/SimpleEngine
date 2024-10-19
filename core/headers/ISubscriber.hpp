#ifndef ISUBSCRIBER_H
#define ISUBSCRIBER_H

class Publisher;

class ISubscriber
{

public:
    ISubscriber() = default;
    virtual void update() = 0;

};

#endif