#include "DHTesp.h"

const int DHT_PIN = 14;  // DHT22 sensor connected to GPIO 14
const int POT_PIN = 34;   // Potentiometer connected to GPIO 34 (ADC pin)

DHTesp dhtSensor;

void setup() {
  Serial.begin(115200);
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);  // Initialize the DHT22 sensor
  pinMode(POT_PIN, INPUT);  // Set potentiometer pin as input
  delay(2000);  // Give time for the sensor to stabilize
}

void loop() {
  // Get temperature and humidity values from DHT22
  TempAndHumidity data = dhtSensor.getTempAndHumidity();
  
  // Check if data is valid
  if (isnan(data.temperature) || isnan(data.humidity)) {
    Serial.println("Failed to read from DHT sensor! Please check wiring or sensor.");
  } else {
    // Print valid temperature and humidity values
    Serial.println("Temp: " + String(data.temperature, 2) + "°C");
    Serial.println("Humidity: " + String(data.humidity, 1) + "%");
  }

  // Read the potentiometer value (0 to 4095 for ESP32)
  int potValue = analogRead(POT_PIN);
  
  // Map the potentiometer value to a wind speed (0 to 50 km/h in this example)
  float windSpeed = map(potValue, 0, 4095, 0, 50); // Max wind speed of 50 km/h

  // Print wind speed
  Serial.println("Wind Speed: " + String(windSpeed) + " km/h");

  Serial.println("---");
  delay(2000);  // Wait for 2 seconds before the next reading
}
