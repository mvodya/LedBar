#include <LiquidCrystal_I2C.h>
#include "Arduino.h"

class LedBar {
  // LCD display
  LiquidCrystal_I2C *lcd;

 private:
  // Init LCD display
  void lcdInit();
  // Greetings display
  void greetingLoad();
  // On connection wait
  bool connectWait();

 public:
  // Contructor
  LedBar();
  // Loop tick
  void tick();
};