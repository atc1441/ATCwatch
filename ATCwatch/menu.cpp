
#include "menu.h"
#include "class.h"
#include "classApp.h"
#include "images.h"
#include "pinout.h"
#include "touch.h"
#include "backlight.h"
#include "bootloader.h"
#include "display.h"
#include "menuAppsBase.h"
#include "menu_Boot.h"
#include "menu_Home.h"
#include "menu_Heart.h"
#include "menu_Debug.h"
#include "menu_Reboot.h"
#include "menu_Update.h"
#include "menu_Off.h"
#include "menu_Notify.h"
#include "menu_Battery.h"
#include "menu_Settings.h"
#include "menu_Error.h"
#include "menu_animation.h"
#include "menu_infos.h"
#include "menu_Accl.h"

long last_main_run;
int vars_menu = -1;
int vars_max_menu = 3;


BootScreen bootScreen;
HomeScreen homeScreen;
HeartScreen heartScreen;
DebugScreen debugScreen;
RebootScreen rebootScreen;
UpdateScreen updateScreen;
OffScreen offScreen;
NotifyScreen notifyScreen;
BatteryScreen batteryScreen;
SettingsScreen settingsScreen;
ErrorScreen errorScreen;
AnimationScreen animationScreen;
InfosScreen infosScreen;
AcclScreen acclScreen;


App notifyApp("Notify", symbolMsg, &notifyScreen);
App heartApp("Heartrate", symbolHeart, &heartScreen);
App batteryApp("Battery", symbolBatteryBig, &batteryScreen);
App debugApp("Debug", symbolDebug, &debugScreen);

App rebootApp("Reboot", symbolReboot, &rebootScreen);
App updateApp("Bootloader", symbolBootloader, &updateScreen);
App offApp("Schutdown", symbolShutdown, &offScreen);
App settingsApp("Settings", symbolSettings, &settingsScreen);

App animationApp("Animation", symbolAnimation, &animationScreen);
App infosApp("Infos", symbolInfos, &infosScreen);
App acclApp("Accl", symbolAccl , &acclScreen);

AppScreen apps1Screen(1, &notifyApp, &heartApp, &debugApp, &animationApp);
AppScreen apps2Screen(2, &rebootApp, &updateApp, &offApp, &settingsApp);
AppScreen apps3Screen(3, &infosApp, &acclApp, &batteryApp, &batteryApp);

Screen *currentScreen = &homeScreen;
Screen *oldScreen = &homeScreen;
Screen *lastScreen = &homeScreen;
Screen *menus[4] = {&homeScreen, &apps1Screen, &apps2Screen, &apps3Screen};

void init_menu() {

}

void display_home() {
  lastScreen = currentScreen;
  currentScreen = &homeScreen;
  vars_menu = 0;
}

void display_error() {
  lastScreen = &errorScreen;
  currentScreen = &errorScreen;
  vars_menu = 0;
}

void display_notify() {
  lastScreen = currentScreen;
  currentScreen = &notifyScreen;
  vars_menu = 0;
}

void display_booting() {
  lastScreen = currentScreen;
  currentScreen = &bootScreen;
  oldScreen = &bootScreen;
  currentScreen->pre();
  currentScreen->main();
}

void display_screen(bool ignoreWait) {
  if (millis() - last_main_run > get_menu_delay_time()|| ignoreWait) {
    last_main_run = millis();
    if (currentScreen != oldScreen) {
      oldScreen->post();
      oldScreen = currentScreen;
      currentScreen->pre();
    }
    currentScreen->main();
  }
}

void check_menu() {
  touch_data_struct touch_data = get_touch();
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

void change_screen(Screen* screen) {
  lastScreen = currentScreen;
  currentScreen = screen;
}

int get_sleep_time_menu() {
  return currentScreen->sleepTime();
}

void set_last_menu() {
  currentScreen = lastScreen;
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
