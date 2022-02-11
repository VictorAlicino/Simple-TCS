#include <MFRC522.h>
#include <SPI.h>
#include <Arduino.h>
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
    ESP_LOGD(__FILE__, "RFID Chip Initialized");
}

void loop(){
    byte bufferATQA[2];
    byte bufferSize = sizeof(bufferATQA);

    // Reset baud rates
    RFID.PCD_WriteRegister(RFID.TxModeReg, 0x00);
    RFID.PCD_WriteRegister(RFID.RxModeReg, 0x00);
    // Reset ModWidthReg
    RFID.PCD_WriteRegister(RFID.ModWidthReg, 0x26);

    MFRC522::StatusCode result = RFID.PICC_RequestA(bufferATQA, &bufferSize);
    ESP_LOGD(__FILE__, "%d", (int)result);
    if(RFID.PICC_IsNewCardPresent() ){
        ESP_LOGD(__FILE__, "Card Available");
        if(RFID.PICC_ReadCardSerial()) {
            digitalWrite(2, HIGH);
            String UID = (char *) RFID.uid.uidByte;
            ESP_LOGD(__FILE__, "%s", UID);
            digitalWrite(2, LOW);
        }
    }
}