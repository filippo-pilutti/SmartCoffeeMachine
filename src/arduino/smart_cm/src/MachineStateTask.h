#ifndef __MACHINESTATETASK__
#define __MACHINESTATETASK__

#include "Task.h"
#include "Lcd.h"

class MachineStateTask: public Task {

private:
    Lcd* lcd;
    enum {
        BOOT,
        READY,
        OPERATING,
        SLEEP,
        ASSISTANCE,
        TESTING
    } state;

public:
    MachineStateTask();
    void init(int period);
    void tick();
};

#endif