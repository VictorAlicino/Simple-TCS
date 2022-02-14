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
    ssid = WIFI_SSID;
    pass = WIFI_PASSWORD;
    WIFI_CONNECTION_STATUS = READY_TO_CONNECT;

    ESP_LOGD(TAG, "The Wi-Fi Credentials are code locked!");
    ESP_LOGD(TAG, "SSID: %s", ssid.c_str());
    ESP_LOGD(TAG, "Password: %s", pass.c_str());

    /**
    * The system will try to connect to Wi-Fi the number of times defined in WIFI_ATTEMPTS Macro
    * If the connections failed in all attempts, the device will ask in the Serial Port for a Reboot
    */
    int vote = 0; //If Wi-Fi vote positive, the system will finish the configuration
    int counter = 0;

    while(counter < WIFI_ATTEMPTS){
        if(WIFI_CONNECTION_STATUS == READY_TO_CONNECT){
            try{
                wifi_connect();
                vote++;
            }catch(...){
                ESP_LOGE("Wi-Fi Connection Error");
            }
        }
        counter++;
        ESP_LOGD(TAG, "%d connection attempts left before system failure", WIFI_ATTEMPTS - counter);
    }

    //Capturing possible erros
    if(counter == WIFI_ATTEMPTS){
        ESP_LOGE(TAG, "The system tried to connect to Wi-Fi %d times and failed",
                 WIFI_ATTEMPTS);
        ESP_LOGD(TAG, "The following connection(s) failed:");
        if(WIFI_CONNECTION_STATUS != CONNECTED){
            ESP_LOGD(TAG, "Wi-Fi Connection failed");
        }
        ESP_LOGD(TAG, "Restarting Now...");
        ESP.restart();
    }
    //end of Capturing possible erros

    //Initializing HTTP Client
    wifi_client = new WiFiClient();
    http_client = new HTTPClient();

    ESP_LOGD(TAG, "%s successfully initialized", name.c_str());
    buzzer.connected();
}

void loop(){
    if (RFID.PICC_IsNewCardPresent() ) {
        if (RFID.PICC_ReadCardSerial()) {
            digitalWrite(2, HIGH);
            Card temp(RFID.uid);
            send_uid(temp);
            ESP_LOGD(__FILE__, "RFID Detected || UID: %s", temp.to_string().cstring());
            buzzer.simple_tone();
            digitalWrite(2, LOW);
        }
    }
}