
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
#include "images_nian.h"


class AnimationScreen : public TheScreen
{
  public:
    virtual void pre()
    {
      currentSymbol = 0;
      displayRect(0, 0, 240, 240, 0x0000);
      displayPrintln(0, 0, "Animation Test", 0xFFFF, 0x0000, 2);
      displayPrintln(0, 16, "Speed:", 0xFFFF, 0x0000, 2);
      displayPrintln(0, 32, String(speedChange) + " ms    ", 0xFFFF, 0x0000, 2);
    }

    virtual void up()
    {
      speedChange -= 10;
      if (speedChange <= 0)speedChange = 0;
      if (speedChange >= 5000)speedChange = 5000;
      displayPrintln(0, 32, String(speedChange) + " ms    ", 0xFFFF, 0x0000, 2);
    }

    virtual void down()
    {
      speedChange += 10;
      if (speedChange <= 0)speedChange = 0;
      if (speedChange >= 5000)speedChange = 5000;
      displayPrintln(0, 32, String(speedChange) + " ms    ", 0xFFFF, 0x0000, 2);
    }

    virtual void main()
    {
      switch (currentSymbol) {
        case 1:
          displayImage(x, y, w, h, symbolNian1);
          break;
        case 2:
          displayImage(x, y, w, h,  symbolNian2);
          break;
        case 3:
          displayImage(x, y, w, h,  symbolNian3);
          break;
        case 4:
          displayImage(x, y, w, h,  symbolNian4);
          break;
        case 5:
          displayImage(x, y, w, h,  symbolNian5);
          break;
        case 6:
          displayImage(x, y, w, h,  symbolNian6);
          break;
        case 7:
          displayImage(x, y, w, h,  symbolNian7);
          break;
        case 8:
          displayImage(x, y, w, h, symbolNian8);
          break;
        default:
          currentSymbol = 1;
          break;
      }

      if (millis() - lastChange > speedChange) {
        lastChange = millis();

        if (currentSymbol >= 8)
          currentSymbol = 0;
        else
          currentSymbol++;
      }
    }

    virtual uint32_t refreshTime()
    {
      return 1;
    }

  private:
    int x = 50, y = 70, w = 120, h = 76;
    int currentSymbol = 1;
    long lastChange;
    int speedChange = 100;

};
