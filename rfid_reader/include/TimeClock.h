//
// Created by victo on 12/02/2022.
//

#ifndef RFIDREADER_TIMECLOCK_H
#define RFIDREADER_TIMECLOCK_H

#include <Arduino.h>
#include <cppQueue.h>
#include <MFRC522.h>

class Card : public MFRC522::Uid {
public:
    explicit Card(MFRC522::Uid UID);
    String to_string(String separator);
};

class TimeClock{
};



#endif //RFIDREADER_TIMECLOCK_H
