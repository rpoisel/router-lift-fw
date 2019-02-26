#include <components.h>
#include <stepper.h>
#include <ui.h>

#include <Arduino.h>

static uint8_t const BUTTON_PIN = 4;

static int buttonOldVal;
static int32_t encOldPos;

static void handleButton();
static void handleRotaryEncoder();
static void setupTimerInterrupt();

void setup()
{
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  buttonOldVal = digitalRead(BUTTON_PIN);
  display.begin();
  encOldPos = myEnc.read();

  setupMenu();
  setupTimerInterrupt();
}

void loop()
{
  handleButton();
  handleRotaryEncoder();
}

static void handleButton()
{
  auto buttonCurVal = digitalRead(BUTTON_PIN);
  if (buttonCurVal == LOW && buttonOldVal == HIGH)
  {
    ms.select();
    ms.display();
  }
  buttonOldVal = buttonCurVal;
}

static void handleRotaryEncoder()
{
  int32_t encCurPos = myEnc.read() / 4;
  if (encCurPos != encOldPos)
  {
    if (encCurPos > encOldPos)
    {
      ms.prev();
    }
    else
    {
      ms.next();
    }
    ms.display();
    encOldPos = encCurPos;
  }
}

static void setupTimerInterrupt()
{
  noInterrupts();

  // set timer0 interrupt at 1kHz
  TCCR0A = 0; // set entire TCCR2A register to 0
  TCCR0B = 0; // same for TCCR2B
  TCNT0 = 0;  // initialize counter value to 0
  // set compare match register for 2khz increments
  OCR0A = (16L * 10 ^ 6) / (1000L * 64) - 1; // (must be <256)
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
  stepper.update();
}