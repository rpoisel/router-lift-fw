#include <components.h>

Rotary myEnc(5, 6);
Stepper stepper(200 /* steps */, 2 /* direction */, 3 /* step */);

MyDisplay<LiquidCrystal_I2C> display(0x27, 20, 4);
MyRenderer<LiquidCrystal_I2C> my_renderer(display);
MenuSystem ms(my_renderer);