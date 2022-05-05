#ifndef HARDWARE_H
#define HARDWARE_H

#include <Arduino.h>

/**
 * ESP32    RC522
 * SCK      18
 * MISO     19
 * SDA      21
 * RST      22
 * MOSI     23
 *
 * GND      GND
 * 3V3      3V3
 */

//Configurações
#define ACTIVATED LOW
#define DEACTIVATED HIGH
//Fim das configurações


typedef unsigned int uint_8t;
enum CONNECTION_STATUS{
    NOT_READY,
    READY_TO_CONNECT,
    CONNECTED
};

enum DEVICE_STATUS{
    IN_PROGRESS,
    READY,
    DONE,
    FAILURE,
    CRITICAL_FAILURE
};

enum MESSAGES_IDENTIFIERS{
    SERVER_RECEIVED         = 0x00,
    DEVICE_SEND             = 0X01,
    DEVICE_GENERIC_ERROR    = 0x02,
};

enum MODE{
};

/**
 * @brief Get the device name
 * 
 * @return String The first two and the last two characters of the MAC Address
 */
String get_device_name();

/**
 * @brief Set up all the hardware connected for use
 * @details
 * 
 */
void activate_hardware();

#endif