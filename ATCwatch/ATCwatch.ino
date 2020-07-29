/*
 * Copyright (c) 2020 Aaron Christophel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "pinout.h"
#include "watchdog.h"
#include "tasks.h"
#include "fast_spi.h"
#include "i2c.h"
#include "bootloader.h"
#include "inputoutput.h"
#include "backlight.h"
#include "battery.h"
#include "heartrate.h"
#include "time.h"
#include "touch.h"
#include "sleep.h"
#include "ble.h"
#include "interrupt.h"
#include "menu.h"
#include "display.h"
#include "accl.h"
#include "push.h"
#include "flash.h"

bool stepsWhereReseted = false;

void setup() {
  delay(500);
  if (get_button()) {//if button is pressed on startup goto Bootloader
    NRF_POWER->GPREGRET = 0x01;
    NVIC_SystemReset();
  }
  init_watchdog();// Init all kind of hardware and software
  initRTC2();
  init_tasks();
  init_bootloader();
  init_fast_spi();//needs to be before init_display and external flash
  init_i2c();//needs to be before init_hrs3300, init_touch and init_accl
  init_inputoutput();
  init_backlight();
  init_display();
  display_booting();
  set_backlight(3);
  init_battery();
  init_hrs3300();
  init_time();
  init_touch();
  init_sleep();
  init_menu();
  init_push();
  init_flash();
  init_accl();
  init_ble();//must be before interrupts!!!
  init_interrupt();//must be after ble!!!
  delay(100);
  set_backlight(3);
  display_home();
}

void loop() {
  ble_feed();//manage ble connection
  if (!get_button())watchdog_feed();//reset the watchdog if the push button is not pressed, if it is pressed for more then WATCHDOG timeout the watch will reset
  if (get_sleep()) {//see if we are sleeping
    sleep_wait();//just sleeping
  } else {//if  we are awake do display stuff etc
    check_sleep_times();//check if we should go sleeping again
    display_screen();//manage menu and display stuff
    check_battery_status();// check battery status. if lower than XX show message
  }
  if (get_timed_int()) {//Theorecticly every 40ms via RTC2 but since the display takes longer its not accurate at all when display on
    if (get_sleep()) {
      if (acc_input()){
         sleep_up(WAKEUP_ACCL);//check if the hand was lifted and turn on the display if so
      }
    }
    time_data_struct time_data = get_time();
    if (time_data.hr == 0) {// check for new day
      if (!stepsWhereReseted) {//reset steps on a new day
        stepsWhereReseted = true;
        reset_step_counter();
      }
    } else stepsWhereReseted = false;

    check_timed_heartrate(time_data.min);//Meassure HR every 15minutes
  }
  gets_interrupt_flag();//check interrupt flags and do something with it
}
