/*
 * Copyright (c) 2020 Aaron Christophel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "menu.h"
#include "class_def.h"
#include "images.h"
#include "pinout.h"
#include "touch.h"
#include "backlight.h"
#include "bootloader.h"
#include "display.h"
#include "menu_Boot.h"
#include "menu_Home.h"
#include "menu_Heart.h"
#include "menu_Debug.h"
#include "menu_Reboot.h"
#include "menu_Update.h"
#include "menu_Off.h"
#include "menu_Notify.h"
#include "menu_Battery.h"
#include "menu_Settings_Time.h"
#include "menu_Settings_Date.h"
#include "menu_Settings_Color.h"
#include "menu_Settings_Brightness.h"
#include "menu_Animation.h"
#include "menu_infos.h"
#include "menu_Accl.h"
#include "menu_App.h"
#include "menu_Demo.h"
#include "menu_Charging.h"
#include "menu_Flash.h"
#include "menu_Touch.h"
#include "menu_Http.h"
#include "menu_Log.h"
#include "menu_Settings.h"
#include <lvgl.h>

long last_main_run;
int vars_menu = -1;
int vars_max_menu = 4;
bool swipe_enabled_bool = false;

Screen_def *currentScreen = &homeScreen;
Screen_def *oldScreen = &homeScreen;
Screen_def *lastScreen = &homeScreen;

app_struct notifyApp = {"Notify", &IsymbolMsg, &notifyScreen};
app_struct heartApp = {"Heartrate", &IsymbolHeart, &heartScreen};
app_struct batteryApp = {"Battery", &IsymbolBatteryBig, &batteryScreen};
app_struct debugApp = {"Debug", &IsymbolDebug, &debugScreen};

app_struct rebootApp = {"Reboot", &IsymbolReboot, &rebootScreen};
app_struct updateApp = {"Bootloader", &IsymbolBootloader, &updateScreen};
app_struct offApp = {"Shutdown", &IsymbolShutdown, &offScreen};
app_struct settingsApp = {"Settings", &IsymbolSettings, &settingsScreen};

app_struct animationApp = {"Animation", &IsymbolAnimation, &animationScreen};
app_struct infosApp = {"Infos", &IsymbolInfos, &infosScreen};
app_struct acclApp = {"Accl", &IsymbolAccl , &acclScreen};
app_struct demoApp = {"Demo", &IsymbolChart , &demoScreen};

app_struct flashApp = {"Flash_test", &IsymbolChart , &flashScreen};
app_struct touchApp = {"Touch", &IsymbolMouse , &touchScreen};
app_struct httpApp = {"HTTP", &IsymbolMouse , &httpScreen};
app_struct logApp = {"Logging", &IsymbolAnimation , &logScreen};

int maxApps = 4;
AppScreen apps1Screen(1, maxApps, &notifyApp, &heartApp, &debugApp, &animationApp);
AppScreen apps2Screen(2, maxApps, &rebootApp, &updateApp, &offApp, &settingsApp);
AppScreen apps3Screen(3, maxApps, &infosApp, &acclApp, &demoApp, &batteryApp);
AppScreen apps4Screen(4, maxApps, &flashApp, &touchApp, &httpApp, &logApp);

Screen_def *menus[5] = {&homeScreen, &apps1Screen, &apps2Screen, &apps3Screen, &apps4Screen};

void init_menu() {

}

void display_home() {
  lastScreen = currentScreen;
  currentScreen = &homeScreen;
  vars_menu = 0;
}

void display_notify() {
  lastScreen = currentScreen;
  currentScreen = &notifyScreen;
  vars_menu = 0;
}

void display_charging() {
  lastScreen = currentScreen;
  currentScreen = &chargingScreen;
  vars_menu = 0;
}

void display_booting() {
  set_gray_screen_style();
  lastScreen = currentScreen;
  currentScreen = &bootScreen;
  oldScreen = &bootScreen;
  set_swipe_enabled(false);
  currentScreen->pre_display();
  set_gray_screen_style();
  currentScreen->pre();
  currentScreen->main();
  inc_tick();
  lv_task_handler();
}

void display_screen(bool ignoreWait) {
  if (ignoreWait || millis() - last_main_run > get_menu_delay_time()) {
    last_main_run = millis();
    if (currentScreen != oldScreen) {
      oldScreen->post();
      currentScreen->pre_display();
      set_gray_screen_style();
      oldScreen = currentScreen;
      set_swipe_enabled(false);
      currentScreen->pre();
    }
    currentScreen->main();
  }
  lv_task_handler();
}

void check_button_push(int length) {
  currentScreen->button_push(length);
}

void check_menu(touch_data_struct touch_data) {
  if (touch_data.gesture == TOUCH_SLIDE_UP) {
    currentScreen->up();
  } else if (touch_data.gesture == TOUCH_SLIDE_DOWN) {
    currentScreen->down();
  } else if (touch_data.gesture == TOUCH_SINGLE_CLICK) {
    currentScreen->click(touch_data);
  } else if (touch_data.gesture == TOUCH_LONG_PRESS) {
    currentScreen->long_click(touch_data);
  } else if (touch_data.gesture == TOUCH_SLIDE_LEFT) {
    currentScreen->left();
  } else if (touch_data.gesture == TOUCH_SLIDE_RIGHT) {
    currentScreen->right();
  }
}

uint32_t get_menu_delay_time() {
  return currentScreen->refreshTime();
}

void change_screen(Screen_def* screen) {
  lastScreen = currentScreen;
  currentScreen = screen;
}

int get_sleep_time_menu() {
  return currentScreen->sleepTime();
}

void set_last_menu() {
  currentScreen = lastScreen;
}

void set_swipe_enabled(bool state) {
  swipe_enabled_bool = state;
}

bool swipe_enabled() {
  return swipe_enabled_bool;
}

void inc_vars_menu() {
  lastScreen = currentScreen;
  vars_menu++;
  if (vars_menu > vars_max_menu | vars_menu < 0)vars_menu = 0;
  currentScreen = menus[vars_menu];
}

void dec_vars_menu() {
  lastScreen = currentScreen;
  vars_menu--;
  if (vars_menu < 0 | vars_menu > vars_max_menu)vars_menu = vars_max_menu;
  currentScreen = menus[vars_menu];
}

static void lv_event_handler(lv_obj_t * object, lv_event_t event)
{
  currentScreen->lv_event_class(object, event);
}
