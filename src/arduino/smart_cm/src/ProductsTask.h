#ifndef __PRODUCTSTASK__
#define __PRODUCTSTASK__

#include "Task.h"
#include "Button.h"
#include "Lcd.h"
#include "ServoMotor.h"
#include "Pot.h"

class ProductsTask: public Task {

private:
    int bPrevPin;
    int bNextPin;
    int bmakePin;
    int servoPin;
    int potPin;
    Button* bPrev;
    Button* bNext;
    Button* bMake;
    Lcd* lcd;
    ServoMotor* servo;
    Pot* pot;
    enum {
        IDLE,
        SELECT_COFFEE,
        SELECT_TEA,
        SELECT_CHOC,
        MAKING_COFFEE,
        MAKING_TEA,
        MAKING_CHOC,
        PRODUCT_READY
    } state;

public:
    ProductsTask(int prevPin, int nextPin, int makePin, int servoPin, int potPin);
    void init(int period);
    void tick();
};

#endif