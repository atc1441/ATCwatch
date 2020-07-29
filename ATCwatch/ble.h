/*
 * Copyright (c) 2020 Aaron Christophel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "Arduino.h"
#include <BLEPeripheral.h>

void init_ble();
void ble_feed();
void ble_ConnectHandler(BLECentral& central);
void ble_DisconnectHandler(BLECentral& central);
void ble_DisconnectHandler(BLECentral& central);
void ble_written(BLECentral& central, BLECharacteristic& characteristic);
void ble_write(String Command);
bool get_vars_ble_connected();
void set_vars_ble_connected(bool state);
void filterCmd(String Command);
