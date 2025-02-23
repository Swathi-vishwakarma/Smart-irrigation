#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>

// Pin Definitions
const int soilMoisturePin = A0;    // Soil moisture sensor
const int pumpRelayPin = 7;        // Relay control for water pump
const int buzzerPin = 8;           // Buzzer for alarm
const int wateringDuration = 5000; // Water pump run time in milliseconds (5 seconds)

// Threshold value to trigger irrigation
const int moistureThreshold = 400;

// RTC Module
RTC_DS3231 rtc;

// LCD Display (16x2)
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address of LCD is 0x27

// Variables
int soilMoistureLevel = 0;
unsigned long lastWateredTime = 0;
bool watering = false;

void setup() {
  // Initialize Serial Monitor for debugging
  Serial.begin(9600);
  
  // Initialize RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  // Initialize LCD
  lcd.begin(16, 2);
  lcd.print("Irrigation System");
  delay(2000);
  
  // Initialize pins
  pinMode(pumpRelayPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(pumpRelayPin, LOW);  // Initially pump off
  
  // Display initial status
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Soil Moisture:");
  lcd.setCursor(0, 1);
  lcd.print("Pump OFF");
}

void loop() {
  // Get current time from RTC
  DateTime now = rtc.now();
  
  // Read soil moisture level
  soilMoistureLevel = analogRead(soilMoisturePin);
  
  // Display soil moisture on LCD
  lcd.setCursor(0, 1);
  lcd.print("Moisture: ");
  lcd.print(soilMoistureLevel);
  
  // Check if watering is needed
  if (soilMoistureLevel < moistureThreshold) {
    if (!watering) {
      // Start watering if soil is dry
      digitalWrite(pumpRelayPin, HIGH);  // Turn on pump
      lcd.setCursor(0, 1);
      lcd.print("Pump ON ");
      Serial.println("Soil is dry, starting irrigation...");
      lastWateredTime = millis();  // Record the time watering started
      watering = true;
    }
  }
  
  // Check if watering duration has passed
  if (watering && millis() - lastWateredTime > wateringDuration) {
    digitalWrite(pumpRelayPin, LOW);  // Turn off pump
    lcd.setCursor(0, 1);
    lcd.print("Pump OFF ");
    Serial.println("Watering completed.");
    watering = false;
  }
  
  // Schedule irrigation between 6 AM and 8 AM only
  if (now.hour() >= 6 && now.hour() < 8) {
    // If it's scheduled watering time, check soil moisture
    if (soilMoistureLevel < moistureThreshold) {
      // Start watering if soil is dry
      digitalWrite(pumpRelayPin, HIGH);
      lcd.setCursor(0, 1);
      lcd.print("Pump ON ");
      delay(wateringDuration);  // Run for specific duration
      digitalWrite(pumpRelayPin, LOW);
      lcd.setCursor(0, 1);
      lcd.print("Pump OFF ");
    }
  }

  // If the soil moisture remains dry for too long, activate buzzer
  if (soilMoistureLevel < moistureThreshold && millis() - lastWateredTime > 10000) { // 10 seconds
    tone(buzzerPin, 1000);  // Turn on buzzer
    lcd.setCursor(0, 1);
    lcd.print("ALERT: Dry soil");
    Serial.println("Soil is dry for too long, ALERT!");
  } else {
    noTone(buzzerPin);  // Turn off buzzer
  }

  // Delay before next loop iteration
  delay(1000);
}
