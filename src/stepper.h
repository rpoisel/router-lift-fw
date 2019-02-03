#ifndef STEPPER_H
#define STEPPER_H

#include <FSM.h>

#include <stdint.h>

class Stepper;

class StepperMoving : public State
{
  public:
  StepperMoving(Stepper* stepper) : stepper(stepper), stepsLeft(0), stepNumber(0), lastStepTime(0)
  {
  }
  void execute(FSM* fsm);
  void reset(int32_t numberOfSteps);

  private:
  void doStep(uint32_t thisStep) const;

  Stepper* stepper;
  int32_t stepsLeft;
  uint32_t stepNumber;
  unsigned long lastStepTime;
};

class StepperIdle : public State
{
  public:
  StepperIdle() = default;
  void execute(FSM* fsm);
};

class Stepper
{
  public:
  Stepper(uint32_t numberOfSteps, uint8_t motorPin1, uint8_t motorPin2);

  void setSpeed(uint32_t whatSpeed);
  void step(uint32_t numberOfSteps);

  inline unsigned long getStepDelay() const
  {
    return this->stepDelay;
  }
  constexpr static int version()
  {
    return 6;
  }
  void update();

  inline uint8_t getPinCount() const
  {
    return pinCount;
  }
  inline uint32_t getNumberOfSteps() const
  {
    return numberOfSteps;
  }
  inline uint8_t getMotorPin1() const
  {
    return motorPin1;
  }
  inline uint8_t getMotorPin2() const
  {
    return motorPin2;
  }
  inline State* getIdleState()
  {
    return &stateIdle;
  }
  inline State* getMovingState()
  {
    return &stateMoving;
  }

  private:
  FSM fsm;

  unsigned long stepDelay;
  StepperIdle stateIdle;
  StepperMoving stateMoving;

  uint8_t const pinCount;
  uint32_t const numberOfSteps;
  uint8_t const motorPin1;
  uint8_t const motorPin2;
};

#endif /* STEPPER_H */