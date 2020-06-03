
#include "accl.h"
#include "Arduino.h"
#include <Wire.h>
#include "pinout.h"
#include "bma421.h"
#include "watchdog.h"
#include "inputoutput.h"
#include "ble.h"
#include "sleep.h"

uint8_t reset_register = 0xB6;

struct bma4_dev dev;
struct bma4_accel_config conf;
struct accl_data_struct accl_data;
bool accl_is_enabled;

void init_accl() {
  pinMode(BMA421_INT, INPUT);
  Wire.begin();
  Wire.setClock(200000);

  uint16_t rslt = 0;
  uint8_t init_seq_status = 0;

  watchdog_feed();

  dev.dev_addr = BMA4_I2C_ADDR_PRIMARY;
  dev.interface = BMA4_I2C_INTERFACE;
  dev.bus_read = i2c_reg_read;
  dev.bus_write = i2c_reg_write;
  dev.delay = delay_ms;
  dev.read_write_len = 8;
  dev.resolution = 12;
  dev.feature_len = 0x40;

  conf.odr = BMA4_OUTPUT_DATA_RATE_50HZ;
  conf.range = BMA4_ACCEL_RANGE_4G;
  conf.bandwidth = BMA4_ACCEL_NORMAL_AVG4;
  conf.perf_mode = BMA4_CONTINUOUS_MODE;


  rslt = rslt | bma421_init(&dev);

  delay(50);

  i2c_reg_write(0x18, 0x7E, &reset_register, 1);

  delay(50);

  rslt = rslt | bma421_write_config_file(&dev);
  delay(20);

  rslt = rslt | bma4_set_accel_config(&conf, &dev);
  rslt = rslt | bma4_set_accel_enable(BMA4_ENABLE, &dev);
  delay(40);

  rslt = rslt | bma421_feature_enable1(BMA421_STEP_CNTR | BMA421_ANY_MOTION | BMA421_ACTIVITY | BMA421_WAKEUP | BMA421_TILT, BMA4_ENABLE, &dev);

  unsigned int v4;
  uint8_t data[64];
  do
  {
    delay(10);
    rslt = bma4_read_regs(0x5Eu, data, 0x40u, &dev);
    v4 = ((unsigned int)data[59] >> 4) & 1;
    delay(1);
  }
  while ( !v4 );
  watchdog_feed();
  do
  {
    rslt = bma421_step_detector_enable(BMA4_ENABLE, &dev);
    delay(10);
    bma4_read_regs(0x5Eu, data, 0x40u, &dev);
    v4 = ((unsigned int)data[59] >> 4) & 1;
    delay(1);
  }
  while ( !v4 );

  rslt = rslt | bma_421_step_counter_init(&dev);
  rslt = rslt | write0x7Fto0x40(&dev);
  delay(10);

  uint8_t v12 = 4;
  do
  {
    v12 = 4;
    bma4_write_regs(0x7D, &v12, 1, &dev);
    delay(1);
    v12 = 0;
    bma4_read_regs(0x7D, &v12, 1, &dev);
  }
  while ( v12 != 4 );
  v12 = 6;
  bma4_write_regs(0x70, &v12, 1, &dev);
  // rslt = rslt | bma421_map_interrupt(BMA4_INTR1_MAP, BMA421_STEP_CNTR_INT | BMA421_ACTIVITY_INT | BMA421_TILT_INT | BMA421_WAKEUP_INT | BMA421_ANY_NO_MOTION_INT | BMA421_ERROR_INT, BMA4_ENABLE, &dev);
  //rslt = rslt | bma421_reset_step_counter(&dev);
  accl_is_enabled = true;
  accl_data.result = rslt;
}

void reset_accl() {
  i2c_reg_write(0x18, 0x7E, &reset_register, 1);
}

void reset_step_counter() {
  uint16_t temp = bma_reset_step_counter(&dev);
}

int last_y_acc = 0;
bool acc_input() {
  if (!accl_is_enabled)return false;
  struct bma4_accel data;
  bma4_read_accel_xyz(&data, &dev);

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

bool get_is_looing_at(){
  if (!accl_is_enabled)return false;
  struct bma4_accel data;
  bma4_read_accel_xyz(&data, &dev);

 #ifdef SWITCH_X_Y // pinetime has 90° rotated Accl
 short tempX = data.x;
 data.x = data.y;
 data.y = tempX;
 #endif
 
  if ((data.y + 300) <= 600 && (data.x + 300) <= 600 && data.z < 0)
      return true;
  return false;
}

accl_data_struct get_accl_data() {
  int16_t rslt;
  struct bma4_accel data;
  if (!accl_is_enabled)return accl_data;
  rslt = bma4_read_accel_xyz(&data, &dev);
  
 #ifdef SWITCH_X_Y // pinetime has 90° rotated Accl
 short tempX = data.x;
 data.x = data.y;
 data.y = tempX;
 #endif
 
  accl_data.x = data.x;
  accl_data.y = data.y;
  accl_data.z = data.z;


  rslt = bma421_step_counter_output(&accl_data.steps, &dev);
  rslt = bma421_activity_output(&accl_data.activity, &dev);

  int32_t get_temp_C;
  rslt = bma4_get_temperature(&get_temp_C, BMA4_DEG, &dev);

  accl_data.temp = get_temp_C / 1000;

  return accl_data;
}

void get_accl_int() {
  if (!accl_is_enabled)return;
  /*accl_data.result = */bma421_read_int_status( &accl_data.interrupt, &dev);
}

uint16_t i2c_reg_write(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t length)
{
  byte error;
  set_i2cReading(true);
  Wire.beginTransmission(i2c_addr);
  Wire.write(reg_addr);
  for (int i = 0; i < length; i++) {
    Wire.write(*reg_data++);
  }
  if ( Wire.endTransmission())return -1;
  set_i2cReading(false);
  return 0;
}

uint16_t i2c_reg_read(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t length)
{
  set_i2cReading(true);
  Wire.beginTransmission(i2c_addr);
  Wire.write(reg_addr);
  if ( Wire.endTransmission())return -1;
  Wire.requestFrom(i2c_addr, length);
  for (int i = 0; i < length; i++) {
    *reg_data++ = Wire.read();
  }
  set_i2cReading(false);
  return 0;
}

void delay_ms(uint32_t period) {
  delay(period);
}

uint16_t  bma_421_step_counter_init(bma4_dev *dev)
{
  uint16_t  rslt;
  struct bma421_stepcounter_settings settings;

  rslt = bma421_stepcounter_get_parameter(&settings, dev);
  if ( !rslt )
  {
    settings.param5 = 5;
    rslt = bma421_stepcounter_set_parameter(&settings, dev);
    delay(20);
  }
  return rslt;
}

uint16_t write0x7Fto0x40(bma4_dev *dev)
{
  uint16_t rslt;
  uint8_t v7;

  v7 = 0;
  if ( dev != NULL)
  {
    rslt = bma4_read_regs(0x7Cu, &v7, 1u, dev);
    if ( !rslt )
    {
      v7 = 3;
      rslt = bma4_write_regs(0x7Cu, &v7, 1u, dev);
      rslt = rslt | bma4_read_regs(0x40u, &v7, 1u, dev);
      if ( !rslt )
      {
        v7 &= 0x7Fu;
        rslt = bma4_write_regs(0x40u, &v7, 1u, dev);
      }
    }
  }
  else
  {
    rslt = 1;
  }
  return rslt;
}

uint16_t bma421_feature_enable1(int feature, int enable, bma4_dev *dev)
{
  uint16_t rslt;
  uint8_t v7;
  uint8_t feature_config[64] = {0};
  if ( !dev )
  {
    rslt = 1;
    return rslt;
  }
  if ( dev->chip_id == 17 )
  {
    rslt = bma4_read_regs(0x5E, feature_config, 0x40, dev);
    if ( rslt )
      return rslt;
    if ( enable == 1 )
    {
      if ( feature & 2 )
        feature_config[3] |= 0xE0u;
      if ( feature & 4 )
        feature_config[7] |= 0xE0u;
      if ( feature << 31 )
        feature_config[59] |= 0x10u;
      if ( feature & 8 )
        feature_config[59] |= 0x20;
    }
    else
    {
      if ( feature & 2 )
        feature_config[3] &= 0x1Fu;
      if ( feature & 4 )
        feature_config[7] &= 0x1Fu;
      if ( feature << 31 )
        feature_config[59] &= 0xEFu;
      if ( feature & 8)
        feature_config[59] &= 0xDF;
    }
    rslt = bma4_write_regs(0x5E, feature_config, 0x40, dev);
    return rslt;
  }
  rslt = 4;
  return rslt;
}

uint16_t bma_reset_step_counter(struct bma4_dev *dev)
{
  uint16_t rslt;
  uint8_t feature_config[64] = {0};
  if ( dev )
  {
    if ( dev->chip_id == 17 )
    {
      rslt = bma4_read_regs(0x5Eu, feature_config, 0x40u, dev);
      if ( !rslt )
      {
        feature_config[59] |= 4u;
        rslt = bma4_write_regs(0x5Eu, feature_config, 0x40u, dev);
      }
    }
    else
    {
      rslt = 4;
    }
  }
  else
  {
    rslt = 1;
  }
  return rslt;
}
