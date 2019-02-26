#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <Encoder.h>

#include <stepper.h>
#include <ui.h>

extern Encoder myEnc;
extern Stepper stepper;

extern MyDisplay<LiquidCrystal_I2C> display;
extern MyRenderer<LiquidCrystal_I2C> my_renderer;
extern MenuSystem ms;

#endif /* COMPONENTS_H */