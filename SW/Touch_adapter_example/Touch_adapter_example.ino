// Touch example for LaskaKit E-paper touch adapter.
// ESPink-42 Touch FT6336

#include <Arduino.h>
#include "FT6236.h"
#include <esp_timer.h>

#define DISPLAY_POWER_PIN 2  // Epaper power pin

FT6236 ts = FT6236(400, 300);

void setup() {
  Serial.begin(115200);
  pinMode(DISPLAY_POWER_PIN, OUTPUT);     // Set display power pin as output
  digitalWrite(DISPLAY_POWER_PIN, HIGH);  // Turn on the display

  if (!ts.begin(10))  // 40 in this case represents the sensitivity. Try higer or lower for better response.
  {
    Serial.println("Unable to start the capacitive touchscreen.");
  }
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