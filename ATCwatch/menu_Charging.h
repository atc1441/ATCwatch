
#pragma once
#include "Arduino.h"
#include "class.h"
#include "images.h"
#include "menu.h"
#include "display.h"
#include "ble.h"
#include "time.h"
#include "battery.h"
#include "accl.h"
#include "push.h"
#include "heartrate.h"


class ChargingScreen : public Screen
{
  public:
    virtual void pre()
    {
      label = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text(label, "Charging");
      lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, -30);

      lv_style_copy( &st, &lv_style_plain );
      st.text.color = lv_color_hsv_to_rgb(10, 5, 95);
      st.text.font = &mksd50;

      label_battery_big = lv_label_create(lv_scr_act(), NULL);
      lv_obj_set_style( label_battery_big, &st );
      lv_label_set_text(label_battery_big, "---%");
      lv_obj_align(label_battery_big, lv_scr_act(), LV_ALIGN_CENTER, -20, 20);
    }

    virtual void main()
    {
      lv_label_set_text_fmt(label_battery_big, "%i%%", get_battery_percent());
    }

    virtual void long_click()
    {
      display_home();
    }

    virtual void left()
    {
      display_home();
    }

    virtual void right()
    {
      display_home();
    }

    virtual void up()
    {
      display_home();
    }
    virtual void down()
    {
      display_home();
    }

    virtual void click(touch_data_struct touch_data)
    {
      display_home();
    }
    
  private:
    lv_obj_t *label;
    lv_obj_t *label_battery, *label_battery_big, *label_backlight_big;
    lv_style_t style_battery, st;
};

ChargingScreen chargingScreen;
