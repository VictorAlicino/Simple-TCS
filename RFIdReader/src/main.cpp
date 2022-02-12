#include <MFRC522.h>
#include <SPI.h>
#include <Arduino.h>
#include <Card.h>
#include <TimeClock.h>
#include <_defs.h>

MFRC522::MIFARE_Key key;

// RFID Chip Status Code
MFRC522::StatusCode status;

MFRC522 RFID(SS_PIN, RST_PIN);

void setup(){

    //Initializing internal LED pin
    pinMode(2, OUTPUT);

    //Initializing RFID Reader
    SPI.begin();
    RFID.PCD_Init();
    ESP_LOGD(__FILE__, "MFRC522 Chip Initialized");
}

void loop(){
    if (RFID.PICC_IsNewCardPresent() ) {
        if (RFID.PICC_ReadCardSerial()) {
            digitalWrite(2, HIGH);
            Card temp(RFID.uid);
            ESP_LOGD(__FILE__, "RFID Detected || UID: %s", temp.to_string().cstring());
            digitalWrite(2, LOW);
        }
    }
}