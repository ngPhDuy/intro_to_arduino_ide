void setup() {
  pinMode(D5, OUTPUT);
}

void loop() {
  for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle++) {
    analogWrite(D5, dutyCycle); 
    delay(10); 
}

  for (int dutyCycle = 255; dutyCycle >= 0; dutyCycle--) {
    analogWrite(D5, dutyCycle);
    delay(10);
  }
}