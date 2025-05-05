/*
* Example code for display erasing
*
* Board:   LaskaKit ESPink ESP32 e-Paper   https://www.laskakit.cz/laskakit-espink-esp32-e-paper-pcb-antenna/
* Libraries:
* EPD library: https://github.com/ZinggJM/GxEPD2
*
* made by laskakit (c) 2024
*/
 
#include <WiFi.h>
#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <GxEPD2_4C.h>
#include <GxEPD2_7C.h>
#include "SPI.h"


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
  #define CS2   35 // For GDEM1085T51 Only
  #define DC    48 
  #define RST   45  
  #define BUSY  36 
  #define POWER 47
#endif


/*------------------------  Define EPD driver - uncomment the used one  -----------------------------*/

//BW
//GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT> display(GxEPD2_154_D67(SS, DC, RST, BUSY)); // 1.54" b/w
//GxEPD2_BW<GxEPD2_154_M10, GxEPD2_154_M10::HEIGHT> display(GxEPD2_154_M10(SS, DC, RST, BUSY)); // 1.54" b/w DES
//GxEPD2_BW<GxEPD2_213_B74, GxEPD2_213_B74::HEIGHT> display(GxEPD2_213_B74(SS, DC, RST, BUSY)); // 2.13" b/w
//GxEPD2_BW<GxEPD2_213_M21, GxEPD2_213_M21::HEIGHT> display(GxEPD2_213_M21(SS, DC, RST, BUSY)); // 2.13" b/w DES
//GxEPD2_BW<GxEPD2_270, GxEPD2_270::HEIGHT> display(GxEPD2_270(SS, DC, RST, BUSY)); // GDEW027W3 176x264, EK79652 (IL91874)
//GxEPD2_BW<GxEPD2_290_GDEY029T71H, GxEPD2_290_GDEY029T71H::HEIGHT> display(GxEPD2_290_GDEY029T71H(SS, DC, RST, BUSY)); // GDEY029T71H 168x384, SSD1685, (FPC-H004 22.03.24)
//GxEPD2_BW<GxEPD2_420_GDEY042T81, GxEPD2_420_GDEY042T81::HEIGHT> display(GxEPD2_420_GDEY042T81(SS, DC, RST, BUSY)); // GDEY042T81, 400x300, SSD1683 (no inking)
//GxEPD2_BW<GxEPD2_426_GDEQ0426T82, GxEPD2_426_GDEQ0426T82::HEIGHT> display(GxEPD2_426_GDEQ0426T82(SS, DC, RST, BUSY)); // GDEQ0426T82 480x800, SSD1677 (P426010-MF1-A)
GxEPD2_BW<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT> display(GxEPD2_750_T7(SS, DC, RST, BUSY)); // 7.5" b/w 800x480
//GxEPD2_BW < GxEPD2_1020_GDEM102T91, GxEPD2_1020_GDEM102T91::HEIGHT / 2> display(GxEPD2_1020_GDEM102T91(SS, DC, RST, BUSY)); // GDEM102T91 960x640, SSD1677, (FPC7705 REV.b)
//GxEPD2_BW < GxEPD2_1085_GDEM1085T51, GxEPD2_1085_GDEM1085T51::HEIGHT / 2> display(GxEPD2_1085_GDEM1085T51(SS, DC, RST, BUSY, CS2)); // GDEM1085T51 1360x480, JD79686AB, (FPC8617)
//GxEPD2_BW < GxEPD2_1330_GDEM133T91, GxEPD2_1330_GDEM133T91::HEIGHT / 2> display(GxEPD2_1330_GDEM133T91(SS, DC, RST, BUSY)); // GDEM133T91 960x680, SSD1677, (FPC-7701 REV.B)

// 3 Color
//GxEPD2_3C<GxEPD2_154_Z90c, GxEPD2_154_Z90c::HEIGHT> display(GxEPD2_154_Z90c(SS, DC, RST, BUSY)); // GDEH0154Z90 200x200, SSD1681
//GxEPD2_3C<GxEPD2_420c_Z21, GxEPD2_420c_Z21::HEIGHT> display(GxEPD2_420c_Z21(SS, DC, RST, BUSY)); // GDEQ042Z21 400x300, UC8276GxEPD2_3C<GxEPD2_420c_GDEY042Z98, GxEPD2_420c_GDEY042Z98::HEIGHT> display(GxEPD2_420c_GDEY042Z98(SS, DC, RST, BUSY)); // GDEY042Z98 400x300, SSD1683 (no inking)
//GxEPD2_3C<GxEPD2_583c_GDEQ0583Z31, GxEPD2_583c_GDEQ0583Z31::HEIGHT / 2> display(GxEPD2_583c_GDEQ0583Z31(SS, DC, RST, BUSY)); // GDEQ0583Z31 648x480, UC8179C
//GxEPD2_3C<GxEPD2_750c_Z08, GxEPD2_750c_Z08::HEIGHT> display(GxEPD2_750c_Z08(SS, DC, RST, BUSY)); // GDEW075Z08 800x480, GD7965
//GxEPD2_3C<GxEPD2_1160c_GDEY116Z91, GxEPD2_1160c_GDEY116Z91::HEIGHT / 2> display(GxEPD2_1160c_GDEY116Z91(SS, DC, RST, BUSY)); // GDEY116Z91 960x640, SSD1677
//GxEPD2_3C<GxEPD2_1330c_GDEM133Z91, GxEPD2_1330c_GDEM133Z91::HEIGHT / 4> display(GxEPD2_1330c_GDEM133Z91(SS, DC, RST, BUSY)); // GDEM133Z91 960x680, SSD1677
//GxEPD2_3C<GxEPD2_1248c, GxEPD2_1248c::HEIGHT / 4> display(GxEPD2_1248c(/*sck=*/ 12, /*miso=*/ -1, /*mosi=*/ 11, /*cs_m1=*/ 10, /*cs_s1=*/ 18, /*cs_m2=*/ 48, /*cs_s2=*/ 41, /*dc1=*/ 46, /*dc2=*/ 45, /*rst1=*/ 3, /*rst2=*/ 39, /*busy_m1=*/ 8, /*busy_s1=*/ 17, /*busy_m2=*/ 40, /*busy_s2=*/ 16)); // GDEY1248Z51 - 3C, 1304x984px, 12.48"
// 4 Color
//GxEPD2_4C<GxEPD2_213c_GDEY0213F51, GxEPD2_213c_GDEY0213F51::HEIGHT> display(GxEPD2_213c_GDEY0213F51(SS, DC, RST, BUSY)); // GDEY0213F51 122x250, JD79661 (FPC-A002 20.04.08)
//GxEPD2_4C<GxEPD2_290c_GDEY029F51H, GxEPD2_290c_GDEY029F51H::HEIGHT> display(GxEPD2_290c_GDEY029F51H(SS, DC, RST, BUSY)); // GDEY029F51H 168x384, JD79667 (FPC-H004 22.03.24)
//GxEPD2_4C<GxEPD2_1160c_GDEY116F51, GxEPD2_1160c_GDEY116F51::HEIGHT / 2> display(GxEPD2_1160c_GDEY116F51(SS, DC, RST, BUSY)); // GDEY116F51 960x640, SSD2677, (FPC-K012 23.09.27)

// 7 Color
//GxEPD2_7C < GxEPD2_565c_GDEP0565D90, GxEPD2_565c_GDEP0565D90::HEIGHT / 2 > display(GxEPD2_565c_GDEP0565D90(SS, DC, RST, BUSY)); // DIP: 1-ON, 2-OFF: GDEP0565D90 600x448 7-color (E219454, AB1024-EGA AC0750TC1)

/*  ------------------------------------------------------------------------------------------------- */
// Note: all supported ePapers you can find on https://github.com/ZinggJM/GxEPD2

void setup() {
  Serial.begin(115200);
  pinMode(POWER, OUTPUT); 
  digitalWrite(POWER, HIGH); // enable power supply for ePaper and uSup
  delay(500);

  display.init(); // inicializace
  display.fillScreen(GxEPD_WHITE);  // white background
  display.display(false); // update 

  delay(100);
  digitalWrite(POWER, LOW); // disable power supply for ePaper

  // deep sleep mode
  esp_sleep_enable_timer_wakeup(300 * 1000000);
  delay(200);
  esp_deep_sleep_start();
}

void loop() {

}
