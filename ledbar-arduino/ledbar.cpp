#include "ledbar.h"

// Contructor
LedBar::LedBar() {
  // Init Serial
  Serial.begin(9600);
  // Init LCD display
  lcdInit();
  // Random seed (from unused analog)
  randomSeed(analogRead(A0));
}

// Init LCD display
void LedBar::lcdInit() {
  // Init
  lcd = new LiquidCrystal_I2C(0x27, 20, 4);
  lcd->init();
  // Turn on backlight
  lcd->backlight();
  greetingLoad();
}

// Greetings display
void LedBar::greetingLoad() {
  // Random 0/1
  for (int i = 0; i < 4; i++) {
    lcd->setCursor(0, i);
    for (int j = 0; j < 20; j++) {
      lcd->print(random(2));
      delay(50);
    }
  }
  delay(1000);
  // Remove random
  for (int i = 0; i < 20; i++) {
    lcd->setCursor(i, 0);
    lcd->print(" ");
    lcd->setCursor(19 - i, 1);
    lcd->print(" ");
    lcd->setCursor(i, 2);
    lcd->print(" ");
    lcd->setCursor(19 - i, 3);
    lcd->print(" ");
    delay(200);
  }
  delay(400);
  // Draw device logo
  lcd->setCursor(0, 0);
  lcd->print("LCD BAR");
  lcd->setCursor(0, 3);
  lcd->print("by @mvodya");
  delay(700);
  // Computer connect wait
  lcd->setCursor(0, 1);
  lcd->print("waiting connect");
  while (!connectWait()) {
    lcd->setCursor(15, 1);
    lcd->print("   ");
    lcd->setCursor(15, 1);
    delay(300);
    lcd->print(".");
    delay(300);
    lcd->print(".");
    delay(300);
    lcd->print(".");
    delay(100);
  }
  lcd->setCursor(0, 1);
  lcd->print("connected!         ");
  delay(1000);
  lcd->clear();
}

// On connection wait
bool LedBar::connectWait() {
  if (Serial.readString() == "TRY_CONN")
    return true;
  else
    return false;
}

// Loop tick
void LedBar::tick() {

}