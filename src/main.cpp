#include <controller.h>

#include <Arduino.h>

using namespace RouterFW;

static void setupTimerInterrupt();

void setup()
{
  Controller::instance().begin();
  setupTimerInterrupt();
}

void loop()
{
  Controller::instance().tick();
}

static void setupTimerInterrupt()
{
  noInterrupts();

  // set timer0 interrupt at 2kHz
  TCCR0A = 0; // set entire TCCR2A register to 0
  TCCR0B = 0; // same for TCCR2B
  TCNT0 = 0;  // initialize counter value to 0
  // set compare match register for 2khz increments
  OCR0A = (16L * 10 ^ 6) / (2000L * 64) - 1; // (must be <256)
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS01 and CS00 bits for 64 prescaler
  TCCR0B |= (1 << CS01) | (1 << CS00);
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);

  interrupts();
}

ISR(TIMER0_COMPA_vect)
{
  Controller::instance().isrHandler();
}