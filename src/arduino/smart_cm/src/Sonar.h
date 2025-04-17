#ifndef __SONAR__
#define __SONAR__

class Sonar {

public:
    Sonar(int trig, int echo);
    float detectDistance();

private:
    int trigPin;
    int echoPin;
};

#endif