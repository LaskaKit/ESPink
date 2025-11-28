/*
* This example code is used for ESPink v3.1 board  https://www.laskakit.cz/laskakit-espink-esp32-e-paper-pcb-antenna
*
* ESPink board reads voltage of Battery  
* and sends every 2 seconds through UART 
*
* Made by (c) laskakit.cz 2024
*
* Board: ESP32-S3 Dev Module
*/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SDA 42
#define SCL 2
#define i2c_Address 0x3c
#define ADCpin 9
#define POWER 47
#define DeviderRatio 1.7693877551  // Voltage devider ratio on ADC pin 1MOhm + 1.3MOhm

Adafruit_SSD1306 display(128, 32, &Wire, -1);

void setup() {
    
  Serial.begin(115200);
  delay(100); // let serial console settle

  pinMode(POWER, OUTPUT);
  pinMode(ADCpin, INPUT);
  digitalWrite(POWER, HIGH);

  Wire.begin(SDA,SCL);
  
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, i2c_Address)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  display.clearDisplay(); 
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setTextSize(1); 
}

void loop() {

  float bat_voltage = analogReadMilliVolts(ADCpin) * DeviderRatio / 1000;
  Serial.print("Battery Voltage = " );
  Serial.print(bat_voltage);
  Serial.println("V");

  display.setCursor(0,0);
  display.println("Battery: " + String(bat_voltage, 3) + "V");
  display.display();
  display.clearDisplay();
  delay(2000);
}
