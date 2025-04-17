#include <Arduino.h>
#include "Pot.h"

Pot::Pot(int p) {
    this->pin = p;
}

int Pot::getValue() {
    int val = analogRead(pin);
    return map(val, 0, 1023, 0, 10);
}