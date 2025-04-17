#include "SerialCommunicationTask.h"
#include "globals.h"

SerialCommunicationTask::SerialCommunicationTask() {}

void SerialCommunicationTask::init(int period) {
    Task::init(period);
    MsgService.init();
    state = SHOW_STATE;
}

void SerialCommunicationTask::tick() {

    switch(state) {

        case SHOW_STATE:
            if (readyState) {
                MsgService.sendMsg("Modality: IDLE");
            } else if (operatingState) {
                MsgService.sendMsg("Modality: OPERATING");
            } else if (testState) {
                MsgService.sendMsg("Modality: TESTING");
            } else if (assistanceState) {
                MsgService.sendMsg("Modality: ASSISTANCE REQUIRED");
            } else {
                break;
            }
            Serial.print("Coffee: ");
            Serial.println(nMaxCoffee);
            Serial.print("Tea: ");
            Serial.println(nMaxTea);
            Serial.print("Chocolate: ");
            Serial.println(nMaxChoc);
            Serial.print("Tests: ");
            Serial.println(nSelfTests);

            if (assistanceState) {
                state = ASSISTANCE;
                break;
            } else {
                break;
            }
            

        case ASSISTANCE:
            if (MsgService.isMsgAvailable()) {
                Msg* msg = MsgService.receiveMsg();
                if (msg->getContent() == "fix" && tempOutOfBounds) {
                    fixed = true;
                    state = SHOW_STATE;
                    delete msg;
                    break;
                } else if (msg->getContent() == "refill" && !tempOutOfBounds) {
                    nMaxCoffee = NCOFFEE;
                    nMaxTea = NTEA;
                    nMaxChoc = NCHOC;
                    fixed = true;
                    state = SHOW_STATE;
                    delete msg;
                    break;
                } else {
                    delete msg;
                    break;
                }
            }
    }
}