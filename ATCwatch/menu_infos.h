
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

#define versionString "1.1.1"

class InfosScreen : public TheScreen
{
  public:
    InfosScreen() {
    }

    virtual void pre()
    {
      displayRect(0, 0, 240, 240, 0x0000);
      displayImage(120 - (72 / 2), 240-72, 72, 72, symbolInfos);
      displayPrintln(0, 0, "Infos:", 0xFFFF, 0x0000, 2);
      displayPrintln(0, 16+2, "Firmware By:", 0xFFFF, 0x0000, 2);
      displayPrintln(0, 16 + 16+5, "   ATCnetz.de", 0xFFFF, 0x0000, 2);
      displayPrintln(0, 16 + 16 + 16+6, "(Aaron Christophel)", 0xFFFF, 0x0000, 2);
      displayPrintln(20, 16 + 16 + 16 + 16 + 16, "Version:" + (String)versionString, 0xFFFF, 0x0000, 2);
      displayPrintln(20, 16 + 16 + 16 + 16 + 16 + 16, "Compiled:", 0xFFFF, 0x0000, 2);
      displayPrintln(20, 16 + 16 + 16 + 16 + 16 + 16 + 16+4, (String)__DATE__ , 0xFFFF, 0x0000, 2);
      displayPrintln(20, 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16+8, (String)__TIME__ , 0xFFFF, 0x0000, 2);
    }

    virtual void main()
    {

    }

  private:

};
