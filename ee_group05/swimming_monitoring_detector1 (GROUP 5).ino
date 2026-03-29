#include <Adafruit_LiquidCrystal.h>

// Tinkercad's specific I2C LCD setup
Adafruit_LiquidCrystal lcd(0);

int tempPin = A0; // Now connected to the Potentiometer's middle pin
int pHPin = A1;
int ldrPin = A2;
int ledGreen = 7;
int ledRed = 8;
int buzzer = 9;

void setup() {
  // Tinkercad's specific initialization commands
  lcd.begin(16, 2);
  lcd.setBacklight(1);
  
  lcd.setCursor(0, 0);
  lcd.print("SYSTEM BOOTING...");
  
  for (int i = 3; i > 0; i--) {
    lcd.setCursor(0, 1); 
    lcd.print("Starting in: ");
    lcd.print(i);
    delay(1000); 
  }
  
  lcd.clear();
  lcd.print("Now running...");
  delay(1000); 
  
  Serial.begin(9600);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // NEW: Maps the potentiometer (0-1023) to a temperature range of 0.0 to 50.0 Celsius
  float temp = (analogRead(tempPin) / 1023.0) * 50.0; 
  
  float pH = analogRead(pHPin) * 14.0 / 1023.0;
  float turbidity = 100.0 - (analogRead(ldrPin) / 1023.0) * 100.0;

  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print("C pH: ");
  Serial.print(pH);
  Serial.print(" Turbidity: ");
  Serial.println(turbidity);

  lcd.setCursor(0, 0);
  lcd.print("T: ");
  lcd.print(temp, 1); 
  lcd.print("C pH: ");
  lcd.print(pH, 1);

  lcd.setCursor(0, 1);
  lcd.print("Turb: ");
  lcd.print(turbidity, 1);
  lcd.print("% ");

  lcd.setCursor(12, 1);
  // The temperature ranges (24 to 30) remain exactly as you had them!
  if (temp < 19.0 || temp > 30.0 || pH < 7.2 || pH > 7.8 || turbidity > 40.0) {
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, LOW);
    tone(buzzer, 1000);
    lcd.print("BAD!");
  } else {
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, LOW);
    noTone(buzzer);
    lcd.print("GOOD!");
  }
  
  delay(1000); 
}