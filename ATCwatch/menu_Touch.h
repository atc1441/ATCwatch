/*
 * Copyright (c) 2020 Aaron Christophel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

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

class TouchScreen : public Screen
{
  public:
    virtual void pre()
    {
      set_swipe_enabled(true);
      touch_data = get_touch();
      
      label = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text(label, "Touchscreen");
      lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
      
      label_gesture = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text_fmt(label_gesture, "Gesture: %02X", touch_data.gesture);
      lv_obj_align(label_gesture, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 25);
      label_touchpoints = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text_fmt(label_touchpoints, "Gesture: %02X", touch_data.touchpoints);
      lv_obj_align(label_touchpoints, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 45);
      label_event = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text_fmt(label_event, "Event: %02X", touch_data.event);
      lv_obj_align(label_event, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 65);
      label_xpos = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text_fmt(label_xpos, "X: %02X", touch_data.xpos);
      lv_obj_align(label_xpos, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 85);
      label_ypos = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text_fmt(label_ypos, "Y: %02X", touch_data.ypos);
      lv_obj_align(label_ypos, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 105);      
      label_versionInfo = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text_fmt(label_versionInfo, "Tp Version: %02X %02X %02X %02X", touch_data.version15, touch_data.versionInfo[0], touch_data.versionInfo[1], touch_data.versionInfo[2]);
      lv_obj_align(label_versionInfo, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 10, 125);
      label_int = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text_fmt(label_int, "Interrupt: %i", digitalRead(TP_INT));  
      lv_obj_align(label_int, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 10, 145);
    }

    virtual void main()
    {
      touch_data = get_touch();
      lv_label_set_text_fmt(label_gesture, "Gesture: %02X", touch_data.gesture);
      lv_label_set_text_fmt(label_touchpoints, "Touchpoints: %02X", touch_data.touchpoints);
      lv_label_set_text_fmt(label_event, "Event: %02X", touch_data.event);
      lv_label_set_text_fmt(label_xpos, "X: %i", touch_data.xpos);
      lv_label_set_text_fmt(label_ypos, "Y: %i", touch_data.ypos);
      lv_label_set_text_fmt(label_int, "Interrupt: %i", digitalRead(TP_INT));
    }

    virtual void up()
    {
    }

    virtual void down()
    {
    }

    virtual void right()
    {
    }

    virtual void left()
    {
    }

  private:
    touch_data_struct touch_data;
    lv_obj_t *label;
    lv_obj_t *label_gesture,*label_touchpoints,*label_event,*label_xpos,*label_ypos,*label_versionInfo,*label_int,*label_a5;
};

TouchScreen touchScreen;
