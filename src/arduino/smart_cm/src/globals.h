#ifndef __GLOBALS__
#define __GLOBALS

#define NCOFFEE  10
#define NTEA  10
#define NCHOC  10

extern bool productReady;
extern bool productTaken;
extern bool userPresent;
extern bool fixed;
extern bool tempOutOfBounds;

extern bool readyState;
extern bool sleepState;
extern bool operatingState;
extern bool testState;
extern bool assistanceState;

extern int nMaxCoffee;
extern int nMaxChoc;
extern int nMaxTea;
extern int sugarLevel;
extern int nSelfTests;

#endif