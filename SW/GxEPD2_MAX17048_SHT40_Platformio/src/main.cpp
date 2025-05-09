/* Display test for LaskaKit ESPink ESP32 e-Paper board V3 and newest 
 * example from GxEPD2, SparkFun_MAX1704x and Adafruit_SHT4x library is used
 * 
 * Board:   LaskaKit ESPink ESP32 e-Paper   https://www.laskakit.cz/laskakit-espink-esp32-e-paper-pcb-antenna/
 * Display: Good Display GDEY075T7          https://www.laskakit.cz/good-display-gdey075t7-7-5--800x480-epaper-displej-grayscale/
 * 
 * Email:podpora@laskakit.cz
 * Web:laskakit.cz
 */

// Display Library example for SPI e-paper panels from Dalian Good Display.
// Requires Adafruit_GFX and https://github.com/ZinggJM/GxEPD2 Author: Jean-Marc Zingg

#define ENABLE_GxEPD2_GFX 0

#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <GxEPD2_4C.h>
#include "Adafruit_SHT4x.h"
#include <SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library.h>
#include <Fonts/FreeMonoBold9pt7b.h>

#define SLEEP_SEC 300         // Measurement interval (seconds)
//MOSI/SDI    11
//CLK/SCK     12
//SS/CS       10
#define DC    48 
#define RST   45  
#define BUSY  36 
#define POWER 47
#define ALERT 9
#define SDA   42
#define SCL   2

float temp;
float hum;
float volt;
float percent;
float disrate;

SFE_MAX1704X lipo(MAX1704X_MAX17048); // Create a MAX17048
Adafruit_SHT4x sht4 = Adafruit_SHT4x();

GxEPD2_3C<GxEPD2_154_Z90c, GxEPD2_154_Z90c::HEIGHT> display(GxEPD2_154_Z90c(SS, DC, RST, BUSY)); // GDEH0154Z90 200x200, SSD1681
//GxEPD2_4C<GxEPD2_290c_GDEY029F51H, GxEPD2_290c_GDEY029F51H::HEIGHT> display(GxEPD2_290c_GDEY029F51H(SS, DC, RST, BUSY)); // GDEY029F51H 168x384, JD79667 (FPC-H004 22.03.24)
//GxEPD2_BW<GxEPD2_426_GDEQ0426T82, GxEPD2_426_GDEQ0426T82::HEIGHT> display(GxEPD2_426_GDEQ0426T82(SS, DC, RST, BUSY)); // GDEQ0426T82 480x800, SSD1677 (P426010-MF1-A)
//GxEPD2_BW<GxEPD2_750_GDEY075T7, GxEPD2_750_GDEY075T7::HEIGHT> display(GxEPD2_750_GDEY075T7(SS, DC, RST, BUSY)); // GDEY075T7 800x480, UC8179 (GD7965)


void setEPaperPowerOn(bool on) {
  digitalWrite(POWER, on ? HIGH : LOW);
}

void goToSleep(){
  Serial.println("going to sleep " + String(SLEEP_SEC) + " sek");

  // ESP Deep Sleep 
  setEPaperPowerOn(false);
  Serial.println("Display power OFF");
  Serial.println("ESP in sleep mode");
  Serial.flush(); 
  esp_sleep_enable_timer_wakeup(SLEEP_SEC * 1000000);
  esp_deep_sleep_start();
}

void readBattery() {

  Serial.println("Reading battery on ESPink V3 board");

  lipo.begin();

  lipo.enableDebugging(); // Uncomment this line to enable helpful debug messages on Serial

  // Read and print the reset indicator
  Serial.print(F("Reset Indicator was: "));
  bool RI = lipo.isReset(true); // Read the RI flag and clear it automatically if it is set
  Serial.println(RI); // Print the RI
  // If RI was set, check it is now clear
  if (RI)   {
    Serial.print(F("Reset Indicator is now: "));
    RI = lipo.isReset(); // Read the RI flag
    Serial.println(RI); // Print the RI    
  }

  lipo.setThreshold(1); // Set alert threshold to just 1% - we don't want to trigger the alert
  lipo.setVALRTMax((float)4.3); // Set high voltage threshold (Volts)
  lipo.setVALRTMin((float)2.9); // Set low voltage threshold (Volts)

  // Read the variables:
  volt = lipo.getVoltage();
  percent = lipo.getSOC();
  disrate = lipo.getChangeRate();

  lipo.clearAlert();
  // Fuel Gauge Deep Sleep 
  Serial.print("enableHibernate (Output: 0 on success, positive integer on fail): ");
  Serial.println(lipo.enableHibernate()); // Put the MAX17048 into hibernate mode
 
  // Print the variables:
  Serial.print("Voltage: ");
  Serial.print(volt);  // Print the battery voltage
  Serial.print("V");

  Serial.print(" Percentage: ");
  Serial.print(percent, 2); // Print the battery state of charge with 2 decimal places
  Serial.print("%");

  Serial.print(" Change Rate: ");
  Serial.print(disrate, 2); // Print the battery change rate with 2 decimal places
  Serial.print("%/hr");
  
  Serial.println();
}

void readSensor() {

  if (! sht4.begin()) 
  {
    Serial.println("SHT4x not found");
    Serial.println("Check connection");
    while (1) delay(1);
  }
  sht4.setPrecision(SHT4X_LOW_PRECISION); // the higest resolution
  sht4.setHeater(SHT4X_NO_HEATER); // no heater

  sensors_event_t humidity, temperature; // variable for humidity and temperature
  sht4.getEvent(&humidity, &temperature); // read value

  // Read variables
  temp = temperature.temperature;
  hum = humidity.relative_humidity;

  Serial.print("Temperature: "); Serial.print(temp); Serial.println(" degrees C");
  Serial.print("Humidity: "); Serial.print(hum); Serial.println("% rH");
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("setup");

  pinMode(POWER, OUTPUT);
  pinMode(ALERT, INPUT_PULLUP);

  setEPaperPowerOn(true);
  Wire.begin (SDA, SCL);

  readBattery();
  readSensor();

  display.init(); // inicializace displeje
  display.setRotation(0);
  display.setFont(&FreeMonoBold9pt7b);
  if (display.epd2.WIDTH < 104) display.setFont(0);
  display.setTextColor(GxEPD_BLACK);
  display.fillScreen(GxEPD_WHITE);

  display.setCursor(5, 10);
  display.print("Bat Voltage: ");
  display.setCursor(5, 50);
  display.print("Bat Percentage: ");
  display.setCursor(5, 90);
  display.print("(Dis)Charge Rate: ");
  display.setCursor(5, 130);
  display.print("Temperature: ");
  display.setCursor(5, 170);
  display.print("Humidity: ");
  
  display.setTextColor(display.epd2.hasColor ? GxEPD_RED : GxEPD_BLACK);
  display.setCursor(60, 30);
  display.print(String(volt) + "V");
  display.setCursor(60, 70);
  display.print(String(percent) + "%");
  display.setCursor(60, 110);
  display.print(String(disrate, 2) + "%/hr");
  display.setCursor(60, 150);
  display.print(String(temp, 2) + "˚C");
  display.setCursor(60, 190);
  display.print(String(hum, 2) + "%");

  display.display(false); // update 
  display.powerOff();

  goToSleep();
}
void loop() {}