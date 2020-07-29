/*
 * Copyright (c) 2020 Aaron Christophel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "flash.h"
#include "pinout.h"
#include "fast_spi.h"

#define SPIFLASH_PAGE_WRITE       0x02 // Page Program (up to 256 bytes)
#define SPIFLASH_READ             0x03 // Read Data
#define SPIFLASH_READ_STATUS      0x05 // Read Status Register
#define SPIFLASH_WRITE_ENABLE     0x06 // Write Enable
#define SPIFLASH_SUBSECTOR_ERASE  0x20 // SubSector (4K bytes) Erase
#define SPIFLASH_SECTOR_ERASE     0xD8 // Sector (usually 64K bytes) Erase
#define SPIFLASH_RDP              0xAB // Release from Deep Power Down
#define SPIFLASH_DP               0xB9 // Deep Power Down
#define SPIFLASH_MASS_ERASE       0xC7 // Erase entire flash.
#define SPIFLASH_IDREAD           0x9F
#define SPIFLASH_MACREAD          0x4B

bool flash_sleeping = false;

uint8_t temp[8];

void init_flash() {
  pinMode(SPI_CE, OUTPUT);
  digitalWrite(SPI_CE, HIGH);
  flash_sleep(true);
}

void flash_sleep(int state)
{
  startWrite_flash();
  delay(10);
  if ( state )
  {
    temp[0] = SPIFLASH_DP;
    write_fast_spi(temp, 1);
  }
  else
  {
    do
    {
      temp[0] = SPIFLASH_RDP;
      temp[1] = 0x01;
      temp[2] = 0x20;
      temp[3] = 0x30;
      write_fast_spi(temp, 4);
      read_fast_spi(temp, 3);
    }
    while (temp[0] != 0x15 && temp[1] != 0x15 && temp[2] != 0x15);
  }
  endWrite_flash();
  flash_sleeping = state;
}

uint16_t flash_read_id()
{
  if (flash_sleeping)
    flash_sleep(false);
  startWrite_flash();
  temp[0] = SPIFLASH_IDREAD;
  write_fast_spi(temp, 1);
  read_fast_spi(temp, 2);
  endWrite_flash();
  flash_sleep(true);
  return (temp[0] << 8 | temp[1]);
}


void get_temp(uint8_t *ptr) {
  ptr[0] = temp[0];
  ptr[1] = temp[1];
  ptr[2] = temp[2];
  ptr[3] = temp[3];
  ptr[4] = temp[4];
  ptr[5] = temp[5];
  ptr[6] = temp[6];
  ptr[7] = temp[7];
}

void startWrite_flash(void) {
  enable_spi(true);
  digitalWrite(SPI_CE , LOW);
}

void endWrite_flash(void) {
  digitalWrite(SPI_CE , HIGH);
  enable_spi(false);
}
