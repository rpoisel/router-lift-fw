
#include <stepper.h>
#include <ui.h>

#include <Arduino.h>
#include <Encoder.h>

static Encoder myEnc(5, 6);
static Stepper stepper(200, 2, 3);

static MyDisplay display(0x27, 20, 4);
static MyRenderer my_renderer(display);
static MenuSystem ms(my_renderer);

static int32_t oldPos;

MenuItem menuMainItem1("Move +1  Step", [](MenuComponent* p_menu_component) { stepper.step(1); });
MenuItem menuMainItem2("Move +10 Steps", [](MenuComponent* p_menu_component) { stepper.step(10); });
MenuItem menuMainItem3("Move -1  Step", [](MenuComponent* p_menu_component) { stepper.step(-1); });
MenuItem menuMainItem4("Move -10 Steps",
                       [](MenuComponent* p_menu_component) { stepper.step(-10); });
Menu menuSub("Settings");
MenuItem menuSubItem1("Speed", [](MenuComponent* p_menu_component) { stepper.setSpeed(10); });

void setup()
{
  Serial.begin(115200);
  display.begin();
  oldPos = myEnc.read();

  ms.get_root_menu().add_item(&menuMainItem1);
  ms.get_root_menu().add_item(&menuMainItem2);
  ms.get_root_menu().add_item(&menuMainItem3);
  ms.get_root_menu().add_item(&menuMainItem4);
  ms.get_root_menu().add_menu(&menuSub);
  menuSub.add_item(&menuSubItem1);
  ms.display();
}

void loop()
{
  int32_t curPos = myEnc.read();
  if (curPos != oldPos)
  {
    Serial.print(curPos);
    oldPos = curPos;
  }
  char inChar;
  if ((inChar = Serial.read()) > 0)
  {
    switch (inChar)
    {
    case 'w':
      ms.prev();
      ms.display();
      break;
    case 's':
      ms.next();
      ms.display();
      break;
    case 'a':
      ms.back();
      ms.display();
      break;
    case 'd':
      ms.select();
      break;
    default:
      break;
    }
  }
  stepper.update();
}