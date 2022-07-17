/*
* Example code shows values from SHT40 (temperature/humidity), battery voltage on eInk/ePaper display
*
* Compile as ESP32 dev module
* ESPink - ESP32 board for ePaper: https://www.laskakit.cz/laskakit-espink-esp32-e-paper-pcb-antenna/
* SHT40 (https://www.laskakit.cz/laskakit-sht40-senzor-teploty-a-vlhkosti-vzduchu/) is connected through uSup connector 
*
*
* -------- ESPink pinout -------
* MOSI/SDI 23
* CLK/SCK 18
* SS 5 //CS
* DC 17 
* RST 16  
* BUSY 4 
* -------------------------------
*
* Libraries:
* Analog read with calibration data: https://github.com/madhephaestus/ESP32AnalogRead/ 
* SHT40: https://github.com/adafruit/Adafruit_SHT4X
* EPD library: https://github.com/ZinggJM/GxEPD2
*
* made by laskakit (c) 2022
*/
 
#include <WiFi.h>
#include <GxEPD2_BW.h>
#include "SPI.h"

// SHT40
#include "Adafruit_SHT4x.h"

// ADC reading
#include <ESP32AnalogRead.h>
 
// Fonts
#include "OpenSansSB_12px.h"
#include "OpenSansSB_50px.h"
 
/*----------------- Pinout of ESPink -------------*/
// MOSI/SDI 23
// CLK/SCK 18
// CS 5
#define SS 5 //SS
#define DC 17 // D/C
#define RST 16  // RES
#define BUSY 4  //BUSY
/* ---------------------------------------------- */

/*------------------------  Define EPD driver - uncomment the used one  -----------------------------*/
//GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT> display(GxEPD2_154_D67(/*CS*/ SS, /*DC*/ DC, /*RST*/ RST, /*BUSY*/ BUSY)); // 1.54" b/w
//GxEPD2_BW<GxEPD2_154_M10, GxEPD2_154_M10::HEIGHT> display(GxEPD2_154_M10(/*CS*/ SS, /*DC*/ DC, /*RST*/ RST, /*BUSY*/ BUSY)); // 1.54" b/w DES
//GxEPD2_BW<GxEPD2_213_B74, GxEPD2_213_B74::HEIGHT> display(GxEPD2_213_B74(/*CS*/ SS, /*DC*/ DC, /*RST*/ RST, /*BUSY*/ BUSY)); // 2.13" b/w
//GxEPD2_BW<GxEPD2_213_M21, GxEPD2_213_M21::HEIGHT> display(GxEPD2_213_M21(/*CS*/ SS, /*DC*/ DC, /*RST*/ RST, /*BUSY*/ BUSY)); // 2.13" b/w DES
GxEPD2_BW<GxEPD2_420, GxEPD2_420::HEIGHT> display(GxEPD2_420(/*CS*/ SS, /*DC*/ DC, /*RST*/ RST, /*BUSY*/ BUSY)); // 4.2" b/w
//GxEPD2_BW<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT> display(GxEPD2_750_T7(/*CS*/ SS, /*DC*/ DC, /*RST*/ RST, /*BUSY*/ BUSY)); // 7.5" b/w 800x480
/*  ------------------------------------------------------------------------------------------------- */
// Note: all supported ePapers you can find on https://github.com/ZinggJM/GxEPD2

// SHT40
Adafruit_SHT4x sht4 = Adafruit_SHT4x();

// ADC
ESP32AnalogRead adc;
float vBat = 0.0;
 
void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT); 
  digitalWrite(2, HIGH); // enable power supply for ePaper
  delay(500);

  // attach ADC input
  adc.attach(34);

  // read ADC and calculate the voltage
  vBat = adc.readVoltage()*1.3; // the ratio of divider, R2=330k; R1=100k


  /*----------- SHT40 -----------*/
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

  display.init();

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
  digitalWrite(2, LOW); // disable power supply for ePaper

  // deep sleep mode
  esp_sleep_enable_timer_wakeup(300 * 1000000);
  delay(200);
  esp_deep_sleep_start();
}

void loop() {

}
