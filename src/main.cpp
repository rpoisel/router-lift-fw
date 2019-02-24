
#include <stepper.h>
#include <ui.h>

#include <Arduino.h>
#include <Encoder.h>

static Encoder myEnc(5, 6);
static Stepper stepper(200 /* steps */, 2 /* direction */, 3 /* step */);

static MyDisplay<LiquidCrystal_I2C> display(0x27, 20, 4);
static MyRenderer<LiquidCrystal_I2C> my_renderer(display);
static MenuSystem ms(my_renderer);

static int32_t oldPos;

static MenuItem menuMainItem1("Move +1    Step",
                              [](MenuComponent* p_menu_component) { stepper.step(1); });
static MenuItem menuMainItem2("Move +10   Steps",
                              [](MenuComponent* p_menu_component) { stepper.step(10); });
static MenuItem menuMainItem3("Move +100  Steps",
                              [](MenuComponent* p_menu_component) { stepper.step(100); });
static MenuItem menuMainItem4("Move +1000 Steps",
                              [](MenuComponent* p_menu_component) { stepper.step(1000); });
static MenuItem menuMainItem5("Move -1    Step",
                              [](MenuComponent* p_menu_component) { stepper.step(-1); });
static MenuItem menuMainItem6("Move -10   Steps",
                              [](MenuComponent* p_menu_component) { stepper.step(-10); });
static MenuItem menuMainItem7("Move -100  Steps",
                              [](MenuComponent* p_menu_component) { stepper.step(-100); });
static MenuItem menuMainItem8("Move -1000 Steps",
                              [](MenuComponent* p_menu_component) { stepper.step(-1000); });
static Menu menuSub("Settings");
static MenuItem menuSubItem1("Speed",
                             [](MenuComponent* p_menu_component) { stepper.setSpeed(200); });
static MenuItem menuSubItem2("Back", [](MenuComponent* p_menu_component) {
  ms.back();
  ms.display();
});

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

static void handleButton();
static void handleRotaryEncoder();

void loop()
{
  handleButton();
  handleRotaryEncoder();
  stepper.update();
}

static void handleButton()
{
  auto curButtonVal = digitalRead(BUTTON_PIN);
  if (curButtonVal == LOW && lastButtonVal == HIGH)
  {
    ms.select();
    ms.display();
  }
  lastButtonVal = curButtonVal;
}

static void handleRotaryEncoder()
{
  int32_t curPos = myEnc.read() / 4;
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
}