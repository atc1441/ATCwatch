/*
 * Copyright (c) 2020 Aaron Christophel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "bootloader.h"
#include "pinout.h"
#include "interrupt.h"
#include "accl.h"
#include "touch.h"
#include "sleep.h"
#include <nrf_nvic.h>//interrupt controller stuff
#include <nrf_sdm.h>
#include <nrf_soc.h>

void init_bootloader() {

}

void start_bootloader(bool without_sd) {
  disable_hardware();
  if (without_sd) {
    NRF_POWER->GPREGRET = 0x01;
    NVIC_SystemReset();
  } else {
    sd_power_gpregret_set(0x01);
    sd_nvic_SystemReset();
  }
  sd_nvic_SystemReset();
  while (1) {};
}

void set_reboot() {
  disable_hardware();
  sd_nvic_SystemReset();
  while (1) {};
}

bool get_sd_enabled() {
  uint8_t is_enabled;
  sd_softdevice_is_enabled(&is_enabled);
  return is_enabled;
}

void system_off()
{
  sleep_touch(true);
  reset_accl();
  disable_interrupt();
  disable_hardware();
  if (PUSH_BUTTON_OUT != -1) {
    pinMode(PUSH_BUTTON_OUT, OUTPUT);
    digitalWrite(PUSH_BUTTON_OUT, HIGH);
  }
  pinMode(PUSH_BUTTON_IN, INPUT );
  NRF_GPIO->PIN_CNF[PUSH_BUTTON_IN] &= ~GPIO_PIN_CNF_SENSE_Msk;
  NRF_GPIO->PIN_CNF[PUSH_BUTTON_IN] |= ((uint32_t)  GPIO_PIN_CNF_SENSE_High  << GPIO_PIN_CNF_SENSE_Pos);

  pinMode(POWER_INDICATION, INPUT);
  NRF_GPIO->PIN_CNF[POWER_INDICATION] &= ~GPIO_PIN_CNF_SENSE_Msk;
  NRF_GPIO->PIN_CNF[POWER_INDICATION] |= ((uint32_t)  GPIO_PIN_CNF_SENSE_Low << GPIO_PIN_CNF_SENSE_Pos);
  sd_power_system_off();
}
