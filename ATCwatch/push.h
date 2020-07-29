/*
 * Copyright (c) 2020 Aaron Christophel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "Arduino.h"

void init_push();
void show_push(String pushMSG);
void show_http(String httpMSG);
String get_http_msg(int returnLength=0);
String get_push_msg(int returnLength=0);
