#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DS1302.h>

#include "dht.h"
#define dht_apin A0 // Humidity sensor pins = A0

dht DHT;
LiquidCrystal_I2C lcd(0x27, 16, 2); // Display pins = A4, A5
DS1302 rtc(2, 3, 4); // Time pins = 2, 3, 4

void setup() {
  rtc.halt(false);
  rtc.writeProtect(false);
  
  Serial.begin(9600);
  lcd.begin();

  // Set initial time
  rtc.setDOW(FRI);
  rtc.setTime(02, 47, 0);
  rtc.setDate(21, 12, 2019);
}

void loop() {
  
  DHT.read11(dht_apin); // Read measurements
  
  // Serial print time
  Serial.print(rtc.getDOWStr());
  Serial.print(" - ");
  Serial.print(rtc.getDateStr());
  Serial.print(" - ");
  Serial.println(rtc.getTimeStr());

  // Serial print weather
  Serial.print(DHT.temperature);
  Serial.println(DHT.humidity);

  lcd.setCursor(0,0); // Clear the screen for new information

  // Display humidity
  lcd.print("Humidity: ");
  lcd.print(round(DHT.humidity));
  lcd.print("%   ");

  lcd.setCursor(0,1); // Change line

  // Display temperature
  lcd.print("Temperature: ");
  lcd.print(round(DHT.temperature));
  lcd.print("c");
  
  delay(10000); // Add a 10 seconds delay

  lcd.setCursor(0,0); // Start at top again

  // Display date
  lcd.print(rtc.getDOWStr());
  lcd.print(" ");
  lcd.print(rtc.getDateStr());

  // Display time for 10 seconds
  for ( int i = 0; i < 10; i += 1 ) {
    
    lcd.setCursor(0,1); // Go to the bottom line
    
    lcd.print(rtc.getTimeStr());
    lcd.print("        ");
    
    delay(1000);
  }
}
