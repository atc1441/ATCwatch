
#pragma once
#include "Arduino.h"
#include "classScreen.h"
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


class HomeScreen : public TheScreen
{
  public:
    HomeScreen() {
    }

    virtual void pre()
    {
      displayRect(0, 0, 240, 240, 0x0000);
      charge_symbol_change = false;
      displayImage(0, 136, 24, 24, symbolHeartSmall);
      displayImage(0, 136 + 24 + 2, 24, 24, symbolStepsSmall);
      displayImage(0, 136 + 24 + 2 + 24 + 2, 24, 24, symbolMsgSmall);
    }

    virtual void main()
    {
      time_data_struct time_data = get_time();
      accl_data_struct accl_data = get_accl_data();

      char time_string[14];
      sprintf(time_string, "%02i:%02i:%02i", time_data.hr, time_data.min, time_data.sec);
      char date_string[14];
      sprintf(date_string, "%02i.%02i.%04i", time_data.day, time_data.month, time_data.year);
      displayPrintln(20, 70, time_string, 0xFFFF, 0x0000, 4);
      displayPrintln(28, 104, date_string, 0xFFFF, 0x0000, 3);

      displayPrintln(30, 140, (String)get_last_heartrate() + "     ", 0xFFFF, 0x0000, 2);
      displayPrintln(30, 140 + 24 + 2, (String)accl_data.steps + "     ", 0xFFFF, 0x0000, 2);
      displayPrintln(30, 140 + 24 + 2 + 24 + 2, get_push_msg(17), 0xFFFF, 0x0000, 2);

      if (get_vars_ble_connected())
        displayImage(190, 0, 24, 24, symbolBle1);
      else
        displayImage(190, 0, 24, 24, symbolBle2);


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
    }

    virtual void up()
    {
      inc_vars_menu();
    }

    virtual void down()
    {
      dec_vars_menu();
    }

    virtual void left()
    {
    }
    virtual void right()
    {
    }
  private:
    bool charge_symbol_change = false;

};
