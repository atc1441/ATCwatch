/*
   Copyright (c) 2020 Aaron Christophel

   SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include "Arduino.h"

struct accl_data_struct {
  int16_t x;
  int16_t y;
  int16_t z;
  uint8_t temp;
  uint32_t steps;
  uint8_t activity;
};

void init_accl();
void accl_config_read_write(bool rw, uint8_t addr, uint8_t *data, uint32_t len, uint32_t offset);
void reset_accl();
void reset_step_counter();
uint32_t read_step_data();
bool acc_input();
bool get_is_looked_at();
accl_data_struct get_accl_data();
void update_accl_data();
void accl_write_reg(uint8_t reg, uint8_t data);
uint8_t accl_read_reg(uint8_t reg);
