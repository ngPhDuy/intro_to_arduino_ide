#include "LiquidCrystal_I2C.h";
#include <Arduino.h>

LiquidCrystal_I2C lcd(0x21,16,2);

void setup() {
  lcd.init();

  lcd.backlight();
}

void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hello World!");
  lcd.setCursor(0, 1);
  lcd.print("06/07/2024");
  delay(5000);
}