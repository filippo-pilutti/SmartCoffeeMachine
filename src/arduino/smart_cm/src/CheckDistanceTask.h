#ifndef __CHECKDISTANCETASK__
#define __CHECKDISTANCETASK__

#include "Task.h"
#include "Sonar.h"
#include "ServoMotor.h"

class CheckDistanceTask: public Task {

    int trigPin;
    int echoPin;
    Sonar* sonar;

    enum { IDLE, CHECKING } state;

public:
    CheckDistanceTask(int trig, int echo);
    void init(int period);
    void tick();
};

#endif