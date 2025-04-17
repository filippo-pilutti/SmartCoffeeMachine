#include "TempSensor.h"
#include <Arduino.h>

TempSensor::TempSensor(int pin) {
    this->pin = pin;
}

double TempSensor::detectTemperature() {
    int value = analogRead(pin);
    int value_in_mV = (5000/1023) * value;
    double value_in_C = (value_in_mV - 500) / 10;
    return value_in_C;
}