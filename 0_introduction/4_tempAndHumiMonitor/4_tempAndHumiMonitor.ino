#include "LiquidCrystal_I2C.h";
#include "DHT20.h"

#include <Arduino.h>

LiquidCrystal_I2C lcd(0x21, 16, 2);
DHT20 DHT;

void setup() {
  lcd.init();

  lcd.backlight();
}

void loop() {
  DHT.read();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print((DHT.getTemperature()));
  lcd.setCursor(0, 1);
  lcd.print("Humi: ");
  lcd.print((DHT.getHumidity()));
  delay(5000);
}