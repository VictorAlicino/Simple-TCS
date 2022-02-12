//
// Created by victo on 12/02/2022.
//

#ifndef RFIDREADER_CARD_H
#define RFIDREADER_CARD_H
#include "MFRC522.h"


class Card : public MFRC522::Uid {
public:
    explicit Card(MFRC522::Uid UID);
    String to_string(String separator);
};


#endif //RFIDREADER_CARD_H
