#include "classScreen.h"
#include "images.h"
#include "menu.h"
#include "display.h"
#include "menuAppsBase.h"
#include "ble.h"
#include "time.h"
#include "battery.h"
#include "accl.h"
#include "push.h"
#include "touch.h"
#include "heartrate.h"
class App
{
  public:
    App(String title, const uint16_t* symbol, TheScreen* screen)
    {
      _title = title;
      _symbol = symbol;
      _screen = screen;
    }
    String _title;
    const uint16_t* _symbol;
    Screen* _screen;
};

class AppScreen : public TheScreen
{
  public:
    AppScreen(int menuPosition, App* app1, App* app2, App* app3, App* app4)
    {
      _menuPosition = menuPosition;
      _app1 = app1;
      _app2 = app2;
      _app3 = app3;
      _app4 = app4;
    }

    virtual void pre()
    {
      menuAppsBase(_menuPosition);
      displayIconAndText(32, 28, 72, 72, _app1->_title, _app1->_symbol);
      displayIconAndText(136, 28, 72, 72, _app2->_title, _app2->_symbol);
      displayIconAndText(32, 132, 72, 72, _app3->_title, _app3->_symbol);
      displayIconAndText(136, 132, 72, 72, _app4->_title, _app4->_symbol);
    }

    virtual void main()
    {

    }

    virtual void click(touch_data_struct touch_data)
    {
      switch (check_app_click(touch_data.xpos, touch_data.ypos)) {
        case 1:
          change_screen(_app1->_screen);
          break;
        case 2:
          change_screen(_app2->_screen);
          break;
        case 3:
          change_screen(_app3->_screen);
          break;
        case 4:
          change_screen(_app4->_screen);
          break;
        default:
          break;
      }
    }

    virtual void up()
    {
      inc_vars_menu();
    }

    virtual void down()
    {
      dec_vars_menu();
    }

    virtual void left()
    {
    }

    virtual void right()
    {
      display_home();
    }
  private:
    App* _app1;
    App* _app2;
    App* _app3;
    App* _app4;
    uint32_t _menuPosition;
};
