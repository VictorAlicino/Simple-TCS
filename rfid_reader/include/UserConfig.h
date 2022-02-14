//
// Created by victo on 28/10/2021.
//

#ifndef USERCONFIG_H
#define USERCONFIG_H

// ------------------ Wi-Fi Configurations  ----------------- //
/**
 * Change the SELF_WIFI Macro to "true" if you want the user to input the Wi-Fi Credentials via Webserver
 * or change to false in order to set the Wi-Fi Credentials in compilation time, be advised that errors caused by
 * connection problems will not be treated in the SELF_WIFI false Mode. Be careful.
 */
#define WIFI_SSID           "LabIoT"
#define WIFI_PASSWORD       "labiot2020."

/**
 * The WIFI_ATTEMPTS Macro will define how many times the device should try to connect to Wi-Fi before communicate
 * a failure.
 * This Macro is an Integer. Example: WIFI_ATTEMPTS 5
 */
#define WIFI_ATTEMPTS       5
// -------------- end of WiFi Configurations  -------------- //

// ---------------- Server Configurations  ----------------- //
#define SERVER_URL "http://192.168.1.108:3000"
// ------------- end of Server Configurations  ------------- //

// -------------- General Purpose Input/Output   ----------- //
#define SS_PIN    21
#define RST_PIN   22

#define BUZZER_PIN 5
// --------- end General Purpose Input/Output   ------------ //

#define SIZE_BUFFER     18
#define MAX_SIZE_BLOCK  16

#define TAG __FILE__

#endif //USERCONFIG_H
