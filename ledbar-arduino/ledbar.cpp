#include "ledbar.h"

// Contructor
LedBar::LedBar() {
  // Init LCD display
  lcdInit();
}

// Init LCD display
void LedBar::lcdInit() {
  // Init
  lcd = new LiquidCrystal_I2C(0x27, 20, 4);
  lcd->init();
  // Turn on backlight
  lcd->backlight();
}