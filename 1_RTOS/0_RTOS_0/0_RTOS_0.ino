#include <Adafruit_NeoPixel.h>
#include "LiquidCrystal_I2C.h";
#include "DHT20.h"

// Define your tasks here
void TaskBlink(void* params);
void TaskRead(void* params);

//Define your components here
Adafruit_NeoPixel pixels3(4, D3, NEO_GRB + NEO_KHZ800);
LiquidCrystal_I2C lcd(0x21, 16, 2);
DHT20 dht;

void setup() {

  // Initialize serial communication at 115200 bits per second:
  Serial.begin(115200); 
  
  xTaskCreate(TaskBlink, "Task Blink", 2048, NULL, 2, NULL);
  xTaskCreate(TaskRead, "Task Read", 2048, NULL, 1, NULL);

  lcd.init();
  lcd.backlight();

  pixels3.begin();

  pinMode(A0, INPUT);
}

void loop() {
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskBlink(void* params) {
  while(1) {
    pixels3.fill(pixels3.Color(255,178,102));
    pixels3.show();
    delay(1000);
    pixels3.fill(pixels3.Color(255,102,102));
    pixels3.show();
    delay(1000);
  }
}

void TaskRead(void *params) {  
  while(1) {
    dht.read();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temp: ");
    lcd.print(dht.getTemperature());
    lcd.setCursor(0,1);
    lcd.print("Humi: ");
    lcd.print(dht.getHumidity());
    delay(1000);
  }
}