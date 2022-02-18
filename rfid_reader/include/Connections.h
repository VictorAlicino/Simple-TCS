//
// Created by victo on 01/10/2021.
//

#ifndef CONNECTIONS_H
#define CONNECTIONS_H

#include <Arduino.h>
#include <WiFi.h>
#include "TimeClock.h"

/**
 * Attempt to connect to the Wi-Fi Network using the global variables credentials
 */
void wifi_connect();

/**
 * Activates the Access Point on the device
 * @return The IP Address of the Access Point
 */
IPAddress activate_internal_wifi();

/**
 * Get the device Mac Address
 * @return Device's Mac Address
 */
String get_mac_address();

void send_rfid_to_api(Card card, const String& URL, const String& path);



#endif //CONNECTIONS_H
