#include "Lcd.h"
#include <Wire.h>
#include <Arduino.h>
#include "LiquidCrystal_I2C.h"

LiquidCrystal_I2C* lcd;

Lcd::Lcd(int addr) {
    this->addr = addr;
    this->cols = 20;
    this->rows = 4;
    lcd = new LiquidCrystal_I2C(addr, cols, rows);
    lcd->init();
}

void Lcd::displayMsg(char const str[]) {
    lcd->backlight(); 
    lcd->clear();
    lcd->setCursor(1, 1);
    lcd->print(str);
}

void Lcd::turnOn() {
    lcd->on();
    lcd->backlight();
}

void Lcd::turnOff() {
    lcd->clear();
    lcd->noBacklight();
    lcd->off();
}