//
// Created by victo on 30/09/2021.
//

#include <Arduino.h>
#include <BuzzerTone.h>


Buzzer::Buzzer(uint8_t pin, uint8_t channel, uint16_t frequency, uint16_t resolution) {
    this->pin = pin;
    this->channel = channel;
    ledcSetup(channel, frequency, resolution);
    ledcAttachPin(pin, channel);
}

void Buzzer::startup() const {
    ledcWriteTone(this->channel, 1174);
    vTaskDelay(this->xDelay*230);
    ledcWriteTone(this->channel, 1318);
    vTaskDelay(this->xDelay*230);
    ledcWriteTone(this->channel, 1760);
    vTaskDelay(this->xDelay*500);
    ledcWriteTone(this->channel, 0);
}

void Buzzer::connected() const {
    ledcWriteTone(this->channel, 1318);
    vTaskDelay(this->xDelay*230);
    ledcWriteTone(this->channel, 880);
    vTaskDelay(this->xDelay*230);
    ledcWriteTone(this->channel, 1760);
    vTaskDelay(this->xDelay*230);
    ledcWriteTone(this->channel, 0);
}

void Buzzer::disconnected() const {
    ledcWriteTone(this->channel, 1760);
    vTaskDelay(this->xDelay*230);
    ledcWriteTone(this->channel, 880);
    vTaskDelay(this->xDelay*230);
    ledcWriteTone(this->channel, 1318);
    vTaskDelay(this->xDelay*230);
    ledcWriteTone(this->channel, 0);
}

void Buzzer::shutdown() {
    ledcWriteTone(this->channel, 1760);
    vTaskDelay(this->xDelay*230);
    ledcWriteTone(this->channel, 1318);
    vTaskDelay(this->xDelay*230);
    ledcWriteTone(this->channel, 1174);
    vTaskDelay(this->xDelay*500);
}

void Buzzer::simple_tone(double frequency) {
    ledcWriteTone(this->channel, frequency);
    vTaskDelay(this->xDelay*100);
    ledcWriteTone(this->channel, 0);
}