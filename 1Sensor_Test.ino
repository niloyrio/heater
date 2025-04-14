#include "max6675.h"

// MAX6675 pins
int thermoDO = 19;
int thermoCS = 5;
int thermoCLK = 18;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

// TRIAC control
int triacPin = 25;

// Set temperature in Celsius
float setTemp = 100.0;

// State tracking
bool heaterOn = false;

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("Heater Control with ±5°C Hysteresis");

  pinMode(triacPin, OUTPUT);
  digitalWrite(triacPin, LOW); // Heater OFF
}

void loop() {
  float currentTemp = thermocouple.readCelsius();

  // Hysteresis control: ±5°C
  if (!heaterOn && currentTemp < (setTemp - 5)) {
    digitalWrite(triacPin, HIGH); // Turn ON heater
    heaterOn = true;
  } else if (heaterOn && currentTemp > (setTemp + 5)) {
    digitalWrite(triacPin, LOW); // Turn OFF heater
    heaterOn = false;
  }

  // Print info
  Serial.print("Current Temp: ");
  Serial.print(currentTemp);
  Serial.print(" °C | Set Temp: ");
  Serial.print(setTemp);
  Serial.print(" °C | Heater: ");
  Serial.println(heaterOn ? "ON" : "OFF");

  delay(1000);
}
