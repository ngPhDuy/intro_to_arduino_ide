#include <Arduino.h>
#include "LiquidCrystal_I2C.h";
#include <Adafruit_NeoPixel.h>

LiquidCrystal_I2C lcd(0x21, 16, 2);
Adafruit_NeoPixel rgb(4, D3, NEO_GRB + NEO_KHZ800);

void setup() {
  lcd.init();
  lcd.backlight();

  rgb.begin();

  pinMode(A0, INPUT);
}

void loop() {
  int sensorVal = analogRead(A0);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SensorVal: ");
  lcd.print(sensorVal);
  lcd.setCursor(0, 1);

  if (sensorVal > 1000) {
    lcd.print("LED OFF");
    rgb.fill(rgb.Color(0,0,0));
  } else {
    lcd.print("LED ON");
    rgb.fill(rgb.Color(255,153,51));
  }
  rgb.show();

  delay(1000);
}
