#include <Arduino.h>
#include "Sonar.h"

const float vs = 331.45 + 0.62*20;

Sonar::Sonar(int trig, int echo) {
    this->trigPin = trig;
    this->echoPin = echo;
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

float Sonar::detectDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(3);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(trigPin, LOW);

    float tUS = pulseIn(echoPin, HIGH);
    float t = tUS / 1000.0 / 1000.0 / 2;
    float d = t*vs;
    return d;
}