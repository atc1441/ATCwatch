
#include "menuAppsBase.h"
#include "Arduino.h"
#include "images.h"
#include "menu.h"
#include "display.h"

uint16_t borderColor = 0xffff;
uint16_t bgColor = 0x0000;

void rectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint16_t color) {
  displayRect(x, y, 1, h, borderColor);
  displayRect(x, y, w, 1, borderColor);
  displayRect(x + w, y, 1, h, borderColor);
  displayRect(x, y + h, w, 1, borderColor);
}

void displayIconAndText(uint32_t x, uint32_t y, uint32_t w, uint32_t h, String text, const uint16_t *buff) {
  displayImage(x, y, w, (h - 1), buff);
  displayRect(x + 1, y + h + 2, w, 8, 0x0000);
  displayPrintln(x + 1, y + h + 2, text);
}

void menuAppsBase(uint32_t page) {
  displayRect(0, 0, 240, 240, 0x0000);
  if (page == 1)
    displayImage(228, 100, 12, 12, symbolCheck2);
  else
    displayImage(228, 100, 12, 12, symbolCheck1);
  if (page == 2)
    displayImage(228, 114, 12, 12, symbolCheck2);
  else
    displayImage(228, 114, 12, 12, symbolCheck1);
  if (page == 3)
    displayImage(228, 128, 12, 12, symbolCheck2);
  else
    displayImage(228, 128, 12, 12, symbolCheck1);

  /* rectangle(25, 19, 82, 82, borderColor);
    rectangle(25, 128, 82, 82, borderColor);
    rectangle(132, 19, 82, 82, borderColor);
    rectangle(132, 128, 82, 82, borderColor);*/

}

int check_app_click(uint32_t x, uint32_t y) {
  if (32 <= x && x <= (32 + 72) && 28 <= y && y <= (28 + 72))
    return 1;
  else if (136 <= x && x <= (136 + 72) && 28 <= y && y <= (28 + 72))
    return 2;
  else if (32 <= x && x <= (32 + 72) && 132 <= y && y <= (132 + 72))
    return 3;
  else if (136 <= x && x <= (136 + 72) && 132 <= y && y <= (132 + 72))
    return 4;
  return 0;
}
