/*
* This example code is used for LaskaKit ESPink V3 board  https://www.laskakit.cz/laskakit-espink-esp32-e-paper-pcb-antenna/?variantId=12416
*
* Board reads voltage on Battery  
* and sends every 2 seconds through UART
*
* Made by (c) laskakit.cz 2024
* 
*/

#include <SPI.h>
#include <Wire.h>
#include <ESP32AnalogRead.h>    // https://github.com/madhephaestus/ESP32AnalogRead

ESP32AnalogRead adcB;
#define ADCBpin   9
#define POWERpin  47
#define bDeviderRatio 1.7693877551  // Voltage devider ratio on ADC pin 1MOhm + 1.3MOhm

void setup() {
    
  Serial.begin(115200);
  delay(100); // let serial console settle

  pinMode(POWERpin, OUTPUT); 
  digitalWrite(POWERpin, HIGH); // enable power supply for ePaper and uSup

  // setting ADC
  adcB.attach(ADCBpin);
}

void loop() {

  float bat_voltage = adcB.readVoltage() * bDeviderRatio;
  Serial.print("Battery Voltage = " );
  Serial.print(bat_voltage);
  Serial.println("V");

  delay(2000);
}
