
#include "Arduino.h"
#include "sleep.h"
#include "menu.h"
#include "display.h"
#include "inputoutput.h"

String msgText = " ";
String httpText = " ";

void init_push() {

}

String filter_string(String str)
{
  int i = 0, len = str.length();
  while (i < len)
  {
    char c = str[i];
    if ((c >= 0x20))
    {
      ++i;
    }
    else
    {
      str.remove(i, 1);
      --len;
    }
  }
  return str;
}

void show_push(String pushMSG) {
  int commaIndex = pushMSG.indexOf(',');
  int secondCommaIndex = pushMSG.indexOf(',', commaIndex + 1);
  int lastCommaIndex = pushMSG.indexOf(',', secondCommaIndex + 1);
  String MsgText = pushMSG.substring(commaIndex + 1, secondCommaIndex);
  int timeShown = pushMSG.substring(secondCommaIndex + 1, lastCommaIndex).toInt();
  int SymbolNr = pushMSG.substring(lastCommaIndex + 1).toInt();
  msgText = filter_string(MsgText);
  sleep_up(WAKEUP_BLEPUSH);
  display_notify();
  set_motor_ms();
  set_led_ms(100);
  set_sleep_time();
}

void show_http(String httpMSG) {
  httpText = filter_string("http: " + httpMSG);
  set_motor_ms();
  set_sleep_time();
}

String get_http_msg(int returnLength) {
  if (returnLength != 0 || httpText.length() == returnLength) {
    if (httpText.length() < returnLength) {
      String tempText = httpText;
      int toSmall = returnLength - httpText.length();
      for (int i = 0; i < toSmall; i++) {
        tempText += " ";
      }
      return tempText;
    } else if (httpText.length() > returnLength)
      return httpText.substring(0, returnLength - 3) + "...";
  }
  return httpText;
}

String get_push_msg(int returnLength) {
  if (returnLength != 0 || msgText.length() == returnLength) {
    if (msgText.length() < returnLength) {
      String tempText = msgText;
      int toSmall = returnLength - msgText.length();
      for (int i = 0; i < toSmall; i++) {
        tempText += " ";
      }
      return tempText;
    } else if (msgText.length() > returnLength)
      return msgText.substring(0, returnLength - 3) + "...";
  }
  return msgText;
}
