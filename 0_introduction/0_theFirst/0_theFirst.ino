void setup() {
    Serial.begin(115200);

    pinMode(A0, INPUT);
}

void loop() {
    int sensorValue = analogRead(A0);

    Serial.print("Light: ");
    Serial.println(sensorValue);

    delay(1000);
}