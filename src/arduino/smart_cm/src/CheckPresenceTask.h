#ifndef __CHECKPRESENCETASK__
#define __CHECKPRESENCETASK__

#include "Task.h"
#include "Pir.h"

class CheckPresenceTask: public Task {

private:
    int pirPin;
    //Pir* pir;
    enum { IDLE, CHECKING } state;

public:
    CheckPresenceTask(int pirPin);
    void init(int period);
    void tick();
};

#endif