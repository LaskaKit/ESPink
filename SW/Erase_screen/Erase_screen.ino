/*
* Example code shows values from SHT40 (temperature/humidity), battery voltage on eInk/ePaper display
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
* EPD library: https://github.com/ZinggJM/GxEPD2
*
* made by laskakit (c) 2024
*/
 
#include <WiFi.h>
#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include "SPI.h"
// Fonts
#include "OpenSansSB_12px.h"
#include "OpenSansSB_50px.h"

/*------------------------  Define EPD driver - uncomment the used one  -----------------------------*/
//GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT> display(GxEPD2_154_D67(/*CS*/ SS, /*DC*/ DC, /*RST*/ RST, /*BUSY*/ BUSY)); // 1.54" b/w
//GxEPD2_BW<GxEPD2_154_M10, GxEPD2_154_M10::HEIGHT> display(GxEPD2_154_M10(/*CS*/ SS, /*DC*/ DC, /*RST*/ RST, /*BUSY*/ BUSY)); // 1.54" b/w DES
//GxEPD2_BW<GxEPD2_213_B74, GxEPD2_213_B74::HEIGHT> display(GxEPD2_213_B74(/*CS*/ SS, /*DC*/ DC, /*RST*/ RST, /*BUSY*/ BUSY)); // 2.13" b/w
//GxEPD2_BW<GxEPD2_213_M21, GxEPD2_213_M21::HEIGHT> display(GxEPD2_213_M21(/*CS*/ SS, /*DC*/ DC, /*RST*/ RST, /*BUSY*/ BUSY)); // 2.13" b/w DES
//GxEPD2_BW<GxEPD2_270, GxEPD2_270::HEIGHT> display(GxEPD2_270(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4)); // GDEW027W3 176x264, EK79652 (IL91874)
//GxEPD2_BW<GxEPD2_420_GDEY042T81, GxEPD2_420_GDEY042T81::HEIGHT> display(GxEPD2_420_GDEY042T81(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4)); // GDEY042T81, 400x300, SSD1683 (no inking)
GxEPD2_3C<GxEPD2_420c_Z21, GxEPD2_420c_Z21::HEIGHT> display(GxEPD2_420c_Z21(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4)); // GDEQ042Z21 400x300, UC8276
//GxEPD2_BW<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT> display(GxEPD2_750_T7(/*CS*/ SS, /*DC*/ DC, /*RST*/ RST, /*BUSY*/ BUSY)); // 7.5" b/w 800x480
/*  ------------------------------------------------------------------------------------------------- */
// Note: all supported ePapers you can find on https://github.com/ZinggJM/GxEPD2

void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT); 
  digitalWrite(2, HIGH); // enable power supply for ePaper and uSup
  delay(500);

  display.init(); // inicializace
  display.fillScreen(GxEPD_WHITE);  // white background
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
