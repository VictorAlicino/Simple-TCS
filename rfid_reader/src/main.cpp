#include <MFRC522.h>
#include <Arduino.h>
#include <TimeClock.h>
#include <HTTPClient.h>
#include <BuzzerTone.h>
#include <Connections.h>
#include <UserConfig.h>
#include "Hardware.h"

//Global Variables
MFRC522::MIFARE_Key key;
Buzzer buzzer(BUZZER_PIN, 0, 2000, 10);
MFRC522::StatusCode status;
MFRC522 RFID(SS_PIN, RST_PIN);
String ssid;
String pass;
String device_name;
WiFiClient *wifi_client = nullptr;
HTTPClient *http_client = nullptr;
//end of Global Variables

//Global FLAGS
int WIFI_CONNECTION_STATUS;
int DEVICE_STATUS;
//end of Global FLAGS

void setup(){
    //Setting up name
    device_name = get_device_name();
    String name = "LabIoT TCS ";
    name = name + "(" + device_name + ")";
    WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
    WiFi.setHostname(name.c_str());
    ESP_LOGD(__FILE__, "Device Name: %s", device_name.c_str());

    //Welcome message
    ESP_LOGD(TAG, "Initializing Time Clock Punch-Card System");
    ESP_LOGD(TAG, "Device name: %s", name.c_str());
    ESP_LOGD(TAG, "Device MAC Address: %s", get_mac_address().c_str());

    //Setting Hardware possible configurations
    activate_hardware();

    //Wi-Fi Definitions
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while(WiFiClass::status() != WL_CONNECTED){

    }

    //Initializing HTTP Client
    wifi_client = new WiFiClient();
    http_client = new HTTPClient();

    ESP_LOGD(TAG, "%s successfully initialized", name.c_str());
    buzzer.connected();
}

void loop(){
    if (RFID.PICC_IsNewCardPresent() ) {
        if (RFID.PICC_ReadCardSerial()) {
            const TickType_t xDelay = 10 / portTICK_PERIOD_MS;
            digitalWrite(2, HIGH);
            Card temp(RFID.uid);
            send_rfid_to_api(temp, "http://192.168.1.100:3000", "/");
            ESP_LOGD(__FILE__, "RFID Detected || UID: %s", temp.to_string(":").c_str());
            digitalWrite(13, HIGH);
            buzzer.card_readed();
            digitalWrite(13, LOW);
            digitalWrite(2, LOW);
        }
    }
}