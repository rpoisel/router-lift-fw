#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <Rotary.h>

#include <stepper.h>
#include <ui.h>

extern Rotary myEnc;
extern Stepper stepper;

extern MyDisplay<LiquidCrystal_I2C> display;
extern MyRenderer<LiquidCrystal_I2C> my_renderer;
extern MenuSystem ms;

#endif /* COMPONENTS_H */