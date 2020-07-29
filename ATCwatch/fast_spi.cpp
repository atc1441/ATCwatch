/*
 * Copyright (c) 2020 Aaron Christophel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "fast_spi.h"
#include "pinout.h"

void init_fast_spi() {
  pinMode(LCD_SCK, OUTPUT);
  pinMode(LCD_SDI, OUTPUT);
  pinMode(SPI_MISO, INPUT);
  pinMode(LCD_CS, OUTPUT);
  digitalWrite(LCD_SCK, HIGH);
  digitalWrite(LCD_SDI, HIGH);
  digitalWrite(LCD_CS, HIGH);

  NRF_SPIM2->PSELSCK  = SPI_SCK;
  NRF_SPIM2->PSELMOSI = SPI_MOSI;
  NRF_SPIM2->PSELMISO = SPI_MISO;
  NRF_SPIM2->FREQUENCY = 0x80000000;
  NRF_SPIM2->INTENSET = 0;
  NRF_SPIM2->ORC = 255;
  NRF_SPIM2->CONFIG = 0;
}

void enable_spi(bool state) {
  if (state)
    NRF_SPIM2->ENABLE = 7;
  else {
    while (NRF_SPIM2->ENABLE == 0) {
      NRF_SPIM2->ENABLE = 0;
    }
  }
}

void enable_workaround(NRF_SPIM_Type * spim, uint32_t ppi_channel, uint32_t gpiote_channel) {
  NRF_GPIOTE->CONFIG[gpiote_channel] = (GPIOTE_CONFIG_MODE_Event << GPIOTE_CONFIG_MODE_Pos) |
                                       (spim->PSEL.SCK << GPIOTE_CONFIG_PSEL_Pos) |
                                       (GPIOTE_CONFIG_POLARITY_Toggle << GPIOTE_CONFIG_POLARITY_Pos);

  NRF_PPI->CH[ppi_channel].EEP = (uint32_t) &NRF_GPIOTE->EVENTS_IN[gpiote_channel];
  NRF_PPI->CH[ppi_channel].TEP = (uint32_t) &spim->TASKS_STOP;
  NRF_PPI->CHENSET = 1U << ppi_channel;
}

void disable_workaround(NRF_SPIM_Type * spim, uint32_t ppi_channel, uint32_t gpiote_channel) {
  NRF_GPIOTE->CONFIG[gpiote_channel] = 0;
  NRF_PPI->CH[ppi_channel].EEP = 0;
  NRF_PPI->CH[ppi_channel].TEP = 0;
  NRF_PPI->CHENSET = ppi_channel;
}

void write_fast_spi(const uint8_t *ptr, uint32_t len) {
  if (len == 1) {
    enable_workaround(NRF_SPIM2, 8, 8);
  } else {
    disable_workaround(NRF_SPIM2, 8, 8);
  }

  int v2 = 0;
  do
  {
    NRF_SPIM2->EVENTS_END = 0;
    NRF_SPIM2->EVENTS_ENDRX = 0;
    NRF_SPIM2->EVENTS_ENDTX = 0;
    NRF_SPIM2->TXD.PTR = (uint32_t) ptr + v2;
    if ( len <= 0xFF )
    {
      NRF_SPIM2->TXD.MAXCNT = len;
      v2 += len;
      len = 0;
    }
    else
    {
      NRF_SPIM2->TXD.MAXCNT = 255;
      v2 += 255;
      len -= 255;
    }
    NRF_SPIM2->RXD.PTR = 0;
    NRF_SPIM2->RXD.MAXCNT = 0;
    NRF_SPIM2->TASKS_START = 1;
    while (NRF_SPIM2->EVENTS_END == 0);
    NRF_SPIM2->EVENTS_END = 0;
  }
  while ( len );
}

void read_fast_spi(uint8_t *ptr, uint32_t len)
{
  if (len == 1) {
    enable_workaround(NRF_SPIM2, 8, 8);
  } else {
    disable_workaround(NRF_SPIM2, 8, 8);
  }

  int v2 = 0;
  do
  {
    NRF_SPIM2->EVENTS_END = 0;
    NRF_SPIM2->EVENTS_ENDRX = 0;
    NRF_SPIM2->EVENTS_ENDTX = 0;
    NRF_SPIM2->TXD.PTR = 0;
    NRF_SPIM2->TXD.MAXCNT = 0;
    NRF_SPIM2->RXD.PTR = (int)ptr + v2;
    if ( len <= 0xFF )
    {
      NRF_SPIM2->RXD.MAXCNT = len;
      v2 += len;
      len = 0;
    }
    else
    {
      NRF_SPIM2->RXD.MAXCNT = 255;
      v2 += 255;
      len -= 255;
    }
    NRF_SPIM2->TASKS_START = 1;
    while (NRF_SPIM2->EVENTS_END == 0);
    NRF_SPIM2->EVENTS_END = 0;
  }
  while ( len );
}
