#include "ledbar.h"

// Contructor
LedBar::LedBar() {
  // Init Serial
  Serial.begin(9600);
  // Init LCD display
  lcdInit();
  // Init I/O
  ioInit();
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

// Init output's/input's
void LedBar::ioInit() {
  // RGB Led
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  // Connect indicator
  pinMode(PIN_CONNECT_INDICATOR, OUTPUT);
}

// Greetings display
void LedBar::greetingLoad() {
  // Random 0/1
  for (int i = 0; i < 4; i++) {
    lcd->setCursor(0, i);
    for (int j = 0; j < 20; j++) {
      lcd->print(random(2));
      // Random rgb blink
      rgbSet(random(255), random(255), random(255));
      delay(20);
    }
  }
  // Off rgb
  rgbSet(0, 0, 0);
  delay(500);
  // Remove random
  for (int i = 0; i < 20; i++) {
    rgbSet(0, 0, 255 - (i * 12));
    lcd->setCursor(i, 0);
    lcd->print(" ");
    lcd->setCursor(19 - i, 1);
    lcd->print(" ");
    lcd->setCursor(i, 2);
    lcd->print(" ");
    lcd->setCursor(19 - i, 3);
    lcd->print(" ");
    delay(50);
  }
  // Off rgb
  rgbSet(0, 0, 0);
  delay(300);
  // Draw device logo
  lcd->setCursor(0, 0);
  lcd->print("LCD BAR");
  lcd->setCursor(0, 3);
  lcd->print("by @mvodya");
  // Clear screen and off
  delay(1500);
  rgbSet(0, 0, 0);
  lcd->clear();
  lcd->noBacklight();
}

// RGB Control
void LedBar::rgbSet(int r, int g, int b) {
  // Red
  analogWrite(PIN_RGB_R, r);
  // Green
  analogWrite(PIN_RGB_G, g);
  // Blue
  analogWrite(PIN_RGB_B, b);
}

// Loop tick
void LedBar::tick() {
  while (Serial.available()) {
    // Blink connect indicator
    digitalWrite(PIN_CONNECT_INDICATOR, 1);
    // Read serial string
    String command = Serial.readStringUntil(';');
    // WRite SCreen
    if (command.substring(0, 4) == "WRSC") {
      int pos = command.substring(4, 5).toInt();
      String text = command.substring(5);
      lcd->setCursor(0, pos);
      lcd->print(text);
      // Clear right space
      for (int i = 0; i < 20 - text.length(); i++) {
        lcd->print(" ");
      }
    }
    // CLear SCreen
    if (command.substring(0, 4) == "CLSC") {
      lcd->clear();
    }
    // Back Light Control oFf
    if (command.substring(0, 4) == "BLCF") {
      lcd->noBacklight();
    }
    // Back Light Control oN
    if (command.substring(0, 4) == "BLCN") {
      lcd->backlight();
    }
    // Blink connect indicator
    digitalWrite(PIN_CONNECT_INDICATOR, 0);
  }
}
