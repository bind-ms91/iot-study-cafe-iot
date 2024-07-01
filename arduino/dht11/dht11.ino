#include "DHT.h"

int serialBaudRate = 9600;
int vccPin = 2;
int dhtPin = 3;
int gndPin = 4;
int dhtType = DHT11;

DHT dht(dhtPin, dhtType);

void setup() {
  Serial.begin(serialBaudRate);
  
  pinMode(vccPin, OUTPUT);
  pinMode(gndPin, OUTPUT);
  digitalWrite(vccPin, HIGH);
  digitalWrite(gndPin, LOW);

  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    return;
  }

  // message : {"temperature":value,"humidity":value}\n
  Serial.print(F("{\"temperature\":"));
  Serial.print(t);
  Serial.print(F(",\"humidity\":"));
  Serial.print(h);
  Serial.print(F("}"));
  Serial.println();
}
