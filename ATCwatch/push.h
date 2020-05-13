
#pragma once

#include "Arduino.h"

void init_push();
void show_push(String pushMSG);
String get_push_msg(int returnLength=0);
