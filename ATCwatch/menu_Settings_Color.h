
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


class SettingsColorScreen : public Screen
{
  public:
    virtual void pre()
    {
      set_swipe_enabled(true);
      main_color_save = get_main_color();
      grad_color_save = get_grad_color();
      font_color_save = get_font_color();

      label_screen = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text(label_screen, "Set Colors");
      lv_obj_align(label_screen, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);

      btn1 = lv_btn_create(lv_scr_act(), NULL);
      lv_obj_set_event_cb(btn1, lv_event_handler);
      lv_obj_align(btn1, NULL, LV_ALIGN_IN_BOTTOM_MID, -55, 0);
      lv_btn_set_fit2(btn1, LV_FIT_NONE, LV_FIT_TIGHT);
      btn1_label = lv_label_create(btn1, NULL);
      lv_label_set_text(btn1_label, "Abort");

      btn2 = lv_btn_create(lv_scr_act(), NULL);
      lv_obj_set_event_cb(btn2, lv_event_handler);
      lv_btn_set_fit2(btn2, LV_FIT_NONE, LV_FIT_TIGHT);
      lv_obj_align(btn2, NULL, LV_ALIGN_IN_BOTTOM_MID, 55, 0);
      btn2_label = lv_label_create(btn2, NULL);
      lv_label_set_text(btn2_label, "Save");

      ddlist_main = lv_ddlist_create(lv_scr_act(), NULL);
      lv_ddlist_set_options(ddlist_main,  "Milk\n"
                            "Gray\n"
                            "Black\n"
                            "Red\n"
                            "Green\n"
                            "Blue");
      lv_obj_align(ddlist_main, NULL, LV_ALIGN_CENTER, -85, -50);
      lv_obj_set_event_cb(ddlist_main, lv_event_handler);
      lv_ddlist_set_selected(ddlist_main, main_color_save);

      main_label = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text(main_label, "Main");
      lv_obj_align(main_label, ddlist_main, LV_ALIGN_OUT_TOP_MID, 0, -2);

      ddlist_grad = lv_ddlist_create(lv_scr_act(), NULL);
      lv_ddlist_set_options(ddlist_grad,  "Milk\n"
                            "Gray\n"
                            "Black\n"
                            "Red\n"
                            "Green\n"
                            "Blue");
      lv_obj_align(ddlist_grad, NULL, LV_ALIGN_CENTER, 0, -50);
      lv_obj_set_event_cb(ddlist_grad, lv_event_handler);
      lv_ddlist_set_selected(ddlist_grad, grad_color_save);

      grad_label = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text(grad_label, "Grad");
      lv_obj_align(grad_label, ddlist_grad, LV_ALIGN_OUT_TOP_MID, 0, -2);

      ddlist_font = lv_ddlist_create(lv_scr_act(), NULL);
      lv_ddlist_set_options(ddlist_font, "Milk\n"
                            "Gray\n"
                            "Black\n"
                            "Red\n"
                            "Green\n"
                            "Blue");
      lv_obj_align(ddlist_font, NULL, LV_ALIGN_CENTER, 85, -50);
      lv_obj_set_event_cb(ddlist_font, lv_event_handler);
      lv_ddlist_set_selected(ddlist_font, font_color_save);

      font_label = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text(font_label, "Font");
      lv_obj_align(font_label, ddlist_font, LV_ALIGN_OUT_TOP_MID, 0, -2);
    }

    virtual void lv_event_class(lv_obj_t * object, lv_event_t event)
    {
      if (object == btn1 && event == LV_EVENT_CLICKED) {
        set_main_color(main_color_save);
        set_grad_color(grad_color_save);
        set_font_color(font_color_save);
        set_last_menu();
      } else if (object == btn2 && event == LV_EVENT_CLICKED) {
        set_last_menu();
        set_motor_ms(35);
      } else if (object == ddlist_main && event == LV_EVENT_VALUE_CHANGED) {
        set_main_color(lv_ddlist_get_selected(ddlist_main));
        set_gray_screen_style();
      } else if (object == ddlist_grad && event == LV_EVENT_VALUE_CHANGED) {
        set_grad_color(lv_ddlist_get_selected(ddlist_grad));
        set_gray_screen_style();
      } else if (object == ddlist_font && event == LV_EVENT_VALUE_CHANGED) {
        set_font_color(lv_ddlist_get_selected(ddlist_font));
        set_gray_screen_style();
      }
    }

  private:
    lv_obj_t *label_screen;
    lv_obj_t *btn1, *btn2, *btn1_label, *btn2_label, *label_points;
    lv_obj_t *ddlist_main, *main_label, *ddlist_grad, *grad_label, *ddlist_font, *font_label;
    int main_color_save, grad_color_save, font_color_save;
};

SettingsColorScreen settingsColorScreen;
