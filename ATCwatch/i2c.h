#pragma once

#include <Arduino.h>
#include "nrf.h"
#include "Stream.h"
#include "RingBuffer.h"

void init_i2c();

//void set_i2cReading(bool state);
bool get_i2cReading();
uint8_t user_i2c_read(uint8_t addr, uint8_t reg_addr, uint8_t *reg_data, uint32_t length);
uint8_t user_i2c_write(uint8_t addr, uint8_t reg_addr, const uint8_t *reg_data, uint32_t length);

void Wire_begin();
void Wire_beginTransmission(uint8_t);
uint8_t Wire_endTransmission(bool stopBit);
uint8_t Wire_requestFrom(uint8_t address, size_t quantity, bool stopBit);
uint8_t Wire_requestFrom(uint8_t address, size_t quantity);
void Wire_write(uint8_t data);
int Wire_read(void);
