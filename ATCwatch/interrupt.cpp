/*
   Copyright (c) 2020 Aaron Christophel

   SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "interrupt.h"
#include "pinout.h"
#include "i2c.h"
#include "menu.h"
#include "sleep.h"
#include "accl.h"
#include "touch.h"
#include "inputoutput.h"
#include "inputoutput.h"
#include "battery.h"

long last_button_press = 0;

bool interrupt_enabled = false;

volatile bool charged_int;
volatile bool charge_int;
volatile bool button_int;
volatile bool touch_int;
volatile bool accl_int;

volatile bool last_button_state;
volatile bool last_charge_state;
volatile bool last_charged_state;
volatile bool last_touch_state;
volatile bool last_accl_state;

#ifdef __cplusplus
extern "C" {
#endif
void GPIOTE_IRQHandler()
{
  if ((NRF_GPIOTE->EVENTS_PORT != 0))
  {
    NRF_GPIOTE->EVENTS_PORT = 0;

    bool button_pin = digitalRead(PUSH_BUTTON_IN);
    if (button_pin != last_button_state) {
      last_button_state = button_pin;
      NRF_GPIO->PIN_CNF[PUSH_BUTTON_IN] &= ~GPIO_PIN_CNF_SENSE_Msk;
      NRF_GPIO->PIN_CNF[PUSH_BUTTON_IN] |= ((last_button_state ? GPIO_PIN_CNF_SENSE_Low : GPIO_PIN_CNF_SENSE_High) << GPIO_PIN_CNF_SENSE_Pos);
      set_button_interrupt();
    }
    bool charge_pin = digitalRead(POWER_INDICATION);
    if (charge_pin != last_charge_state) {
      last_charge_state = charge_pin;
      NRF_GPIO->PIN_CNF[POWER_INDICATION] &= ~GPIO_PIN_CNF_SENSE_Msk;
      NRF_GPIO->PIN_CNF[POWER_INDICATION] |= ((last_charge_state ? GPIO_PIN_CNF_SENSE_Low : GPIO_PIN_CNF_SENSE_High) << GPIO_PIN_CNF_SENSE_Pos);
      set_charge_interrupt();
    }
    bool charged_pin = digitalRead(CHARGE_INDICATION);
    if (charged_pin != last_charged_state) {
      last_charged_state = charged_pin;
      NRF_GPIO->PIN_CNF[CHARGE_INDICATION] &= ~GPIO_PIN_CNF_SENSE_Msk;
      NRF_GPIO->PIN_CNF[CHARGE_INDICATION] |= ((last_charged_state ? GPIO_PIN_CNF_SENSE_Low : GPIO_PIN_CNF_SENSE_High) << GPIO_PIN_CNF_SENSE_Pos);
      set_charged_interrupt();
    }
    bool touch_pin = digitalRead(TP_INT);
    if (touch_pin != last_touch_state) {
      last_touch_state = touch_pin;
      NRF_GPIO->PIN_CNF[TP_INT] &= ~GPIO_PIN_CNF_SENSE_Msk;
      NRF_GPIO->PIN_CNF[TP_INT] |= ((last_touch_state ? GPIO_PIN_CNF_SENSE_Low : GPIO_PIN_CNF_SENSE_High) << GPIO_PIN_CNF_SENSE_Pos);
      if (last_touch_state == false)set_touch_interrupt();
    }
    bool accl_pin = digitalRead(BMA421_INT);
    if (accl_pin != last_accl_state) {
      last_accl_state = accl_pin;
      NRF_GPIO->PIN_CNF[BMA421_INT] &= ~GPIO_PIN_CNF_SENSE_Msk;
      NRF_GPIO->PIN_CNF[BMA421_INT] |= ((last_accl_state ? GPIO_PIN_CNF_SENSE_Low : GPIO_PIN_CNF_SENSE_High) << GPIO_PIN_CNF_SENSE_Pos);
      if (last_accl_state == false)set_accl_interrupt();
    }
  }
  (void)NRF_GPIOTE->EVENTS_PORT;
}
#ifdef __cplusplus
}
#endif

void init_interrupt() {

  NRF_GPIOTE->INTENCLR = GPIOTE_INTENSET_PORT_Msk;
  NVIC_DisableIRQ(GPIOTE_IRQn);
  NVIC_ClearPendingIRQ(GPIOTE_IRQn);
  NVIC_SetPriority(GPIOTE_IRQn, 1);
  NVIC_EnableIRQ(GPIOTE_IRQn);


  NRF_GPIOTE->EVENTS_PORT = 1;
  NRF_GPIOTE->INTENSET = GPIOTE_INTENSET_PORT_Msk;

  if (PUSH_BUTTON_OUT != -1) {
    pinMode(PUSH_BUTTON_OUT, OUTPUT);
    digitalWrite(PUSH_BUTTON_OUT, HIGH);
  }
  pinMode(PUSH_BUTTON_IN, INPUT );
  last_button_state = digitalRead(PUSH_BUTTON_IN);
  NRF_GPIO->PIN_CNF[PUSH_BUTTON_IN] |= ((uint32_t)  (last_button_state ? GPIO_PIN_CNF_SENSE_Low : GPIO_PIN_CNF_SENSE_High)  << GPIO_PIN_CNF_SENSE_Pos);

  pinMode(POWER_INDICATION, INPUT);
  last_charge_state = digitalRead(POWER_INDICATION);
  NRF_GPIO->PIN_CNF[POWER_INDICATION] |= ((uint32_t) (last_charge_state ? GPIO_PIN_CNF_SENSE_Low : GPIO_PIN_CNF_SENSE_High) << GPIO_PIN_CNF_SENSE_Pos);

  pinMode(CHARGE_INDICATION, INPUT);
  last_charged_state = digitalRead(CHARGE_INDICATION);
  NRF_GPIO->PIN_CNF[CHARGE_INDICATION] |= ((uint32_t)  (last_charged_state ? GPIO_PIN_CNF_SENSE_Low : GPIO_PIN_CNF_SENSE_High) << GPIO_PIN_CNF_SENSE_Pos);

  pinMode(TP_INT, INPUT);
  last_touch_state = digitalRead(TP_INT);
  NRF_GPIO->PIN_CNF[TP_INT] |= ((uint32_t)  (last_touch_state ? GPIO_PIN_CNF_SENSE_Low : GPIO_PIN_CNF_SENSE_High) << GPIO_PIN_CNF_SENSE_Pos);

  pinMode(BMA421_INT, INPUT);
  last_accl_state = digitalRead(BMA421_INT);
  NRF_GPIO->PIN_CNF[BMA421_INT] |= ((uint32_t)  (last_accl_state ? GPIO_PIN_CNF_SENSE_Low : GPIO_PIN_CNF_SENSE_High) << GPIO_PIN_CNF_SENSE_Pos);

  interrupt_enabled = true;
}

void gets_interrupt_flag() {
  if (charged_int) {
    charged_int = false;
    interrupt_charged();
  }
  if (charge_int) {
    charge_int = false;
    interrupt_charge();
  }
  if (button_int) {
    button_int = false;
    interrupt_button();
  }
  if (touch_int) {
    touch_int = false;
    interrupt_touch();
  }
  if (accl_int) {
    accl_int = false;
    interrupt_accl();
  }
}

void set_charged_interrupt() {
  charged_int = true;
}

void set_charge_interrupt() {
  charge_int = true;
}

void set_button_interrupt() {
  button_int = true;
}

void set_touch_interrupt() {
  if (!get_i2cReading() && !get_sleep())get_read_touch();
  touch_int = true;
}

void set_accl_interrupt() {
  accl_int = true;
}

void interrupt_charged() {
  sleep_up(WAKEUP_CHARGED);
  set_sleep_time();
  if (get_charged())
    set_led_ms(1000);
  else {
    set_motor_ms();
    display_charging();
  }
}

void interrupt_charge() {
  sleep_up(WAKEUP_CHARGE);
  set_sleep_time();
  if (get_charge())
    set_led_ms(1000);
  else {
    set_motor_ms();
    display_charging();
  }
}

bool button_pressed = false;
long button_press_begin = 0;
void interrupt_button() {
  if (get_button() && (millis() - last_button_press > 200)) {
    last_button_press = millis();
    if (!sleep_up(WAKEUP_BUTTON)) {
      button_pressed = true;
      button_press_begin = millis();
    } else {
      display_home();
      set_motor_ms(40);
      set_sleep_time();
    }
  } else {//button not pressed anymore
    if (button_pressed) {
      button_pressed = false;
      check_button_push(millis() - button_press_begin);
    }
  }
}

void interrupt_touch() {
  set_was_touched(true);
  if (!sleep_up(WAKEUP_TOUCH)) {
    touch_data_struct touch_data = get_touch();
    check_menu(touch_data);
    set_new_touch_interrupt();
  }
  set_sleep_time();
}

void interrupt_accl() {
  sleep_up(WAKEUP_ACCL_INT);
  get_accl_int();
  set_sleep_time();
}

void disable_interrupt() {
  NRF_GPIO->PIN_CNF[PUSH_BUTTON_IN] &= ~GPIO_PIN_CNF_SENSE_Msk;
  NRF_GPIO->PIN_CNF[PUSH_BUTTON_IN] |= (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos);

  NRF_GPIO->PIN_CNF[POWER_INDICATION] &= ~GPIO_PIN_CNF_SENSE_Msk;
  NRF_GPIO->PIN_CNF[POWER_INDICATION] |= (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos);

  NRF_GPIO->PIN_CNF[CHARGE_INDICATION] &= ~GPIO_PIN_CNF_SENSE_Msk;
  NRF_GPIO->PIN_CNF[CHARGE_INDICATION] |= (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos);

  NRF_GPIO->PIN_CNF[TP_INT] &= ~GPIO_PIN_CNF_SENSE_Msk;
  NRF_GPIO->PIN_CNF[TP_INT] |= (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos);

  NRF_GPIO->PIN_CNF[BMA421_INT] &= ~GPIO_PIN_CNF_SENSE_Msk;
  NRF_GPIO->PIN_CNF[BMA421_INT] |= (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos);
  interrupt_enabled = false;
}
