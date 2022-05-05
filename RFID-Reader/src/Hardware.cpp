#include <Arduino.h>
#include <utility>
#include <SPI.h>
#include <Hardware.h>
#include <MFRC522.h>
#include <BuzzerTone.h>
#include <UserConfig.h>
#include <esp_system.h>

//Global Variables
extern MFRC522::MIFARE_Key key;
extern Buzzer buzzer;
extern MFRC522::StatusCode status;
extern MFRC522 RFID;
extern String ssid;
extern String pass;
extern String device_name;
//end of Global Variables


String get_device_name(){
	uint8_t baseMac[6];
	esp_read_mac(baseMac, ESP_MAC_WIFI_STA);
	char baseMacChr[18] = {0};
	sprintf(baseMacChr, "%02X%02X", baseMac[0], baseMac[5]);
	return {baseMacChr};
}

void activate_hardware() {
    ESP_LOGD(__FILE__, "Initializing the Hardware");

    //Initializing internal LED pin
    pinMode(2, OUTPUT);
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);

    //Initializing RFID Reader
    SPI.begin();
    ESP_LOGD(TAG, "SPI Protocol Initialized");
    RFID.PCD_Init();
    ESP_LOGD(TAG, "MIFARE RC522 Chip Initialized");

    //Buzzer notification
    buzzer.startup();
}