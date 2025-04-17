#include "ProductsTask.h"
#include "globals.h"
#include "ButtonImpl.h"
#include "ServoMotorImpl.h"
#include <Arduino.h>

const long selectionTime = 5000;
const long makingTime = 10000;

unsigned long tProd;
unsigned long tOff;

ProductsTask::ProductsTask(int prev, int next, int make, int servoPin, int potPin) {
    this->bPrevPin = prev;
    this->bNextPin = next;
    this->bmakePin = make;
    this->servoPin = servoPin;
    this->potPin = potPin;
}

void ProductsTask::init(int period) {
    Task::init(period);
    bPrev = new ButtonImpl(bPrevPin);
    bNext = new ButtonImpl(bNextPin);
    bMake = new ButtonImpl(bmakePin);
    lcd = new Lcd(0x27);
    servo = new ServoMotorImpl(servoPin);
    pot = new Pot(potPin);
    state = IDLE;
}

void ProductsTask::tick() {

    switch(state) {

        case IDLE:
            if (millis() - tOff > 800) {
                servo->off();
            }
            if (bNext->isPressed() && readyState) {
                tProd = millis();
                state = SELECT_COFFEE;
                lcd->displayMsg("COFFEE");
                operatingState = true;
                break;
            } else if (bPrev->isPressed() && readyState) {
                tProd = millis();
                state = SELECT_CHOC;
                lcd->displayMsg("CHOCOLATE");
                operatingState = true;
                break;
            } else {
                break;
            }

        case SELECT_COFFEE:
            if (millis() - tProd > selectionTime) {
                state = IDLE;
                lcd->displayMsg("Ready");
                operatingState = false;
                break;
            } else if (bNext->isPressed()) {
                tProd = millis();
                state = SELECT_TEA;
                lcd->displayMsg("TEA");
                break;
            } else if (bPrev->isPressed()) {
                tProd = millis();
                state = SELECT_CHOC;
                lcd->displayMsg("CHOCOLATE");
                break;
            } else if (bMake->isPressed() && nMaxCoffee > 0) {
                tProd = millis();
                servo->on();
                state = MAKING_COFFEE;
                lcd->displayMsg("Making a coffee...");
                nMaxCoffee--;
                sugarLevel = pot->getValue();
                break;
            } else {
                break;
            }

        case SELECT_TEA:
            if (millis() - tProd > selectionTime) {
                state = IDLE;
                lcd->displayMsg("Ready");
                operatingState = false;
                break;
            } else if (bNext->isPressed()) {
                tProd = millis();
                state = SELECT_CHOC;
                lcd->displayMsg("CHOCOLATE");
                break;
            } else if (bPrev->isPressed()) {
                tProd = millis();
                state = SELECT_COFFEE;
                lcd->displayMsg("COFFEE");
                break;
            } else if (bMake->isPressed() && nMaxTea > 0) {
                tProd = millis();
                servo->on();
                state = MAKING_TEA;
                lcd->displayMsg("Making a tea...");
                nMaxTea--;
                sugarLevel = pot->getValue();
                break;
            } else {
                break;
            }

        case SELECT_CHOC:
            if (millis() - tProd > selectionTime) {
                state = IDLE;
                lcd->displayMsg("Ready");
                operatingState = false;
                break;
            } else if (bNext->isPressed()) {
                tProd = millis();
                state = SELECT_COFFEE;
                lcd->displayMsg("COFFEE");
                break;
            } else if (bPrev->isPressed()) {
                tProd = millis();
                state = SELECT_TEA;
                lcd->displayMsg("TEA");
                break;
            } else if (bMake->isPressed() && nMaxChoc > 0) {
                tProd = millis();
                servo->on();
                state = MAKING_CHOC;
                lcd->displayMsg("Making a chocolate");
                nMaxChoc--;
                sugarLevel = pot->getValue();
                break;
            } else {
                break;
            }

        case MAKING_COFFEE:
            if (millis() - tProd > makingTime) {
                lcd->displayMsg("The coffee is ready");
                tProd = millis();
                state = PRODUCT_READY;
                productReady = true;
                break;
            } else {
                servo->setPosition(180 * (millis() - tProd) / makingTime);
                break;
            }

        case MAKING_TEA:
            if (millis() - tProd > makingTime) {
                lcd->displayMsg("The tea is ready");
                tProd = millis();
                state = PRODUCT_READY;
                productReady = true;
                break;
            } else {
                servo->setPosition(180 * (millis() - tProd) / makingTime);
                break;
            }

        case MAKING_CHOC:
            if (millis() - tProd > makingTime) {
                lcd->displayMsg("The chocolate is ready");
                tProd = millis();
                state = PRODUCT_READY;
                productReady = true;
                break;
            } else {
                servo->setPosition(180 * (millis() - tProd) / makingTime);
                break;
            }

        case PRODUCT_READY:
            if (productTaken) {
                state = IDLE;
                operatingState = false;
                servo->setPosition(0);
                lcd->displayMsg("Ready");
                tOff = millis();
                break;
            } else {
                break;
            }
    }
}
