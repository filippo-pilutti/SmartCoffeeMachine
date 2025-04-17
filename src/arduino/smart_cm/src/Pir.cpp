#include <Arduino.h>
#include "Pir.h"

Pir::Pir(int p) {
    this->pin = pin;
    pinMode(pin, INPUT);
}

bool Pir::detect() {
    if (digitalRead(pin) == HIGH) {
        return true;
    } else {
        return false;
    }
}