/*
* Example code shows values from SHT40 (temperature/humidity), battery voltage on eInk/ePaper display
*
* Compile as ESP32 dev module
* ESPink - ESP32 board for ePaper: https://www.laskakit.cz/laskakit-espink-esp32-e-paper-pcb-antenna/
* SHT40 (https://www.laskakit.cz/laskakit-sht40-senzor-teploty-a-vlhkosti-vzduchu/) is connected through uSup connector 
*
*
* Libraries:
* SHT40: https://github.com/adafruit/Adafruit_SHT4X
* EPD library: https://github.com/ZinggJM/GxEPD2
*
* made by laskakit (c) 2025
*/
 
#include <WiFi.h>
#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <GxEPD2_4C.h>
#include "SPI.h"
#include "Adafruit_SHT4x.h"
#include "OpenSansSB_12px.h"
#include "OpenSansSB_50px.h"
 
//#define ESPink_V2     //for version v2.6 and earlier
#define ESPink_V3     //for version v3.0 and above

#ifdef ESPink_V2
  //MOSI/SDI    23
  //CLK/SCK     18
  //SS/CS       5
  #define DC    17 
  #define RST   16  
  #define BUSY  4 
  #define POWER 2
#else ESPink_V3
  //MOSI/SDI    11
  //CLK/SCK     12
  //SS/CS       10
  #define DC    48 
  #define RST   45  
  #define BUSY  36 
  #define POWER 47
  #define SDA   42
  #define SCL   2
#endif

//GxEPD2_BW<GxEPD2_426_GDEQ0426T82, GxEPD2_426_GDEQ0426T82::HEIGHT> display(GxEPD2_426_GDEQ0426T82(SS, DC, RST, BUSY)); // GDEQ0426T82 480x800, SSD1677 (P426010-MF1-A)
//GxEPD2_4C<GxEPD2_290c_GDEY029F51H, GxEPD2_290c_GDEY029F51H::HEIGHT> display(GxEPD2_290c_GDEY029F51H(SS, DC, RST, BUSY)); // GDEY029F51H 168x384, JD79667 (FPC-H004 22.03.24)
GxEPD2_3C<GxEPD2_154_Z90c, GxEPD2_154_Z90c::HEIGHT> display(GxEPD2_154_Z90c(SS, DC, RST, BUSY)); // GDEH0154Z90 200x200, SSD1681
//GxEPD2_BW<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT> display(GxEPD2_750_T7(SS, DC, RST, BUSY)); // 7.5" b/w 800x480

// SHT40
Adafruit_SHT4x sht4 = Adafruit_SHT4x();

// ADC
float vBat = 0.0;
 
void setup() {
  Serial.begin(115200);
  pinMode(POWER, OUTPUT); 
  digitalWrite(POWER, HIGH); // enable power supply for ePaper and uSup
  delay(500);

  // read ADC and calculate the voltage
  vBat = analogReadMilliVolts(34) * 1.769 / 1000; // the ratio of divider, R2=1.3M; R1=1M


  /*----------- SHT40 -----------*/
  Wire.begin(SDA,SCL);
  if (! sht4.begin()) 
  {
    Serial.println("SHT4x not found");
    Serial.println("Check connection");
    while (1) delay(1);
  }

  sht4.setPrecision(SHT4X_HIGH_PRECISION); // the higest resolution
  sht4.setHeater(SHT4X_NO_HEATER); // no heater

  sensors_event_t humidity, temperature; // variable for humidity and temperature
  sht4.getEvent(&humidity, &temperature); // read value

  Serial.print("Temperature: "); Serial.print(temperature.temperature); Serial.println(" degrees C");
  Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.println("% rH");

  display.init(); // inicializace

  display.setRotation(3);
  display.fillScreen(GxEPD_WHITE);  // white background
  display.setTextColor(GxEPD_BLACK);  // black font

  display.setCursor(/*x*/5, /*y*/50); // set cursor
  display.setFont(&OpenSansSB_50px); // font
  display.print(String(temperature.temperature, 1)); 
  display.print("  ");
  display.print(String(humidity.relative_humidity, 0)); 

  display.setFont(&OpenSansSB_12px); // font
  display.setCursor(/*x*/30, /*y*/70); // set cursor
  display.println(" degC");
  display.setCursor(/*x*/150, /*y*/70); // set cursor
  display.println(" % Rh");

  display.setCursor(/*x*/160, /*y*/100); // set cursor
  display.print(vBat);
  display.print(" V");

  display.display(false); // update 
  delay(100);
  digitalWrite(POWER, LOW); // disable power supply for ePaper

  // deep sleep mode
  esp_sleep_enable_timer_wakeup(300 * 1000000);
  delay(200);
  esp_deep_sleep_start();
}

void loop() {}
