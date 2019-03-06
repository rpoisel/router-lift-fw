#ifndef UI_H
#define UI_H

#include <LiquidCrystal_I2C.h>

namespace RouterFW
{
class UI
{
  enum MenuSelection { MOVE = 0, RESET, MOVING };

  public:
  static UI& instance()
  {
    static UI instance;
    return instance;
  }

  void begin()
  {
    lcd.init();
    lcd.backlight();
    drawInterface();
  }
  void setPos(int32_t pos)
  {
    lcd.setCursor(4, 1);
    lcd.print((float)pos / 100);
    lcd.print(" mm         ");
  }
  void setMove()
  {
    drawMenu(MOVE);
  }
  void setReset()
  {
    drawMenu(RESET);
  }
  void setMoving()
  {
    drawMenu(MOVING);
  }

  private:
  UI() : lcd(0x27 /* lcd_Addr */, 20 /* lcd_cols */, 4 /* lcd_rows */)
  {
  }
  UI(const UI&);
  UI& operator=(const UI&);
  void drawMenu(MenuSelection selection)
  {
    lcd.setCursor(4, 2);
    lcd.print(selection == MOVE ? "> Move" : "  Move");
    lcd.setCursor(4, 3);
    lcd.print(selection == RESET ? "> Reset" : "  Reset");
  }
  void drawInterface()
  {
    lcd.setCursor(4, 1);
    lcd.print("0.0 mm");
    lcd.setCursor(4, 2);
    lcd.print("  Move");
    lcd.setCursor(4, 3);
    lcd.print("  Reset");
    drawMenu(MOVE);
  }

  LiquidCrystal_I2C lcd;
};
} // namespace RouterFW

#endif /* UI_H */