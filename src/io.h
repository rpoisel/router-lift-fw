#ifndef IO_H
#define IO_H

#include <Arduino.h>

/* see: https://www.arduino.cc/en/Tutorial/Debounce */
class DebouncedInput
{
  public:
  DebouncedInput(uint8_t pin, bool usePullup = true) : pin(pin), debounceTime(10)
  {
    pinMode(pin, usePullup ? INPUT_PULLUP : INPUT);
    lastTime = millis();
    curState = digitalRead(pin);
    lastState = curState;
    lastReading = curState;
    valueValid = false;
  }

  bool rTrig() const
  {
    if (!valueValid)
    {
      return false;
    }
    return curState && !lastState;
  }

  bool fTrig() const
  {
    if (!valueValid)
    {
      return false;
    }
    return !curState && lastState;
  }

  void tick()
  {
    int reading = digitalRead(pin);
    if (reading != lastReading)
    {
      lastTime = millis();
    }
    if ((millis() - lastTime) > debounceTime && reading != curState)
    {
      lastState = curState;
      curState = reading;
      valueValid = true;
    }
    else
    {
      valueValid = false;
    }

    lastReading = reading;
  }

  private:
  uint8_t const pin;
  unsigned long const debounceTime;
  unsigned long lastTime;
  bool curState;
  bool lastState;
  bool lastReading;
  bool valueValid;
};

#endif /* IO_H */