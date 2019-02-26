#ifndef STEPPER_H
#define STEPPER_H

#include <stdint.h>

class Stepper
{
  public:
  Stepper(uint32_t numberOfSteps, uint8_t directionPin, uint8_t stepPin);

  void setSpeed(uint32_t whatSpeed);
  void step(uint32_t numberOfSteps);
  void update();

  private:
  uint32_t const numberOfSteps;
  uint8_t const directionPin;
  uint8_t const stepPin;
  unsigned long stepDelay;
  int32_t stepsLeft;
  unsigned long lastStepTime;
};

#endif /* STEPPER_H */