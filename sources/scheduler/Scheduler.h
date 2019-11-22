#pragma once

#include "../Queue.h"


class Scheduler {
public:
    Scheduler();
    virtual void schedulerQueue(/*Queue queue*/)=0;
};
