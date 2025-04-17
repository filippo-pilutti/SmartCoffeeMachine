#include "MachineStateTask.h"
#include "globals.h"
#include <Arduino.h>
#include "avr/sleep.h"

const long sleepTime = 60000;
const long initTime = 2000;
const unsigned long tCheck = 180000;

unsigned long tm;
unsigned long int tTest;
bool firstBoot;

bool productsFinished() {
    return nMaxCoffee == 0 && nMaxTea == 0 && nMaxChoc == 0;
}

MachineStateTask::MachineStateTask() {
}

void MachineStateTask::init(int period) {
    Task::init(period);
    lcd = new Lcd(0x27);
    tTest = millis();
    state = BOOT;
    firstBoot = true;
}

void MachineStateTask::tick() {

    switch(state) {

        case BOOT:
            if (firstBoot) {
                lcd->displayMsg("Welcome, booting...");
                nMaxCoffee = NCOFFEE;
                nMaxTea = NTEA;
                nMaxChoc = NCHOC;
                nSelfTests = 0;
                firstBoot = false;
                tm = millis();
            }
            if (millis() - tm > initTime) {
                lcd->displayMsg("Ready");
                readyState = true;
                tm = millis();
                state = READY;
                break;
            } else {
                break;
            }

        case READY:
            if (millis() - tTest > tCheck) {
                readyState = false;
                testState = true;
                lcd->displayMsg("Testing");
                nSelfTests++;
                state = TESTING;
                break;
            } else if (operatingState) {
                readyState = false;
                state = OPERATING;
                break;
            } else if (productsFinished() || tempOutOfBounds) {
                lcd->displayMsg("Assistance required");
                readyState = false;
                assistanceState = true;
                state = ASSISTANCE;
                break;
            } else if (millis() - tm > sleepTime && !userPresent) {
                sleepState = true;
                readyState = false;
                state = SLEEP;
                break;
            } else {
                break;
            }

        case OPERATING:
            if (!operatingState) {
                tm = millis();
                readyState = true;
                state = READY;
                break;
            } else {
                break;
            }

        case ASSISTANCE:
            if (fixed) {
                lcd->displayMsg("Ready");
                tm = millis();
                tTest = millis();
                readyState = true;
                assistanceState = false;
                if (tempOutOfBounds) {
                    tempOutOfBounds = false;
                }
                fixed = false;
                state = READY;
                break;
            } else {
                break;
            }

        case SLEEP:
            lcd->turnOff();
            set_sleep_mode(SLEEP_MODE_PWR_DOWN);
            sleep_enable();
            sleep_mode();
            sleep_disable();
            lcd->turnOn();
            lcd->displayMsg("Ready");
            tm = millis();
            sleepState = false;
            readyState = true;
            state = READY;
            break;

        case TESTING:
            if (!testState) {
                readyState = true;
                tTest = millis();
                lcd->displayMsg("Ready");
                state = READY;
                break;
            } else {
                break;
            }

    }
}