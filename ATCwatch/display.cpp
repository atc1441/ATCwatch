#include "display.h"

#include "fast_spi.h"
#include "images.h"
#include "font57.h"
#include "battery.h"
#include "touch.h"
#include "accl.h"
#include "menu.h"
#include "ble.h"
#include "heartrate.h"
#include "backlight.h"
#include "inputoutput.h"
#include "bootloader.h"
#include "time.h"
#include "push.h"

#define LCD_BUFFER_SIZE 15000
uint8_t lcd_buffer[LCD_BUFFER_SIZE+4];
uint32_t widthheigthWindow = 0;
bool last_uni_char = false;
unsigned char last_char;

void init_display() {
  initDisplay();
  display_clear();
}

bool drawChar(uint32_t x, uint32_t y, unsigned char c, uint16_t color, uint16_t bg, uint32_t size) {
  if (c < 32)return false;
  if (c >= 127) {
    if (!last_uni_char) {
      last_char = c;
      last_uni_char = true;
      return false;
    } else {
      last_uni_char = false;
      if (last_char == 0xC3) {
        switch (c) {
          case 0x84://Ä
            c = 0x8E;
            break;
          case 0xA4://ä
            c = 0x84;
            break;
          case 0x96://Ö
            c = 0x99;
            break;
          case 0xB6://ö
            c = 0x94;
            break;
          case 0x9C://Ü
            c = 0x9A;
            break;
          case 0xBC://ü
            c = 0x81;
            break;
          case 0x9F://ß
            c = 0x98;
            break;
          default:
            return false;
            break;
        }
      } else if (last_char == 0xF0 && c == 0x9F)
        c = 0x02;
      else
        return false;
    }
  }
  for (int8_t i = 0; i < 5; i++) {
    uint8_t line = font57[c * 5 + i];
    for (int8_t j = 0; j < 8; j++, line >>= 1) {
      if (line & 1) {
        displayRect(x + i * size, y + j * size, size, size, color);
      } else if (bg != color) {
        displayRect(x + i * size, y + j * size, size, size, bg);
      }
    }
  }
  if (bg != color) {
    displayRect(x + 5 * size, y, size, 8 * size, bg);
  }
  return true;
}

void displayPrintln(uint32_t x, uint32_t y, String text, uint16_t color, uint16_t bg, uint32_t size) {
  int tempPosition = 0;
  for (int f = 0; f < text.length(); f++)
  {
    if (x + (tempPosition * 6 * size) >= 234) {
      x = -(tempPosition * 6 * size);
      y += (8 * size);
    }
    if (drawChar(x + (tempPosition * 6 * size), y, text[f], color, bg, size)) {
      tempPosition++;
    }
  }
}

void displayRect(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint16_t color) {
  startWrite();
  setAddrWindowDisplay(x, y, w, h);
  displayColor(color);
  endWrite();
}

void displayImage(uint32_t x, uint32_t y, uint32_t w, uint32_t h, const uint16_t *buffer) {
  startWrite();
  setAddrWindowDisplay(x, y, w, h);
  uint32_t numPixels = (widthheigthWindow * 2);
  uint32_t curPosition = 0;
  uint32_t curSize;
  uint32_t bufferPos;
  do {
    memset(lcd_buffer, 0x43, LCD_BUFFER_SIZE);
    if ((numPixels - curPosition) > LCD_BUFFER_SIZE)
      curSize = LCD_BUFFER_SIZE;
    else
      curSize = (numPixels - curPosition);

    for (int i = 0; i < curSize; i++) {
      lcd_buffer[i++] = buffer[bufferPos] >> 8;
      lcd_buffer[i] = buffer[bufferPos];
      bufferPos++;
    }
    write_fast_spi(lcd_buffer, curSize);
    curPosition += curSize;
  } while (curPosition < numPixels);
  endWrite();
}

void display_enable(bool state) {
  uint8_t temp[2];
  startWrite();
  if (state) {
    spiCommand(ST77XX_DISPON);
    spiCommand(ST77XX_SLPOUT);
  } else {
    spiCommand(ST77XX_SLPIN);
    spiCommand(ST77XX_DISPOFF);
  }
  endWrite();
}

void display_clear() {
  startWrite();
  setAddrWindowDisplay(0, 0, 240, 240);
  displayColor();
  endWrite();
}

void setAddrWindowDisplay(uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{
  uint8_t temp[4];
  widthheigthWindow = w * h;
  spiCommand(0x2A);
  temp[0] = 0x00;
  temp[1] = x;
  temp[2] = 0x00;
  temp[3] = (x + w - 1);
  write_fast_spi(temp, 4);
  spiCommand(0x2B);
  temp[0] = 0x00;
  temp[1] = y;
  temp[2] = 0x00;
  temp[3] = ((y + h - 1) & 0xFF);
  write_fast_spi(temp, 4);
  spiCommand(0x2C);
}

void initDisplay() {
  uint8_t temp[25];
  pinMode(LCD_CS, OUTPUT);
  pinMode(LCD_RS, OUTPUT);
  pinMode(LCD_RESET, OUTPUT);
  pinMode(LCD_DET, OUTPUT);

  digitalWrite(LCD_CS , HIGH);
  digitalWrite(LCD_RS , HIGH);

  digitalWrite(LCD_RESET, HIGH);
  delay(20);
  digitalWrite(LCD_RESET, LOW);
  delay(100);
  digitalWrite(LCD_RESET, HIGH);
  delay(100);
  startWrite();
  spiCommand(54);
  spiWrite(0);
  temp[0] = 0x00;
  write_fast_spi(temp, 1);
  spiCommand(58);
  temp[0] = 5;
  write_fast_spi(temp, 1);
  spiCommand(178);
  spiWrite(12);
  spiWrite(12);
  spiWrite(0);
  spiWrite(51);
  spiWrite(51);
  temp[0] = 12;
  temp[1] = 12;
  temp[2] = 0;
  temp[3] = 51;
  temp[4] = 51;
  write_fast_spi(temp, 5);
  spiCommand(183);
  temp[0] = 53;
  write_fast_spi(temp, 1);
  spiCommand(187);
  temp[0] = 25;
  write_fast_spi(temp, 1);
  spiCommand(192);
  temp[0] = 44;
  write_fast_spi(temp, 1);
  spiCommand(194);
  temp[0] = 1;
  write_fast_spi(temp, 1);
  spiCommand(195);
  temp[0] = 18;
  write_fast_spi(temp, 1);
  spiCommand(196);
  temp[0] = 32;
  write_fast_spi(temp, 1);
  spiCommand(198);
  temp[0] = 15;
  write_fast_spi(temp, 1);
  spiCommand(208);
  temp[0] = 164;
  temp[1] = 161;
  write_fast_spi(temp, 2);
  spiCommand(224);
  temp[0] = 208;
  temp[1] = 4;
  temp[2] = 13;
  temp[3] = 17;
  temp[4] = 19;
  temp[5] = 43;
  temp[6] = 63;
  temp[7] = 84;
  temp[8] = 76;
  temp[9] = 24;
  temp[10] = 13;
  temp[11] = 11;
  temp[12] = 31;
  temp[13] = 35;
  write_fast_spi(temp, 14);
  spiCommand(225);
  temp[0] = 208;
  temp[1] = 4;
  temp[2] = 12;
  temp[3] = 17;
  temp[4] = 19;
  temp[5] = 44;
  temp[6] = 63;
  temp[7] = 68;
  temp[8] = 81;
  temp[9] = 47;
  temp[10] = 31;
  temp[11] = 31;
  temp[12] = 32;
  temp[13] = 35;
  write_fast_spi(temp, 14);
  spiCommand(33);
  spiCommand(17);
  delay(120);
  spiCommand(41);
  spiCommand(0x11);
  spiCommand(0x29);
  setAddrWindowDisplay(0, 0, 240, 240);
  displayColor();
  endWrite();
}

void spiCommand(uint8_t d) {
  digitalWrite(LCD_RS , LOW);
  write_fast_spi(&d, 1);
  digitalWrite(LCD_RS , HIGH);
}

void spiWrite(uint8_t d) {
  write_fast_spi(&d, 1);
}

void startWrite(void) {
  enable_spi(true);
  digitalWrite(LCD_CS , LOW);
}

void endWrite(void) {
  digitalWrite(LCD_CS , HIGH);
  enable_spi(false);
}

void displayColor(uint16_t color) {
  uint32_t currentPart;
  uint32_t currentAll = (widthheigthWindow * 2);
  uint32_t colorSize = LCD_BUFFER_SIZE;
  if (currentAll < colorSize)colorSize = currentAll;
  for (int i = 0; i <= colorSize; i++) {
    lcd_buffer[i++] = color >> 8;
    lcd_buffer[i] = color;
  }
  do
  {
    if (currentAll >= LCD_BUFFER_SIZE)currentPart = LCD_BUFFER_SIZE;
    else
      currentPart = currentAll;
    write_fast_spi(lcd_buffer, currentPart);
    currentAll -= currentPart;
  }
  while ( currentAll > 0);
}
