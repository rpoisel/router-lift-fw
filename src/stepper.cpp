#include <stepper.h>

#include <Arduino.h>

void StepperMoving::execute(FSM* fsm)
{
  if (!this->stepsLeft)
  {
    fsm->setState(stepper->getIdleState());
  }
  auto now = micros();
  if (now - this->lastStepTime < stepper->getStepDelay())
  {
    return;
  }

  this->doStep();
  this->lastStepTime = now;

  this->stepsLeft += (this->stepsLeft > 0) ? -1 : 1;
}

void StepperMoving::reset(int32_t numberOfSteps)
{
  this->stepsLeft = numberOfSteps;
}

void StepperMoving::doStep() const
{
  digitalWrite(stepper->getDirectionPin(), this->stepsLeft > 0 ? HIGH : LOW);
  digitalWrite(stepper->getStepPin(), HIGH);
  delayMicroseconds(1);
  digitalWrite(stepper->getStepPin(), LOW);
}

Stepper::Stepper(uint32_t numberOfSteps, uint8_t directionPin, uint8_t stepPin)
    : fsm(), stepDelay(0), stateIdle(), stateMoving(this), pinCount(2),
      numberOfSteps(numberOfSteps), directionPin(directionPin), stepPin(stepPin)
{
  fsm.setState(&stateIdle);
  pinMode(this->directionPin, OUTPUT);
  pinMode(this->stepPin, OUTPUT);
  setSpeed(100);
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