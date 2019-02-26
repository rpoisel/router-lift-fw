#include <components.h>
#include <ui.h>

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

void setupMenu()
{
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