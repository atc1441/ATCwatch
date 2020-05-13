
#pragma once
#include "Arduino.h"
#include "class.h"
#include "images.h"
#include "menu.h"
#include "display.h"
#include "menuAppsBase.h"
#include "ble.h"
#include "time.h"
#include "battery.h"
#include "accl.h"
#include "push.h"
#include "heartrate.h"


class BatteryScreen : public TheScreen
{
  public:
    BatteryScreen() {
    }

    virtual void pre()
    {
      charge_symbol_change = false;
      displayRect(0, 0, 240, 240, 0x0000);
      displayPrintln(0, 0, "Battery:", 0xFFFF, 0x0000, 2);
    }

    virtual void main()
    {
      if (get_charge()) {
        if (!charge_symbol_change)displayImage(216, 0, 24, 24, symbolBattery2);
        charge_symbol_change = true;
        int batteryPer = get_battery_percent();
        String batteryDisplay = "";
        if (batteryPer < 10)
          batteryDisplay = " " + (String)batteryPer;
        else
          batteryDisplay = (String)batteryPer;
        displayPrintln(222, 8, batteryDisplay, 0x0000, 0xFFFF);
      } else {
        displayImage(216, 0, 24, 24, symbolBattery1);
        charge_symbol_change = false;
      }

      displayPrintln(10, 120, (String)get_battery_percent() + "%   ", 0xFFFF, 0x0000,3);
    }

    virtual void up()
    {
      inc_backlight();
      set_backlight();
    }

    virtual void down()
    {
      dec_backlight();
      set_backlight();
    }

  private:
    bool charge_symbol_change = false;

};
