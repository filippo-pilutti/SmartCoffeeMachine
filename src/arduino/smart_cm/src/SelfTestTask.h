#ifndef __SELFTESTTASK__
#define __SELFTESTTASK__

#include "Task.h"
#include "ServoMotor.h"
#include "TempSensor.h"

class SelfTestTask: public Task {

private:
    int servoPin;
    int thermoPin;
    ServoMotor* servo;
    TempSensor* thermo;
    enum {
        IDLE,
        TESTMOTOR,
        TESTTEMP
    } state;

public:
    SelfTestTask(int servoPin, int thermoPin);
    void init(int period);
    void tick();
};

#endif