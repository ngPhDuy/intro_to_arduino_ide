#include <Adafruit_NeoPixel.h>
#include "LiquidCrystal_I2C.h";
#include "DHT20.h"

// Define your tasks here
void TaskBlink(void* params);
void TaskReadTemperatureAndHumidity(void* params);
void TaskAutoRelay(void* params);
void TaskAutoLed(void* params);

//Define your components here
Adafruit_NeoPixel pixels3(4, D7, NEO_GRB + NEO_KHZ800);
LiquidCrystal_I2C lcd(0x21, 16, 2);
DHT20 dht;

void setup() {

  // Initialize serial communication at 115200 bits per second:
  Serial.begin(115200); 
  
  xTaskCreate( TaskBlink, "Task Blink" ,2048  ,NULL  ,2 , NULL);
  xTaskCreate( TaskReadTemperatureAndHumidity, "Task Read Temp And Humi" ,2048  ,NULL  ,2 , NULL);
  xTaskCreate( TaskAutoRelay, "Task Auto Relay" ,2048  ,NULL  ,2 , NULL);
  xTaskCreate( TaskAutoLed, "Task Auto Led" ,2048  ,NULL  ,2 , NULL);
  //Now the task scheduler is automatically started.
  Serial.printf("Basic Multi Threading Arduino Example\n");

  lcd.init();
  lcd.backlight();
}

void loop() {
}
/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/
void TaskBlink(void *pvParameters) {  // This is a task.
  pinMode(LED_BUILTIN, OUTPUT);
  
  while(1) {                          
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED ON
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);  // turn the LED OFF
    delay(200);
  }
}


void TaskReadTemperatureAndHumidity(void* params){  // This is a task.
  while(1) {                          
    Serial.println("Task Read Temperature and Humidity");
    dht.read();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temp: ");
    lcd.print(dht.getTemperature());
    lcd.setCursor(0,1);
    lcd.print("Humi: ");
    lcd.print(dht.getHumidity());
    delay(5000);
  }
}

void TaskAutoRelay(void* params) {
  pinMode(D9, OUTPUT);

  while(1) {
    Serial.println("Task Auto Relay: " + analogRead(A3));
  
    if (analogRead(A3) > 500) {
      digitalWrite(D9, LOW);
    }

    if (analogRead(A3) < 50) {
      digitalWrite(D9, HIGH);
    }

    delay(1000);
  }
}

void TaskAutoLed(void* params) {
  pinMode(A0, INPUT);

  while(1) {
    Serial.println("Task Auto Led");

    int sensorValue = analogRead(A0);
    if (sensorValue > 1000) {
      pixels3.setPixelColor(0, pixels3.Color(0,0,0));
      pixels3.setPixelColor(1, pixels3.Color(0,0,0));
      pixels3.setPixelColor(2, pixels3.Color(0,0,0));
      pixels3.setPixelColor(3, pixels3.Color(0,0,0));
      pixels3.show();
    }
    if (sensorValue < 999) {
      pixels3.setPixelColor(0, pixels3.Color(255,255,255));
      pixels3.setPixelColor(1, pixels3.Color(255,255,255));
      pixels3.setPixelColor(2, pixels3.Color(255,255,255));
      pixels3.setPixelColor(3, pixels3.Color(255,255,255)); 
      pixels3.show();    
    }

    delay(1000);
  }
}