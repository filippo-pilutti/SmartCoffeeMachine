#ifndef __LCD__
#define __LCD__

class Lcd {

public:
    Lcd(int addr);
    void displayMsg(char const str[]);
    void turnOff();
    void turnOn();

private:
    int addr;
    int rows;
    int cols;
};

#endif