// Touch example for LaskaKit E-paper touch adapter with displays with FT6236 touch driver.

// Tested: Good Display GDEY027T91-T01 2.7" 264x176         https://www.laskakit.cz/good-display-gdey027t91-t01-2-7--264x176-epaper-displej-grayscale-dotykovy/
// Tested: Good Display GDEY029T94-T01 2.9" 296x128         https://www.laskakit.cz/good-display-gdey029t94-t01-2-9--296x128-epaper-displej-grayscale-dotykovy/
// Tested: Good Display GDEY042T81-FT02 4.2" 400x300        https://www.laskakit.cz/good-display-gdey042t81-ft02-4-2--400x300-epaper-displej-dotykovy-s-podsvicenim/
// Not Tested: Good Display GDEQ0426T82-FT?? 4.26" 800x480  https://www.laskakit.cz/good-display-gdeq0426t82-4-26--800x480-epaper-displej-grayscale/


#include <Arduino.h>
#include "FT6236.h"
#include <esp_timer.h>

// Define the board:
//#define ESPink_V2     //for version v2.4 and earlier
#define ESPink_V3     //for version v3.0 and above

// Define the display:
//#define GDEY027T91T01       //for https://www.laskakit.cz/good-display-gdey027t91-t01-2-7--264x176-epaper-displej-grayscale-dotykovy/
//#define GDEY029T94T01       //for https://www.laskakit.cz/good-display-gdey029t94-t01-2-9--296x128-epaper-displej-grayscale-dotykovy/
#define GDEY042T81FT02      //for https://www.laskakit.cz/good-display-gdey042t81-ft02-4-2--400x300-epaper-displej-dotykovy-s-podsvicenim/
//#define GDEQ0426T82         //for https://www.laskakit.cz/good-display-gdeq0426t82-4-26--800x480-epaper-displej-grayscale/

#ifdef GDEY0154D67T03
  #define RES_X   200 
  #define RES_Y   200
#elif defined(GDEY027T91T01)
  #define RES_X   264 
  #define RES_Y   176
#elif defined(GDEY029T94T01)
  #define RES_X   296 
  #define RES_Y   128
#elif defined(GDEY042T81FT02)
  #define RES_X   400 
  #define RES_Y   300
#elif defined(GDEY042T81FT02)
  #define RES_X   800 
  #define RES_Y   480
#endif

#ifdef ESPink_V2
  #define POWER 2
  #define SDA   21
  #define SCL   22

#else ESPink_V3
  #define POWER 47
  #define SDA   42
  #define SCL   2

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