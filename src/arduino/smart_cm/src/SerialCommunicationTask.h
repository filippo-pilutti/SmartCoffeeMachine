#ifndef __SERIALCOMMUNICATIONTASK__
#define __SERIALCOMMUNICATIONTASK__

#include "Task.h"
#include "MsgService.h"

class SerialCommunicationTask: public Task {

private:
    enum {
        SHOW_STATE,
        ASSISTANCE
    } state;
    
public:
    SerialCommunicationTask();
    void init(int period);
    void tick();
};

#endif