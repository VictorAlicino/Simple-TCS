//
// Created by victo on 12/02/2022.
//

#include "TimeClock.h"
#include <cppQueue.h>

Card::Card(MFRC522::Uid UID) : MFRC522::Uid{UID}{}

String Card::to_string(String separator) {
    String UID = "";
    for (byte i = 0; i < this->size; i++)
    {
        UID.concat(String(this->uidByte[i] < 0x10 ? (separator + "0") : separator));
        UID.concat(String(this->uidByte[i], HEX));
    }
    return UID;
}
