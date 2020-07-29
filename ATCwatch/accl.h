/*
 * Copyright (c) 2020 Aaron Christophel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "Arduino.h"
#include "bma423.h"

struct accl_data_struct {
  int16_t x;
  int16_t y;
  int16_t z;
  int32_t temp;
  uint32_t steps;
  uint16_t result;
  uint8_t activity;
  uint16_t interrupt;
  bool enabled;
};

void init_accl();
uint16_t do_accl_init();
void reset_accl();
void reset_step_counter();
bool acc_input();
bool get_is_looked_at();
accl_data_struct get_accl_data();
void get_accl_int();
int8_t user_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t length, void *intf_ptr);
int8_t user_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t length, void *intf_ptr);
void user_delay(uint32_t period_us, void *intf_ptr);
