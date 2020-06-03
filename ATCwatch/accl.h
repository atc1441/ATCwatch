
#pragma once

#include "Arduino.h"
#include "bma421.h"

struct accl_data_struct {
  float x;
  float y;
  float z;
  float temp;
  uint32_t steps;
  uint16_t result;
  uint8_t activity;
  uint16_t interrupt;
};

void init_accl();
void reset_accl();
void reset_step_counter();
bool acc_input();
bool get_is_looing_at();
accl_data_struct get_accl_data();
void get_accl_int();
uint16_t i2c_reg_write(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t length);
uint16_t i2c_reg_read(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t length);
void delay_ms(uint32_t period);
uint16_t  bma_421_step_counter_init(bma4_dev *dev);
uint16_t write0x7Fto0x40(bma4_dev *dev);
uint16_t bma421_feature_enable1(int feature, int enable, bma4_dev *dev);
uint16_t bma_reset_step_counter(struct bma4_dev *dev);
