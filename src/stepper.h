#ifndef STEPPER_H
#define STEPPER_H

#include <stdint.h>

class Stepper
{
  public:
  Stepper(uint32_t numberOfSteps, uint8_t directionPin, uint8_t stepPin);

  /* to be called from outside an ISR */
  void setSpeed(uint32_t whatSpeed);
  void addSteps(int32_t numberOfSteps);
  void reset();
  /* to be called from insicde an ISR */
  void update();

  private:
  uint32_t const numberOfSteps;
  uint8_t const directionPin;
  uint8_t const stepPin;
  unsigned long stepDelay;
  int32_t volatile stepsLeft;
  unsigned long volatile lastStepTime;
  bool volatile pinState;
};

#endif /* STEPPER_H */