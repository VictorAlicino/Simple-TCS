//
// Created by victo on 01/10/2021.
//
#include <Arduino.h>
#include <WiFi.h>
#include <Preferences.h>
#include <DNSServer.h>
#include <Connections.h>
#include <UserConfig.h>
#include <Hardware.h>

extern String device_name;
extern String ssid;
extern String pass;
extern int WIFI_CONNECTION_STATUS;

struct network_connection_error: public std::exception
{
    const char * what () const noexcept override
    {
        return "Network Connection Error";
    }
};

struct mqtt_connection_error: public std::exception
{
    const char * what () const noexcept override
    {
        return "MQTT Connection Error";
    }
};


void wifi_connect(){
    try{
        WiFi.begin(ssid.c_str(), pass.c_str());
        ESP_LOGD(TAG, "Connecting to WiFi");
        const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;

        //Waiting first connection attempt
        vTaskDelay(xDelay*5);

        //If first attempt was not successfully made, this loop will start a counter to a predefined number of attempts
        //WIFI_ATTEMPTS Macro is used in here
        for(int counter = 0; WiFiClass::status() != WL_CONNECTED && counter < WIFI_ATTEMPTS; counter++){
            vTaskDelay(xDelay*5);
            ESP_LOGE(TAG, "Connection Failed! %d Attempts remaining!", WIFI_ATTEMPTS - counter);
            ESP_LOGD(TAG, "Retrying...");
        }
        //If after all attempts the connection was not successfully made, an Exception is thrown
        if(WiFiClass::status() != WL_CONNECTED){
            ESP_LOGE(TAG, "Connection failed after %d attempts.", WIFI_ATTEMPTS);
            throw network_connection_error();
        }else{
            //Connection made with success
            WIFI_CONNECTION_STATUS = CONNECTED;
            ESP_LOGD(TAG, "Connected");
        }
    }catch(std::exception& e){
        //An error has occurred during connection
        WIFI_CONNECTION_STATUS = NOT_READY;
        ESP_LOGE(TAG, "Network Connection Error -> Throwing Exception.");
        throw e;
    }
}

IPAddress activate_internal_wifi(){
    //Setting Hotspot name
    ESP_LOGD(TAG, "Initializing Internal Wireless Network");
    String name = "LabIoT TCS ";
    name = name + "(" + device_name + ")";

    //Setting device in Access Point + Station Mode
    WiFiClass::mode(WIFI_AP_STA);
    WiFi.softAP(name.c_str(), nullptr);
    IPAddress IP = WiFi.softAPIP();

    //Setting Hostname
    WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
    WiFi.setHostname(name.c_str());
    ESP_LOGI(TAG, "Configuration Access Point set on %s", IP.toString().c_str());
    return IP;
}

String get_mac_address(){
    uint8_t baseMac[6];
    //Get MAC address for Wi-Fi station
    esp_read_mac(baseMac, ESP_MAC_WIFI_STA);
    char baseMacChr[18] = {0};
    sprintf(baseMacChr, "%02X:%02X:%02X:%02X:%02X:%02X", baseMac[0], baseMac[1], baseMac[2], baseMac[3], baseMac[4], baseMac[5]);
    return {baseMacChr};
}
