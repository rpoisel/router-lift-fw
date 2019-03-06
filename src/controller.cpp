#include <controller.h>
#include <ui.h>

namespace RouterFW
{

void Controller::begin()
{
  enc.begin(true);
  UI::instance().begin();
}

void Controller::tick()
{
  tickInternal();

  switch (state)
  {
  case IN_MENU_MOVE:
    handleMenuMove();
    break;
  case IN_MENU_RESET:
    handleMenuReset();
    break;
  case IN_MOVING:
    handleMoving();
    break;
  default:
    break;
  }
}

void Controller::tickInternal()
{
  encPos = enc.process();
  button.tick();
  lowerLimit.tick();
  upperLimit.tick();
}

void Controller::handleMenuMove()
{
  if (button.rTrig())
  {
    state = IN_MOVING;
    UI::instance().setMoving();
    return;
  }
  if (encPos)
  {
    state = IN_MENU_RESET;
    UI::instance().setReset();
  }
}
void Controller::handleMenuReset()
{
  if (button.rTrig())
  {
    pos = 0;
    stepper.reset();
    UI::instance().setPos(0);
  }
  if (encPos)
  {
    state = IN_MENU_MOVE;
    UI::instance().setMove();
  }
}
void Controller::handleMoving()
{
  if (button.rTrig())
  {
    state = IN_MENU_MOVE;
    UI::instance().setMove();
  }
  if (!encPos)
  {
    return;
  }
  // consider limit switches
  auto incPos = encPos == DIR_CCW ? 10 : -10;
  pos += incPos;
  stepper.addSteps(incPos);
  UI::instance().setPos(pos);
}

} // namespace RouterFW