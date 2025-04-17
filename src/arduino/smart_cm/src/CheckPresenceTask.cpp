#include "CheckPresenceTask.h"
#include "globals.h"
#include <Arduino.h>

void wakeUp() {}

CheckPresenceTask::CheckPresenceTask(int pirPin) {
    this->pirPin = pirPin;
}

void CheckPresenceTask::init(int period) {
    Task::init(period);
    state = IDLE;
}

void CheckPresenceTask::tick() {

    switch(state) {

        case IDLE:
            if (readyState || sleepState) {
                userPresent = false;
                state = CHECKING;
                attachInterrupt(digitalPinToInterrupt(pirPin), wakeUp, RISING);
                break;
            } else {
                break;
            }

        case CHECKING:
            if (!readyState && !sleepState) {
                state = IDLE;
                detachInterrupt(pirPin);
                break;
            } else {
                userPresent = digitalRead(pirPin) == HIGH;
                break;
            }
    }
}