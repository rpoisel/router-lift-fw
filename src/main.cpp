
#include <stepper.h>
#include <ui.h>

#include <Arduino.h>
#include <Encoder.h>

static Encoder myEnc(5, 6);
static Stepper stepper(200 /* steps */, 2 /* direction */, 3 /* step */);

static MyDisplay display(0x27, 20, 4);
static MyRenderer my_renderer(display);
static MenuSystem ms(my_renderer);

static int32_t oldPos;

MenuItem menuMainItem1("Move +1    Step", [](MenuComponent* p_menu_component) { stepper.step(1); });
MenuItem menuMainItem2("Move +10   Steps", [](MenuComponent* p_menu_component) { stepper.step(10); });
MenuItem menuMainItem3("Move +100  Steps", [](MenuComponent* p_menu_component) { stepper.step(100); });
MenuItem menuMainItem4("Move +1000 Steps", [](MenuComponent* p_menu_component) { stepper.step(1000); });
MenuItem menuMainItem5("Move -1    Step", [](MenuComponent* p_menu_component) { stepper.step(-1); });
MenuItem menuMainItem6("Move -10   Steps",
                       [](MenuComponent* p_menu_component) { stepper.step(-10); });
MenuItem menuMainItem7("Move -100  Steps",
                       [](MenuComponent* p_menu_component) { stepper.step(-100); });
MenuItem menuMainItem8("Move -1000 Steps",
                       [](MenuComponent* p_menu_component) { stepper.step(-1000); });
Menu menuSub("Settings");
MenuItem menuSubItem1("Speed", [](MenuComponent* p_menu_component) { stepper.setSpeed(200); });
MenuItem menuSubItem2("Back", [](MenuComponent* p_menu_component) { ms.back(); ms.display(); });

static uint8_t const BUTTON_PIN = 4;
static int lastButtonVal;

void setup()
{
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  lastButtonVal = digitalRead(BUTTON_PIN);
  display.begin();
  oldPos = myEnc.read();

  ms.get_root_menu().add_item(&menuMainItem1);
  ms.get_root_menu().add_item(&menuMainItem2);
  ms.get_root_menu().add_item(&menuMainItem3);
  ms.get_root_menu().add_item(&menuMainItem4);
  ms.get_root_menu().add_item(&menuMainItem5);
  ms.get_root_menu().add_item(&menuMainItem6);
  ms.get_root_menu().add_item(&menuMainItem7);
  ms.get_root_menu().add_item(&menuMainItem8);
  ms.get_root_menu().add_menu(&menuSub);
  menuSub.add_item(&menuSubItem1);
  menuSub.add_item(&menuSubItem2);
  ms.display();
}

void loop()
{
  int32_t curPos = myEnc.read() / 4;
  auto curButtonVal = digitalRead(BUTTON_PIN);
  if (curButtonVal == LOW && lastButtonVal == HIGH)
  {
    ms.select();
    ms.display();
  }
  lastButtonVal = curButtonVal;
  if (curPos != oldPos)
  {
    if (curPos > oldPos)
    {
      ms.prev();
    }
    else
    {
      ms.next();
    }
    ms.display();
    oldPos = curPos;
  }
  char inChar;
  if ((inChar = Serial.read()) > 0)
  {
    switch (inChar)
    {
    case 'w':
      ms.prev();
      break;
    case 's':
      ms.next();
      break;
    case 'a':
      ms.back();
      break;
    case 'd':
      ms.select();
      break;
    default:
      break;
    }
    ms.display();
  }
  stepper.update();
}