// Touch example for LaskaKit E-paper touch adapter.

// Tested: Good Display GDEY0154D67-T03 1.54" 200x200   https://www.laskakit.cz/good-display-gdey0154d67-t03-1-54--200x200-epaper-displej-dotykovy/
// Tested: Good Display GDEY027T91-T01 2.7" 264x176     https://www.laskakit.cz/good-display-gdey027t91-t01-2-7--264x176-epaper-displej-grayscale-dotykovy/
// Tested: Good Display GDEY029T94-T01 2.9" 296x128     https://www.laskakit.cz/good-display-gdey029t94-t01-2-9--296x128-epaper-displej-grayscale-dotykovy/
// Tested: Good Display GDEY042T81-FT02 4.2" 400x300    https://www.laskakit.cz/good-display-gdey042t81-ft02-4-2--400x300-epaper-displej-dotykovy-s-podsvicenim/
// Tested: Good Display GDEY075T7-T01 7.5" 800x480      https://www.laskakit.cz/good-display-gdey075t7-t01-7-5--800x480-epaper-displej-grayscale-dotykovy/


#include <Arduino.h>
#include "FT6236.h"
#include <esp_timer.h>

// Define the board:
//#define ESPink_V2     //for version v2.4 and earlier
#define ESPink_V3     //for version v3.0 and above

// Define the display:
//#define GDEY0154D67T03      //for https://www.laskakit.cz/good-display-gdey0154d67-t03-1-54--200x200-epaper-displej-dotykovy/
//#define GDEY027T91T01       //for https://www.laskakit.cz/good-display-gdey027t91-t01-2-7--264x176-epaper-displej-grayscale-dotykovy/
//#define GDEY029T94T01       //for https://www.laskakit.cz/good-display-gdey029t94-t01-2-9--296x128-epaper-displej-grayscale-dotykovy/
#define GDEY042T81FT02      //for https://www.laskakit.cz/good-display-gdey042t81-ft02-4-2--400x300-epaper-displej-dotykovy-s-podsvicenim/
//#define GDEY075T7T01        //for https://www.laskakit.cz/good-display-gdey075t7-t01-7-5--800x480-epaper-displej-grayscale-dotykovy/

#ifdef GDEY0154D67T03
  #define DRIVER  FT6236
  #define RES_X   200 
  #define RES_Y   200
#elif defined(GDEY027T91T01)
  #define DRIVER  FT6236
  #define RES_X   264 
  #define RES_Y   176
#elif defined(GDEY029T94T01)
  #define DRIVER  FT6236
  #define RES_X   296 
  #define RES_Y   128
#elif defined(GDEY042T81FT02)
  #define DRIVER  FT6236
  #define RES_X   400 
  #define RES_Y   300
#elif defined(GDEY075T7T01)
  #define DRIVER  GT911
  #define RES_X   800 
  #define RES_Y   480
#endif

#ifdef ESPink_V2
  //MOSI/SDI    23
  //CLK/SCK     18
  //SS/CS       5
  #define DC    17 
  #define RST   16  
  #define BUSY  4 
  #define POWER 2
  #define SDA   21
  #define SCL   22
  #define BAT   34
#else ESPink_V3
  //MOSI/SDI    11
  //CLK/SCK     12
  //SS/CS       10
  #define DC    48 
  #define RST   45  
  #define BUSY  38 
  #define POWER 47
  #define SDA   42
  #define SCL   2
  #define BAT   9
#endif

FT6236 ts = FT6236(RES_X, RES_Y);

void setup() {
  Serial.begin(115200);
  pinMode(POWER, OUTPUT);     // Set display power pin as output
  digitalWrite(POWER, HIGH);  // Turn on the display
  Wire.begin (SDA, SCL);
  delay(200); // wait to I2C begin

  if (!ts.begin(40)) // 40 in this case represents the sensitivity. Try higer or lower for better response.
    Serial.println("Unable to start the capacitive touchscreen.");
  else
    Serial.println("Capacitive touchscreen started.");
}


void loop() {
  if (ts.touched()) {
    char text[30];
    // Retrieve a point
    TS_Point p = ts.getPoint();
    sprintf(text, "X: %d", p.x);
    Serial.print(text);
    sprintf(text, "Y: %d", p.y);
    Serial.println(text);

  }
  // Debouncing. To avoid returning the same touch multiple times you can play with this delay.
  delay(50);
}