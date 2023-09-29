#include "BME280.h"

BME280 bme;

void setup() {
  Serial.begin(9600);
  if (!bme.initialize()) {
    Serial.println("Could not find BME280 sensor!");
    while (1);
  }
}

void loop() {
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature() / 100.0);
  Serial.println(" *C");

  // Similar print statements for Pressure and Humidity
  
  delay(2000);
}
