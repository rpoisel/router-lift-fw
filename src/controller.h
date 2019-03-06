#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <io.h>
#include <stepper.h>

#include <Rotary.h>

#include <stdint.h>

namespace RouterFW
{

class Controller
{
  public:
  static Controller& instance()
  {
    static Controller controller;
    return controller;
  }
  void begin();
  void tick();
  void isrHandler()
  {
    stepper.update();
  }

  private:
  Controller()
      : enc(5, 6), button(4), upperLimit(8), lowerLimit(7),
        stepper(200 /* steps */, 2 /* direction */, 3 /* step */), state(IN_MENU_MOVE), pos(0),
        encPos(0)
  {
  }
  Controller(const Controller&);
  Controller& operator=(const Controller&);
  void tickInternal();
  void handleMenuMove();
  void handleMenuReset();
  void handleMoving();

  // components
  Rotary enc;
  DebouncedInput button;
  DebouncedInput upperLimit;
  DebouncedInput lowerLimit;
  Stepper stepper;

  // internal state
  enum {
    IN_MENU_MOVE = 0,
    IN_MENU_RESET,
    IN_MOVING,
  } state;
  int32_t pos;
  unsigned char encPos;
};

} // namespace RouterFW

#endif /* CONTROLLER_H */