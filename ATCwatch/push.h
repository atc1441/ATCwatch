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
void show_appName(String nameMSG);
void show_msgBody(String bodyMSG);
void show_titl(String titlMSG);
void show_tick(String titlMSG);
String get_http_msg(int returnLength=0);
String get_push_msg(int returnLength=0);
String get_name_msg(int returnLength=0);
String get_body_msg(int returnLength=0);
String get_titl_msg(int returnLength=0);
String get_tick_msg(int returnLength=0);
