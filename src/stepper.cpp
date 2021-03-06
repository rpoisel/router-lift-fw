#include <stepper.h>

#include <Arduino.h>

#include <util/atomic.h>

Stepper::Stepper(uint32_t numberOfSteps, uint8_t directionPin, uint8_t stepPin)
    : numberOfSteps(numberOfSteps), directionPin(directionPin), stepPin(stepPin), stepDelay(0),
      pinState(false)
{
  pinMode(directionPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  setSpeed(100);
}

void Stepper::update()
{
  if (pinState)
  {
    pinState = false;
    digitalWrite(stepPin, LOW);
    return;
  }
  if (!stepsLeft)
  {
    return;
  }
  auto now = micros();
  if (now - lastStepTime < stepDelay)
  {
    return;
  }

  pinState = true;
  digitalWrite(stepPin, HIGH);

  lastStepTime = now;

  stepsLeft += (stepsLeft > 0) ? -1 : 1;
}

void Stepper::setSpeed(uint32_t whatSpeed)
{
  stepDelay = 60L * 1000 * 1000 / (numberOfSteps * whatSpeed);
}

void Stepper::addSteps(int32_t numberOfSteps)
{
  uint8_t direction;
  ATOMIC_BLOCK(ATOMIC_FORCEON)
  {
    stepsLeft += numberOfSteps;
    direction =stepsLeft > 0 ? HIGH : LOW;
  }
  digitalWrite(directionPin, direction);
}

void Stepper::reset()
{
  ATOMIC_BLOCK(ATOMIC_FORCEON)
  {
    stepsLeft = 0;
  }
}