#ifndef UI_H
#define UI_H

#include <LiquidCrystal_I2C.h>
#include <MenuSystem.h>

void setupMenu();

class MyLiquidCrystal
{
  public:
  inline MyLiquidCrystal(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows)
  {
  }
  inline void clear()
  {
  }
  inline void init()
  {
  }
  inline void backlight()
  {
  }
  inline void setCursor(uint8_t, uint8_t)
  {
  }
  inline size_t print(char const* str)
  {
    return 0;
  }
};

class SerialDisplay
{
  public:
  inline SerialDisplay(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows)
  {
  }
  inline void clear()
  {
  }
  inline void init()
  {
  }
  inline void backlight()
  {
  }
  inline void setCursor(uint8_t, uint8_t)
  {
  }
  inline size_t print(char const* str)
  {
    return Serial.println(str);
  }
};

template <typename display_type>
class MyDisplay
{
  public:
  MyDisplay(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows)
      : lcd(lcd_Addr, lcd_cols, lcd_rows)
  {
  }
  void begin()
  {
    lcd.init();
    lcd.backlight();
    drawTitle();
  }
  inline display_type& getRaw()
  {
    return lcd;
  }

  private:
  void drawTitle()
  {
    lcd.setCursor(4, 0);
    lcd.print("Router-Table");
    lcd.setCursor(3, 1);
    lcd.print("Firmware 0.9.0");
    lcd.setCursor(1, 2);
    lcd.print("(C) Rainer Poisel");
    lcd.setCursor(4, 3);
    lcd.print("Insert Coin");
  }
  display_type lcd;
};

template <typename display_type>
class MyRenderer : public MenuComponentRenderer
{
  public:
  MyRenderer(MyDisplay<display_type>& display) : display(display)
  {
  }
  void render(Menu const& menu) const
  {
    if (menu.get_current_component_num() == menu.get_previous_component_num())
    {
      return;
    }
    display.getRaw().clear();
    display.getRaw().setCursor(0, 0);
    display.getRaw().print(menu.get_name());
    display.getRaw().setCursor(0, 1);
    menu.get_current_component()->render(*this);
  }
  void render_menu_item(MenuItem const& menu_item) const
  {
    display.getRaw().print(menu_item.get_name());
  }
  void render_back_menu_item(BackMenuItem const& menu_item) const
  {
    display.getRaw().print(menu_item.get_name());
  }
  void render_numeric_menu_item(NumericMenuItem const& menu_item) const
  {
    display.getRaw().print(menu_item.get_name());
  }
  void render_menu(Menu const& menu) const
  {
    display.getRaw().print(menu.get_name());
  }

  private:
  MyDisplay<display_type>& display;
};

#endif /* UI_H */