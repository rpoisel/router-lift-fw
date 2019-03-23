#include <controller.h>
#include <states.h>
#include <ui.h>

namespace RouterFW
{

using MenuAction = void (*)(FSM& fsm);
static struct
{
  char const* name;
  MenuAction const action;
} const choosableStates[] = {
    {.name = "Set 0        ",
     .action =
         [](FSM& fsm) {
           (void)fsm;
           Controller::instance().resetRouterPos();
           UI::instance().drawPos(0);
         }},
    {.name = "Move         ", .action = [](FSM& fsm) { fsm.setState(StateMove::instance()); }},
    {.name = "Router toggle", .action = [](FSM& fsm) {
       (void)fsm;
       auto curState = digitalRead(9);
       digitalWrite(9, curState == HIGH ? LOW : HIGH);
     }}};
static size_t const numChoosableStates = sizeof(choosableStates) / sizeof(choosableStates[0]);

void StateMenu::enter(FSM& fsm)
{
  (void)fsm;
  UI::instance().drawMenu(choosableStates[menuPos].name, menuPos + 1 < numChoosableStates
                                                             ? choosableStates[menuPos + 1].name
                                                             : "             ");
}

void StateMenu::execute(FSM& fsm)
{
  if (Controller::instance().getButton().rTrig())
  {
    choosableStates[menuPos].action(fsm);
    return;
  }
  if (Controller::instance().getEncoderPos())
  {
    if (Controller::instance().getEncoderPos() == DIR_CW && menuPos > 0)
    {
      menuPos--;
    }
    else if (Controller::instance().getEncoderPos() == DIR_CCW &&
             menuPos + 1 < numChoosableStates)
    {
      menuPos++;
    }
    UI::instance().drawMenu(choosableStates[menuPos].name, menuPos + 1 < numChoosableStates
                                                               ? choosableStates[menuPos + 1].name
                                                               : "             ");
  }
}

void StateMove::execute(FSM& fsm)
{
  if (Controller::instance().getEncoderPos())
  {
    auto const incSteps = (Controller::instance().getEncoderPos() == DIR_CCW) ? 10 : -10;
    Controller::instance().incRouterPos(incSteps);
    Controller::instance().getStepper().addSteps(incSteps);
    UI::instance().drawPos(Controller::instance().getRouterPos());
  }
  if (Controller::instance().getButton().rTrig())
  {
    fsm.setState(StateMenu::instance());
  }
}

} // namespace RouterFW