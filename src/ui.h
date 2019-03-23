#ifndef UI_H
#define UI_H

#include <LiquidCrystal_I2C.h>

namespace RouterFW
{
class UI
{
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
    drawPos(0);
  }
  void drawPos(int32_t pos)
  {
    lcd.setCursor(4, 1);
    lcd.print((float)pos / 100);
    lcd.print(" mm         ");
  }
  void drawMenu(char const* firstItem, char const* secondItem)
  {
    lcd.setCursor(2, 2);
    lcd.print("> ");
    lcd.setCursor(4, 2);
    lcd.print(firstItem);
    lcd.setCursor(4, 3);
    lcd.print(secondItem);
  }

  private:
  UI() : lcd(0x27 /* lcd_Addr */, 20 /* lcd_cols */, 4 /* lcd_rows */)
  {
  }
  UI(const UI&);
  UI& operator=(const UI&);

  LiquidCrystal_I2C lcd;
};
} // namespace RouterFW

#endif /* UI_H */