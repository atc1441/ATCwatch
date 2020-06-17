
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


class DemoScreen : public Screen
{
  public:
    virtual void pre()
    {
      set_swipe_enabled(true);
      
      label = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text(label, "Demo");
      lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);

      static lv_style_t style_bg;
      static lv_style_t style_indic;
      static lv_style_t style_knob;

      lv_style_copy(&style_bg, &lv_style_pretty);
      style_bg.body.main_color =  LV_COLOR_BLACK;
      style_bg.body.grad_color =  LV_COLOR_GRAY;
      style_bg.body.radius = LV_RADIUS_CIRCLE;
      style_bg.body.border.color = LV_COLOR_WHITE;

      lv_style_copy(&style_indic, &lv_style_pretty_color);
      style_indic.body.radius = LV_RADIUS_CIRCLE;
      style_indic.body.shadow.width = 8;
      style_indic.body.shadow.color = style_indic.body.main_color;
      style_indic.body.padding.left = 3;
      style_indic.body.padding.right = 3;
      style_indic.body.padding.top = 3;
      style_indic.body.padding.bottom = 3;

      lv_style_copy(&style_knob, &lv_style_pretty);
      style_knob.body.radius = LV_RADIUS_CIRCLE;
      style_knob.body.opa = LV_OPA_70;
      style_knob.body.padding.top = 10 ;
      style_knob.body.padding.bottom = 10 ;

      /*Create a slider*/
      lv_obj_t * slider = lv_slider_create(lv_scr_act(), NULL);
      lv_slider_set_style(slider, LV_SLIDER_STYLE_BG, &style_bg);
      lv_slider_set_style(slider, LV_SLIDER_STYLE_INDIC, &style_indic);
      lv_slider_set_style(slider, LV_SLIDER_STYLE_KNOB, &style_knob);
      lv_obj_align(slider, NULL, LV_ALIGN_CENTER, 0, 0);  
    }

    virtual void main()
    {
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

  private:
    lv_style_t st;
    lv_obj_t *label_time;
    lv_obj_t *label;
};
