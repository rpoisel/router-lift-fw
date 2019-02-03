#include <ui.h>

MyDisplay::MyDisplay(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows)
    : lcd(lcd_Addr, lcd_cols, lcd_rows)
{
  lcd.init();
  lcd.backlight();
  drawTitle();
}

void MyDisplay::drawTitle()
{
  lcd.setCursor(3, 0);
  lcd.print("Hello, world!");
  lcd.setCursor(2, 1);
  lcd.print("Router-Table");
  lcd.setCursor(0, 2);
  lcd.print("Firmware 0.9.0");
  lcd.setCursor(2, 3);
  lcd.print("(C) Rainer Poisel");
}

void MyRenderer::render(Menu const& menu) const
{
  display.getRaw().clear();
  display.getRaw().setCursor(0, 0);
  display.getRaw().print(menu.get_name());
  display.getRaw().setCursor(0, 1);
  menu.get_current_component()->render(*this);
}

void MyRenderer::render_menu_item(MenuItem const& menu_item) const
{
  display.getRaw().print(menu_item.get_name());
}

void MyRenderer::render_back_menu_item(BackMenuItem const& menu_item) const
{
  display.getRaw().print(menu_item.get_name());
}

void MyRenderer::render_numeric_menu_item(NumericMenuItem const& menu_item) const
{
  display.getRaw().print(menu_item.get_name());
}

void MyRenderer::render_menu(Menu const& menu) const
{
  display.getRaw().print(menu.get_name());
}