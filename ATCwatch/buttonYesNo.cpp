
#include "buttonYesNo.h"
#include "Arduino.h"
#include "display.h"

  int button_start_x = 30;
  int button_start_y = 50;
  int button_size_x = 240 -(button_start_x*2);
  int button_size_y = 240 -(button_start_y*2);

  int button_yes_start_x = button_start_x+10;
  int button_yes_start_y = button_start_y+button_size_y-10-30;

  int button_no_start_x = button_start_x+button_size_x-10-75;
  int button_no_start_y = button_start_y+button_size_y-10-30;

void drawYesNoButton(String text) {
  displayRect(button_start_x, button_start_y, button_size_x, button_size_y, 0xCE18);
  displayPrintln(button_start_x+10, button_start_y+10, text, 0xFFFF, 0xFFFF, 2);
  
  displayRect(button_yes_start_x, button_yes_start_y, 75, 30, 0x9C71);
  displayPrintln(button_yes_start_x+10, button_yes_start_y+10, "Yes", 0xFFFF, 0xFFFF, 2);
  
  displayRect(button_no_start_x, button_no_start_y, 75, 30, 0x9C71);
  displayPrintln(button_no_start_x+10, button_no_start_y+10, "No", 0xFFFF, 0xFFFF, 2);
}

int checkYesNoButtonClick(uint32_t x, uint32_t y){
 if (button_yes_start_x <= x && x <= (button_yes_start_x + 75) && button_yes_start_y <= y && y <= (button_yes_start_y + 30))   
      return 1;
  else if (button_no_start_x <= x && x <= (button_no_start_x + 75) && button_yes_start_y <= y && y <= (button_no_start_y + 30))
      return 2;
      return 0;
}
