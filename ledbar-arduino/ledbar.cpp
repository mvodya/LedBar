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
      delay(50);
    }
  }
  // Off rgb
  rgbSet(0, 0, 0);
  delay(1000);
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
    delay(100);
  }
  // Off rgb
  rgbSet(0, 0, 0);
  delay(300);
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
    rgbSet(0, 0, 0);
    delay(300);
    lcd->print(".");
    rgbSet(50, 0, 0);
    delay(300);
    lcd->print(".");
    rgbSet(100, 0, 0);
    delay(300);
    lcd->print(".");
    rgbSet(255, 0, 0);
    delay(100);
  }
  // Connected
  lcd->setCursor(0, 1);
  lcd->print("connected!         ");
  rgbSet(0, 255, 0);
  delay(1000);
  rgbSet(0, 0, 0);
  lcd->clear();
}

// On connection wait
bool LedBar::connectWait() {
  if (Serial.readString() == "TRY_CONN")
    return true;
  else
    return false;
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
    String command = Serial.readStringUntil(';');
    // WRite SCreen
    if (command.substring(0, 4) == "WRSC") {
      int pos = command.substring(4,5).toInt();
      String text = command.substring(5);
      lcd->setCursor(0, pos);
      lcd->print(text);
    }
    // CLear SCreen
    if (command.substring(0, 4) == "CLSC") {
      lcd->clear();
    }
  }
}
