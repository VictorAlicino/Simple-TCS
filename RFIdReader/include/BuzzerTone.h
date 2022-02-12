//
// Created by victo on 30/09/2021.
//

#ifndef V2_BUZZERTONE_H
#define V2_BUZZERTONE_H
#include <Arduino.h>

class Buzzer{
private:
    uint8_t pin;
    uint8_t channel;
    const TickType_t xDelay = 1 / portTICK_PERIOD_MS;
public:
    Buzzer(uint8_t pin, uint8_t channel , uint16_t frequency, uint16_t resolution);

    void startup() const;

    void shutdown();

    void connected() const;

    void disconnected() const;

    void simple_tone(double frequency=1760);

};

#endif //V2_BUZZERTONE_H