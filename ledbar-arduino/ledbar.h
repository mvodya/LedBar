#include "../thirdparty/LiquidCrystal_I2C/LiquidCrystal_I2C.h"
#include "Arduino.h"

class LedBar {
  // LCD display
  LiquidCrystal_I2C *lcd;

 private:
  // Init LCD display
  void lcdInit();

 public:
  // Contructor
  LedBar();
};