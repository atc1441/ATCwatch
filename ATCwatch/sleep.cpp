
#include "sleep.h"
#include "Arduino.h"
#include "pinout.h"
#include "display.h"
#include "backlight.h"
#include "heartrate.h"
#include "touch.h"
#include "menu.h"
#include "inputoutput.h"
#include <nrf_nvic.h>//interrupt controller stuff
#include <nrf_sdm.h>
#include <nrf_soc.h>

bool sleep_enable = false;
bool sleep_sleeping = false;
long lastaction = 0;
volatile bool i2cReading = false;

void init_sleep() {
  //sd_power_dcdc_mode_set(NRF_POWER_DCDC_ENABLE);
  sd_power_mode_set(NRF_POWER_MODE_LOWPWR);
}

void set_sleep(bool state) {
  sleep_enable = state;
}

bool get_sleep() {
  return sleep_sleeping;
}

bool sleep_up() {
  if (sleep_sleeping) {
    sleep_sleeping = false;
    set_sleep_time();
    display_enable(true);
    set_backlight();
    return true;
  }
  return false;
}

void sleep_down() {
  if (!sleep_sleeping) {
    sleep_sleeping = true;
    disable_hardware();
  }
}

void disable_hardware() {
  set_backlight(0);
  display_home();
  display_screen(true);
  end_hrs3300();
  set_led(0);
  set_motor(0);
  display_enable(false);
  NRF_SAADC ->ENABLE = 0; //disable ADC
  NRF_PWM0  ->ENABLE = 0; //disable all pwm instance
  NRF_PWM1  ->ENABLE = 0;
  NRF_PWM2  ->ENABLE = 0;
}

void sleep_wait() {
  sd_app_evt_wait();
  sd_nvic_ClearPendingIRQ(SD_EVT_IRQn);
}

void set_sleep_time() {
  lastaction = millis();
}

void check_sleep_times() {
  if (millis() - lastaction > get_sleep_time_menu())
    sleep_down();
}

volatile bool shot;

bool get_timed_int() {
  bool temp = shot;
  shot = false;
  return temp;
}

void set_i2cReading(bool state) {
  i2cReading = state;
}

bool get_i2cReading() {
  return i2cReading;
}

#define LF_FREQUENCY 32768UL
#define SECONDS(x) ((uint32_t)((LF_FREQUENCY * x) + 0.5))
#define wakeUpSeconds 0.040

void initRTC2() {

  NVIC_ClearPendingIRQ(RTC2_IRQn);
  NVIC_SetPriority(RTC2_IRQn, 15);
  NVIC_EnableIRQ(RTC2_IRQn);

  NRF_RTC2->PRESCALER = 0;
  NRF_RTC2->CC[0] = SECONDS(wakeUpSeconds);
  NRF_RTC2->INTENSET = RTC_EVTENSET_COMPARE0_Enabled << RTC_EVTENSET_COMPARE0_Pos;
  NRF_RTC2->EVTENSET = RTC_INTENSET_COMPARE0_Enabled << RTC_INTENSET_COMPARE0_Pos;
  NRF_RTC2->TASKS_START = 1;
}

#ifdef __cplusplus
extern "C" {
#endif
void RTC2_IRQHandler(void)
{
  volatile uint32_t dummy;
  if (NRF_RTC2->EVENTS_COMPARE[0] == 1)
  {
    NRF_RTC2->EVENTS_COMPARE[0] = 0;
    NRF_RTC2->CC[0] = NRF_RTC2->COUNTER +  SECONDS(wakeUpSeconds);
    dummy = NRF_RTC2->EVENTS_COMPARE[0];
    dummy;
    shot = true;
    check_inputoutput_times();
    if (!i2cReading)get_heartrate_ms();
  }
}
#ifdef __cplusplus
}
#endif
