#include "SelfTestTask.h"
#include "ServoMotorImpl.h"
#include "globals.h"

const int tempMin = 17;
const int tempMax = 24;

const int tMotorTest = 15000;

unsigned long tt;
bool front;

SelfTestTask::SelfTestTask(int servoPin, int thermoPin) {
    this->servoPin = servoPin;
    this->thermoPin = thermoPin;
}

void SelfTestTask::init(int period) {
    Task::init(period);
    servo = new ServoMotorImpl(servoPin);
    thermo = new TempSensor(thermoPin);
    state = IDLE;
}

void SelfTestTask::tick() {

    switch(state) {

        case IDLE:
            if (!testState) {
                break;
            } else {
                servo->on();
                tt = millis();
                front = true;
                state = TESTMOTOR;
                break;
            }
        
        case TESTMOTOR:
            if (millis() - tt > tMotorTest) {
                state = TESTTEMP;
                break;
            } else {
                if (front) {
                    servo->setPosition(180 * (millis() - tt) / (tMotorTest * 0.9));
                } else {
                    servo->setPosition(0);
                }
                if (millis() - tt > tMotorTest * 0.9) {
                    front = false;
                }
                break;
            }

        case TESTTEMP:
            servo->off();
            int c = thermo->detectTemperature();
            tempOutOfBounds = c < tempMin || c > tempMax;
            testState = false;
            state = IDLE;
            break;
    }
}