#include <LiquidCrystal_I2C.h>
#include "Arduino.h"

// RGB LED Pins
#define PIN_RGB_R 3
#define PIN_RGB_G 5
#define PIN_RGB_B 6

class LedBar {
  // LCD display
  LiquidCrystal_I2C *lcd;

 private:
  // Init LCD display
  void lcdInit();
  // Init output's/input's
  void ioInit();
  // Greetings display
  void greetingLoad();
  // On connection wait
  bool connectWait();
  // RGB Control
  void rgbSet(int r, int g, int b);
  
 public:
  // Contructor
  LedBar();
  // Loop tick
  void tick();
};