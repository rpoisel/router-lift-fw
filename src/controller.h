#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <fsm.h>
#include <io.h>
#include <states.h>
#include <stepper.h>
#include <ui.h>

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

  void begin()
  {
    enc.begin(true);
    pinMode(9, OUTPUT);
    digitalWrite(9, HIGH);
    UI::instance().begin();
    fsm.setState(StateMenu::instance());
  }
  void tick()
  {
    encPos = enc.process();
    button.tick();
    lowerLimit.tick();
    upperLimit.tick();
    fsm.update();
  }
  void timerHandler()
  {
    stepper.update();
  }
  inline DebouncedInput& getButton()
  {
    return button;
  }
  inline DebouncedInput& getUpperLimit()
  {
    return upperLimit;
  }
  inline DebouncedInput& getLowerLimit()
  {
    return lowerLimit;
  }
  inline Stepper& getStepper()
  {
    return stepper;
  }
  inline unsigned char getEncoderPos() const
  {
    return encPos;
  }
  inline int32_t getRouterPos() const
  {
    return routerPos;
  }
  inline void resetRouterPos()
  {
    routerPos = 0;
  }
  inline void incRouterPos(int32_t steps)
  {
    routerPos += steps;
  }

  private:
  Controller()
      : enc(5, 6), button(4), upperLimit(8), lowerLimit(7),
        stepper(200 /* steps */, 2 /* direction pin */, 3 /* step pin */), encPos(0), routerPos(0)
  {
  }
  Controller(const Controller&);
  Controller& operator=(const Controller&);

  FSM fsm;
  Rotary enc;
  DebouncedInput button;
  DebouncedInput upperLimit;
  DebouncedInput lowerLimit;
  Stepper stepper;
  unsigned char encPos;
  int32_t routerPos;
};

} // namespace RouterFW

#endif /* CONTROLLER_H */