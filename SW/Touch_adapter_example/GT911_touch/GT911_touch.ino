// Touch example for LaskaKit E-paper touch adapter with display with GT911 touch driver.

// Tested: Good Display GDEY075T7-T01 7.5" 800x480      https://www.laskakit.cz/good-display-gdey075t7-t01-7-5--800x480-epaper-displej-grayscale-dotykovy/


#include <Wire.h>
#include "initGT911.h"      //https://github.com/milad-nikpendar/initGT911

// Define the board:
//#define ESPink_V2     //for version v2.4 and earlier
#define ESPink_V3     //for version v3.0 and above

#ifdef ESPink_V2
  #define POWER 2
  #define SDA   21
  #define SCL   22

#else ESPink_V3
  #define POWER 47
  #define SDA   42
  #define SCL   2

#endif

#define I2C_FREQ 400000

// GT911 I2C address
#define TOUCH_ADDR 0x5D // or GT911_I2C_ADDR_28

// Reset and INT pins (set to -1 if unused)
#define RST_PIN  -1
#define INT_PIN  -1  // not used in polling mode

// Create GT911 object
initGT911 Touchscreen(&Wire, TOUCH_ADDR);

void setup() {
  Serial.begin(115200);
  pinMode(POWER, OUTPUT);     // Set display power pin as output
  digitalWrite(POWER, HIGH);  // Turn on the display
  delay(100);

  // Initialize I2C
  Wire.begin(SDA, SCL, I2C_FREQ);

  // Initialize GT911 in polling mode
  if (Touchscreen.begin(INT_PIN, RST_PIN, I2C_FREQ)) {
    Serial.println("GT911 initialized in polling mode");
    Touchscreen.setupDisplay(800, 480, initGT911::Rotate::_0); // example resolution
  } else {
    Serial.println("Failed to initialize GT911");
  }
}

void loop() {
  // In polling mode, we pass GT911_MODE_POLLING
  uint8_t touchCount = Touchscreen.touched(GT911_MODE_POLLING);

  if (touchCount > 0) {
    for (uint8_t i = 0; i < touchCount; i++) {
      GTPoint p = Touchscreen.getPoint(i);
      Serial.printf("Touch %d: X=%d, Y=%d\n", i, p.x, p.y);
    }
  }

  delay(20); // Small delay to reduce bus load
}
