#include "CheckDistanceTask.h"
#include "globals.h"
#include <Arduino.h>

const long timeout = 5000;

unsigned long tCheck;

CheckDistanceTask::CheckDistanceTask(int trig, int echo) {
    this->trigPin = trig;
    this->echoPin = echo;
}

void CheckDistanceTask::init(int period) {
    Task::init(period);
    sonar = new Sonar(trigPin, echoPin);
    state = IDLE;
}

void CheckDistanceTask::tick() {

    switch(state) {
        case IDLE:
        if (productReady) {
            tCheck = millis();
            productTaken = false;
            state = CHECKING;
            break;
        } else {
            break;
        }

        case CHECKING:
            if (sonar->detectDistance() < 0.40 && millis() - tCheck < timeout) {
                break;
            } else {
                productReady = false;
                productTaken = true;
                state = IDLE;
                break;
            }
    }
}