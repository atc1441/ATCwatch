/*
 * Copyright (c) 2020 Aaron Christophel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "accl.h"
#include "Arduino.h"
#include "i2c.h"
#include "pinout.h"
#include "bma423.h"
//https://github.com/BoschSensortec/BMA423-Sensor-API
//Many Thanks to Daniel Thompson(https://github.com/daniel-thompson/wasp-os) to giving the Hint to use a modified BMA423 Library
#include "watchdog.h"
#include "inputoutput.h"
#include "ble.h"
#include "sleep.h"

struct accl_data_struct accl_data;
bool accl_is_enabled;
static uint8_t dev_addr = BMA4_I2C_ADDR_PRIMARY;
struct bma4_dev bma;
struct bma4_accel_config accel_conf;


void init_accl() {
  pinMode(BMA421_INT, INPUT);

  uint16_t rslt = 0;
  uint8_t init_seq_status = 0;

  watchdog_feed();

  bma.intf = BMA4_I2C_INTF;
  bma.bus_read = user_i2c_read;
  bma.bus_write = user_i2c_write;
  bma.variant = BMA42X_VARIANT;
  bma.intf_ptr = &dev_addr;
  bma.delay_us = user_delay;
  bma.read_write_len = 8;

  accel_conf.odr = BMA4_OUTPUT_DATA_RATE_100HZ;
  accel_conf.range = BMA4_ACCEL_RANGE_2G;
  accel_conf.bandwidth = BMA4_ACCEL_NORMAL_AVG4;
  accel_conf.perf_mode = BMA4_CIC_AVG_MODE;

  unsigned int init_counter = 0;
  do
  {
    watchdog_feed();
    rslt = rslt | do_accl_init();
    if (rslt == 0) {
      accl_is_enabled = true;
      accl_data.result = rslt;
      accl_data.enabled = true;
      return;
    }
  } while (init_counter++ < 5);

  accl_is_enabled = false;
  accl_data.result = rslt;
  accl_data.enabled = false;
}

uint16_t do_accl_init() {
  uint16_t init_rslt = 0;
  reset_accl();
  delay(100);
  init_rslt = init_rslt | bma423_init(&bma);
  delay(20);
  init_rslt = init_rslt | bma423_write_config_file(&bma);
  delay(20);
  init_rslt = init_rslt | bma4_set_accel_enable(1, &bma);
  delay(20);
  init_rslt = init_rslt | bma4_set_accel_config(&accel_conf, &bma);
  delay(20);
  init_rslt = init_rslt | bma423_feature_enable(BMA423_STEP_CNTR | BMA423_STEP_ACT, 1, &bma);//Step Counter and Acticity Feature (Standing, Walking, Running)
  delay(20);
  //init_rslt = init_rslt | bma423_map_interrupt(BMA4_INTR1_MAP,  BMA423_ACTIVITY_INT | BMA423_STEP_CNTR_INT, 1,&bma);
  delay(20);
  //init_rslt = init_rslt | bma423_step_counter_set_watermark(1, &bma);// 1*20 Steps
  delay(20);

  struct bma4_int_pin_config int_pin_config;
  int_pin_config.edge_ctrl = BMA4_LEVEL_TRIGGER;
  int_pin_config.lvl = BMA4_ACTIVE_LOW;
  int_pin_config.od = BMA4_PUSH_PULL;
  int_pin_config.output_en = BMA4_OUTPUT_ENABLE;
  int_pin_config.input_en = BMA4_INPUT_DISABLE;
  bma4_set_int_pin_config(&int_pin_config, BMA4_INTR1_MAP, &bma);

  return init_rslt;
}

void reset_accl() {
  byte standby_value[1] = {0xB6};
  user_i2c_write(dev_addr, 0x7E, standby_value, 1);
}

void reset_step_counter() {
  bma423_reset_step_counter(&bma);
}

int last_y_acc = 0;
bool acc_input() {
  if (!accl_is_enabled)return false;
  struct bma4_accel data;
  bma4_read_accel_xyz(&data, &bma);

#ifdef SWITCH_X_Y // pinetime has 90° rotated Accl
  short tempX = data.x;
  data.x = data.y;
  data.y = tempX;
#endif

  if ((data.x + 335) <= 670 && data.z < 0) {
    if (!get_sleep()) {
      if (data.y <= 0) {
        return false;
      } else {
        last_y_acc = 0;
        return false;
      }
    }
    if (data.y >= 0) {
      last_y_acc = 0;
      return false;
    }
    if (data.y + 230 < last_y_acc) {
      last_y_acc = data.y;
      return true;
    }
  }
  return false;
}

bool get_is_looked_at() {
  if (!accl_is_enabled)return false;
  struct bma4_accel data;
  bma4_read_accel_xyz(&data, &bma);

#ifdef SWITCH_X_Y // pinetime has 90° rotated Accl
  short tempX = data.x;
  data.x = data.y;
  data.y = tempX;
#endif

  if ((data.y + 300) <= 600 && (data.x + 300) <= 600 && data.z < 100)
    return true;
  return false;
}

accl_data_struct get_accl_data() {
  int16_t rslt;
  struct bma4_accel data;
  if (!accl_is_enabled)return accl_data;
  rslt = bma4_read_accel_xyz(&data, &bma);

#ifdef SWITCH_X_Y // pinetime has 90° rotated Accl
  short tempX = data.x;
  data.x = data.y;
  data.y = tempX;
#endif

  accl_data.x = data.x;
  accl_data.y = data.y;
  accl_data.z = data.z;

  bma423_step_counter_output(&accl_data.steps, &bma);

  int32_t get_temp_C;
  rslt = bma4_get_temperature(&get_temp_C, BMA4_DEG, &bma);

  accl_data.temp = get_temp_C / 1000;

  bma423_read_int_status(&accl_data.interrupt, &bma);
  bma423_activity_output(&accl_data.activity, &bma);
  return accl_data;
}

void get_accl_int() {
  if (!accl_is_enabled)return;

}

int8_t user_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t length, void *intf_ptr)
{
  return user_i2c_read(dev_addr, reg_addr, reg_data, length);
}

int8_t user_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t length, void *intf_ptr)
{
  return user_i2c_write(dev_addr, reg_addr, reg_data, length);
}


void user_delay(uint32_t period_us, void *intf_ptr)
{
  delayMicroseconds(period_us);
}
