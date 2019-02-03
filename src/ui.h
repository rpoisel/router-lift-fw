#ifndef UI_H
#define UI_H

#include <LiquidCrystal_I2C.h>
#include <MenuSystem.h>

class MyDisplay
{
  public:
  MyDisplay(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows);
  void drawTitle();
  inline LiquidCrystal_I2C& getRaw()
  {
    return lcd;
  }

  private:
  LiquidCrystal_I2C lcd;
};

class MyRenderer : public MenuComponentRenderer
{
  public:
  MyRenderer(MyDisplay& display) : display(display)
  {
  }
  void render(Menu const& menu) const;
  void render_menu_item(MenuItem const& menu_item) const;
  void render_back_menu_item(BackMenuItem const& menu_item) const;
  void render_numeric_menu_item(NumericMenuItem const& menu_item) const;
  void render_menu(Menu const& menu) const;

  private:
  MyDisplay& display;
};

#endif /* UI_H */