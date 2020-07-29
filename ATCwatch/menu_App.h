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
#include <lvgl.h>

struct app_struct {
  const char* _title;
  const lv_img_dsc_t* _symbol;
  Screen* _screen;
};

class AppScreen : public Screen
{
  public:
    AppScreen(int menuPosition, int maxApps, app_struct* app1, app_struct* app2, app_struct* app3, app_struct* app4)
    {
      _menuPosition = menuPosition;
      _maxApps = maxApps;
      _app1 = app1;
      _app2 = app2;
      _app3 = app3;
      _app4 = app4;
    }

    virtual void pre()
    {
      slider = lv_slider_create(lv_scr_act(), NULL);
      lv_obj_set_size(slider, 23, 100);
      lv_slider_set_range(slider, 1, _maxApps);
      lv_slider_set_value(slider, _maxApps - _menuPosition + 1, false);
      lv_obj_align(slider, NULL, LV_ALIGN_IN_RIGHT_MID, -4, 0);
      lv_obj_set_click(slider, false);
      lv_obj_set_click(lv_page_get_scrl(slider), false);

      label = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text_fmt(label, "%i/%i", _menuPosition, _maxApps);
      lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);

      button_image1 = lv_imgbtn_create(lv_scr_act(), NULL);
      lv_imgbtn_set_src(button_image1, LV_BTN_STATE_REL, _app1->_symbol);
      lv_imgbtn_set_src(button_image1, LV_BTN_STATE_PR, _app1->_symbol);
      lv_imgbtn_set_toggle(button_image1, false);
      lv_obj_set_pos(button_image1, 32, 28);
      lv_obj_set_event_cb(button_image1, lv_event_handler);

      image_label = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text(image_label, _app1->_title);
      lv_obj_align(image_label, button_image1, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 2);

      button_image2 = lv_imgbtn_create(lv_scr_act(), NULL);
      lv_imgbtn_set_src(button_image2, LV_BTN_STATE_REL, _app2->_symbol);
      lv_imgbtn_set_src(button_image2, LV_BTN_STATE_PR, _app2->_symbol);
      lv_imgbtn_set_toggle(button_image2, false);
      lv_obj_set_pos(button_image2, 136, 28);
      lv_obj_set_event_cb(button_image2, lv_event_handler);

      image_label = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text(image_label, _app2->_title);
      lv_obj_align(image_label, button_image2, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 2);

      button_image3 = lv_imgbtn_create(lv_scr_act(), NULL);
      lv_imgbtn_set_src(button_image3, LV_BTN_STATE_REL, _app3->_symbol);
      lv_imgbtn_set_src(button_image3, LV_BTN_STATE_PR, _app3->_symbol);
      lv_imgbtn_set_toggle(button_image3, false);
      lv_obj_set_pos(button_image3, 32, 132);
      lv_obj_set_event_cb(button_image3, lv_event_handler);

      image_label = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text(image_label, _app3->_title);
      lv_obj_align(image_label, button_image3, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 2);

      button_image4 = lv_imgbtn_create(lv_scr_act(), NULL);
      lv_imgbtn_set_src(button_image4, LV_BTN_STATE_REL, _app4->_symbol);
      lv_imgbtn_set_src(button_image4, LV_BTN_STATE_PR, _app4->_symbol);
      lv_imgbtn_set_toggle(button_image4, false);
      lv_obj_set_pos(button_image4, 136, 132);
      lv_obj_set_event_cb(button_image4, lv_event_handler);

      image_label = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text(image_label, _app4->_title);
      lv_obj_align(image_label, button_image4, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 2);
    }

    virtual void main()
    {

    }

    virtual void up()
    {
      inc_vars_menu();
    }

    virtual void down()
    {
      dec_vars_menu();
    }

    virtual void right()
    {
      display_home();
    }

    virtual void lv_event_class(lv_obj_t * object, lv_event_t event)
    {
      if (event == LV_EVENT_SHORT_CLICKED) {
        if (object == button_image1) {
          change_screen(_app1->_screen);
        } else if (object == button_image2) {
          change_screen(_app2->_screen);
        } else if (object == button_image3) {
          change_screen(_app3->_screen);
        } else if (object == button_image4) {
          change_screen(_app4->_screen);
        }
      }
    }

  private:
    app_struct* _app1;
    app_struct* _app2;
    app_struct* _app3;
    app_struct* _app4;
    lv_obj_t *button_image1, *button_image2, *button_image3, *button_image4, *image_label, *slider, *label;
    uint32_t _menuPosition, _maxApps;

};
