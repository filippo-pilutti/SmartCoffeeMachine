#include <Arduino.h>
#include "Lcd.h"
#include "Scheduler.h"
#include "CheckDistanceTask.h"
#include "ProductsTask.h"
#include "MachineStateTask.h"
#include "CheckPresenceTask.h"
#include "SelfTestTask.h"
#include "SerialCommunicationTask.h"
#include "Task.h"
#include "globals.h"

#define PREV_PIN 12
#define NEXT_PIN 13
#define MAKE_PIN 11
#define SERVO_PIN 9
#define TRIG_PIN 8
#define ECHO_PIN 10
#define PIR_PIN 2
#define TMP_PIN A1
#define POT_PIN A0

Scheduler sched;

bool productReady = false;
bool productTaken = false;
bool userPresent = false;
bool fixed = false;
bool tempOutOfBounds;
bool readyState = false;
bool sleepState = false;
bool operatingState = false;
bool testState = false;
bool assistanceState = false;
int nMaxCoffee;
int nMaxTea;
int nMaxChoc;
int sugarLevel;
int nSelfTests;

void setup() {
  Serial.begin(9600);

  sched.init(100);

  Task* t0 = new CheckDistanceTask(TRIG_PIN, ECHO_PIN);
  t0->init(500);
  t0->setActive(true);
  sched.addTask(t0);

  Task* t1 = new ProductsTask(PREV_PIN, NEXT_PIN, MAKE_PIN, SERVO_PIN, POT_PIN);
  t1->init(100);
  t1->setActive(true);
  sched.addTask(t1);

  Task* t2 = new MachineStateTask();
  t2->init(200);
  t2->setActive(true);
  sched.addTask(t2);

  Task* t3 = new CheckPresenceTask(PIR_PIN);
  t3->init(3000);
  t3->setActive(true);
  sched.addTask(t3);

  Task* t4 = new SelfTestTask(SERVO_PIN, TMP_PIN);
  t4->init(500);
  t4->setActive(true);
  sched.addTask(t4);

  Task* t5 = new SerialCommunicationTask();
  t5->init(500);
  t5->setActive(true);
  sched.addTask(t5);
}

void loop() {
  sched.schedule();
}