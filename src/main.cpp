#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

/*
 * MotorKnob
 *
 * A stepper motor follows the turns of a potentiometer
 * (or other sensor) on analog input 0.
 *
 * http://www.arduino.cc/en/Reference/Stepper
 * This example code is in the public domain.
 */

#include <Encoder.h>
#include <MenuSystem.h>
#include <Stepper.h>

// change this to the number of steps on your motor
int const STEPS = 200;

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper(STEPS, 8, 9, 10, 11);
LiquidCrystal_I2C lcd(0x27, 20, 4);
Encoder myEnc(5, 6);

class MyRenderer : public MenuComponentRenderer {
  public:
  void render(Menu const& menu) const
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(menu.get_name());
    lcd.setCursor(0, 1);
    menu.get_current_component()->render(*this);
  }

  void render_menu_item(MenuItem const& menu_item) const
  {
    lcd.print(menu_item.get_name());
  }

  void render_back_menu_item(BackMenuItem const& menu_item) const
  {
    lcd.print(menu_item.get_name());
  }

  void render_numeric_menu_item(NumericMenuItem const& menu_item) const
  {
    lcd.print(menu_item.get_name());
  }

  void render_menu(Menu const& menu) const
  {
    lcd.print(menu.get_name());
  }
};
MyRenderer my_renderer;
MenuSystem ms(my_renderer);

void setup()
{
  // set the speed of the motor to 30 RPMs
  stepper.setSpeed(30);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("Hello, world!");
  lcd.setCursor(2, 1);
  lcd.print("Router-Table");
  lcd.setCursor(0, 2);
  lcd.print("Firmware 0.9.0");
  lcd.setCursor(2, 3);
  lcd.print("(C) Rainer Poisel");
}

void loop()
{
  static int previous = 0;
  // get the sensor value
  int val = analogRead(0);

  // move a number of steps equal to the change in the
  // sensor reading
  stepper.step(val - previous);

  // remember the previous value of the sensor
  previous = val;
}
