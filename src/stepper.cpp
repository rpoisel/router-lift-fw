#include <stepper.h>

#include <Arduino.h>

void StepperMoving::execute(FSM* fsm)
{
  auto now = micros();
  if (now - this->lastStepTime < stepper->getStepDelay())
  {
    return;
  }

  this->stepsLeft += (this->stepsLeft > 0) ? -1 : 1;
  this->stepNumber += (this->stepsLeft > 0) ? 1 : -1;

  this->doStep(this->stepNumber);
  this->lastStepTime = now;

  if (!this->stepsLeft)
  {
    fsm->setState(stepper->getIdleState());
  }
}

void StepperMoving::reset(int32_t numberOfSteps)
{
  this->stepsLeft = numberOfSteps;
}

void StepperMoving::doStep(uint32_t thisStep) const
{
  if (stepper->getPinCount() == 2)
  {
    switch (thisStep % 4)
    {
    case 0:
      digitalWrite(stepper->getMotorPin1(), LOW);
      digitalWrite(stepper->getMotorPin2(), HIGH);
      break;
    case 1:
      digitalWrite(stepper->getMotorPin1(), HIGH);
      digitalWrite(stepper->getMotorPin2(), HIGH);
      break;
    case 2:
      digitalWrite(stepper->getMotorPin1(), HIGH);
      digitalWrite(stepper->getMotorPin2(), LOW);
      break;
    case 3:
      digitalWrite(stepper->getMotorPin1(), LOW);
      digitalWrite(stepper->getMotorPin2(), LOW);
      break;
    }
  }
}

void StepperIdle::execute(FSM* fsm)
{
}

Stepper::Stepper(uint32_t numberOfSteps, uint8_t motorPin1, uint8_t motorPin2)
    : fsm(), stepDelay(0), stateIdle(), stateMoving(this), pinCount(2),
      numberOfSteps(numberOfSteps), motorPin1(motorPin1), motorPin2(motorPin2)
{
  fsm.setState(&stateIdle);
  pinMode(this->motorPin1, OUTPUT);
  pinMode(this->motorPin2, OUTPUT);
}

void Stepper::update()
{
  fsm.update();
}

void Stepper::setSpeed(uint32_t whatSpeed)
{
  this->stepDelay = 60L * 1000L * 1000L / (this->numberOfSteps * whatSpeed);
}

void Stepper::step(uint32_t numberOfSteps)
{
  stateMoving.reset(numberOfSteps);
  fsm.setState(&stateMoving);
}