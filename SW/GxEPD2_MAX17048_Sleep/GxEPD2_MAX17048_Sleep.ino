// Display Library example for SPI e-paper panels from Dalian Good Display and boards from Waveshare.
// Requires HW SPI and Adafruit_GFX. Caution: the e-paper panels require 3.3V supply AND data lines!
//
// Display Library based on Demo Example from Good Display: http://www.e-paper-display.com/download_list/downloadcategoryid=34&isMode=false.html
//
// Author: Jean-Marc Zingg
//
// Version: see library.properties
//
// Library: https://github.com/ZinggJM/GxEPD2

// Supporting Arduino Forum Topics:
// Waveshare e-paper displays with SPI: http://forum.arduino.cc/index.php?topic=487007.0
// Good Display ePaper for Arduino: https://forum.arduino.cc/index.php?topic=436411.0

// see GxEPD2_wiring_examples.h for wiring suggestions and examples

// base class GxEPD2_GFX can be used to pass references or pointers to the display instance as parameter, uses ~1.2k more code
// enable or disable GxEPD2_GFX base class
#define ENABLE_GxEPD2_GFX 0

// uncomment next line to use class GFX of library GFX_Root instead of Adafruit_GFX
//#include <GFX.h>
// Note: if you use this with ENABLE_GxEPD2_GFX 1:
//       uncomment it in GxEPD2_GFX.h too, or add #include <GFX.h> before any #include <GxEPD2_GFX.h>

#include <GxEPD2_BW.h>
#include <GxEPD2_4C.h>
#include <SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library.h> // Click here to get the library: http://librarymanager/All#SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library
#include <Fonts/FreeMonoBold9pt7b.h>

#define SLEEP_SEC 15         // Measurement interval (seconds)
//MOSI/SDI    11
//CLK/SCK     12
//SS/CS       10
#define DC    48 
#define RST   45  
#define BUSY  36 
#define POWER 47
#define SDA   42
#define SCL   2

SFE_MAX1704X lipo(MAX1704X_MAX17048); // Create a MAX17048

//GxEPD2_BW<GxEPD2_270, GxEPD2_270::HEIGHT> display(GxEPD2_270(SS, DC, RST, BUSY)); // GDEW027W3 176x264, EK79652 (IL91874)
//GxEPD2_BW<GxEPD2_420_GDEY042T81, GxEPD2_420_GDEY042T81::HEIGHT> display(GxEPD2_420_GDEY042T81(SS, DC, RST, BUSY)); // GDEY042T81, 400x300, SSD1683 (no inking)
GxEPD2_4C<GxEPD2_290c_GDEY029F51H, GxEPD2_290c_GDEY029F51H::HEIGHT> display(GxEPD2_290c_GDEY029F51H(SS, DC, RST, BUSY));

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("setup");
  delay(100);

// turn on power to display
  pinMode(POWER, OUTPUT);
  digitalWrite(POWER, HIGH);   // turn the LED on (HIGH is the voltage level)
  Serial.println("Display power ON");
  delay(1000);  

  Wire.begin (SDA, SCL);
  
  display.init(); // inicializace
  delay(1000);
  lipo.enableDebugging(); // Uncomment this line to enable helpful debug messages on Serial

  // Set up the MAX17048 LiPo fuel gauge:
  if (lipo.begin() == false) // Connect to the MAX17048 using the default wire port
  {
    Serial.println(F("MAX17048 not detected. Please check wiring. Freezing."));
    while (1)
      ;
  }

  // Just because we can, let's reset the MAX17048
  Serial.println(F("Resetting the MAX17048..."));
  delay(1000); // Give it time to get its act back together

  // Read and print the reset indicator
  Serial.print(F("Reset Indicator was: "));
  bool RI = lipo.isReset(true); // Read the RI flag and clear it automatically if it is set
  Serial.println(RI); // Print the RI
  // If RI was set, check it is now clear
  if (RI)
  {
    Serial.print(F("Reset Indicator is now: "));
    RI = lipo.isReset(); // Read the RI flag
    Serial.println(RI); // Print the RI    
  }

  // To quick-start or not to quick-start? That is the question!
  // Read the following and then decide if you do want to quick-start the fuel gauge.
  // "Most systems should not use quick-start because the ICs handle most startup problems transparently,
  //  such as intermittent battery-terminal connection during insertion. If battery voltage stabilizes
  //  faster than 17ms then do not use quick-start. The quick-start command restarts fuel-gauge calculations
  //  in the same manner as initial power-up of the IC. If the system power-up sequence is so noisy that the
  //  initial estimate of SOC has unacceptable error, the system microcontroller might be able to reduce the
  //  error by using quick-start."
  // If you still want to try a quick-start then uncomment the next line:
	//lipo.quickStart();

  // Read and print the device ID
  Serial.print(F("Device ID: 0x"));
  uint8_t id = lipo.getID(); // Read the device ID
  if (id < 0x10) Serial.print(F("0")); // Print the leading zero if required
  Serial.println(id, HEX); // Print the ID as hexadecimal

  // Read and print the device version
  Serial.print(F("Device version: 0x"));
  uint8_t ver = lipo.getVersion(); // Read the device version
  if (ver < 0x10) Serial.print(F("0")); // Print the leading zero if required
  Serial.println(ver, HEX); // Print the version as hexadecimal

  // Read and print the battery threshold
  Serial.print(F("Battery empty threshold is currently: "));
  Serial.print(lipo.getThreshold());
  Serial.println(F("%"));

	// We can set an interrupt to alert when the battery SoC gets too low.
	// We can alert at anywhere between 1% and 32%:
	lipo.setThreshold(20); // Set alert threshold to 20%.

  // Read and print the battery empty threshold
  Serial.print(F("Battery empty threshold is now: "));
  Serial.print(lipo.getThreshold());
  Serial.println(F("%"));

  // Read and print the high voltage threshold
  Serial.print(F("High voltage threshold is currently: "));
  float highVoltage = ((float)lipo.getVALRTMax()) * 0.02; // 1 LSb is 20mV. Convert to Volts.
  Serial.print(highVoltage, 2);
  Serial.println(F("V"));

  // Set the high voltage threshold
  lipo.setVALRTMax((float)4.1); // Set high voltage threshold (Volts)

  // Read and print the high voltage threshold
  Serial.print(F("High voltage threshold is now: "));
  highVoltage = ((float)lipo.getVALRTMax()) * 0.02; // 1 LSb is 20mV. Convert to Volts.
  Serial.print(highVoltage, 2);
  Serial.println(F("V"));

  // Read and print the low voltage threshold
  Serial.print(F("Low voltage threshold is currently: "));
  float lowVoltage = ((float)lipo.getVALRTMin()) * 0.02; // 1 LSb is 20mV. Convert to Volts.
  Serial.print(lowVoltage, 2);
  Serial.println(F("V"));

  // Set the low voltage threshold
  lipo.setVALRTMin((float)3.9); // Set low voltage threshold (Volts)

  // Read and print the low voltage threshold
  Serial.print(F("Low voltage threshold is now: "));
  lowVoltage = ((float)lipo.getVALRTMin()) * 0.02; // 1 LSb is 20mV. Convert to Volts.
  Serial.print(lowVoltage, 2);
  Serial.println(F("V"));

  // Enable the State Of Change alert
  Serial.print(F("Enabling the 1% State Of Change alert: "));
  if (lipo.enableSOCAlert())
  {
    Serial.println(F("success."));
  }
  else
  {
    Serial.println(F("FAILED!"));
  }
  
  // Read and print the HIBRT Active Threshold
  Serial.print(F("Hibernate active threshold is: "));
  float actThr = ((float)lipo.getHIBRTActThr()) * 0.00125; // 1 LSb is 1.25mV. Convert to Volts.
  Serial.print(actThr, 5);
  Serial.println(F("V"));

  // Read and print the HIBRT Hibernate Threshold
  Serial.print(F("Hibernate hibernate threshold is: "));
  float hibThr = ((float)lipo.getHIBRTHibThr()) * 0.208; // 1 LSb is 0.208%/hr. Convert to %/hr.
  Serial.print(hibThr, 3);
  Serial.println(F("%/h"));
   // Print the variables:
  Serial.print("Voltage: ");
  Serial.print(lipo.getVoltage());  // Print the battery voltage
  Serial.print("V");

  Serial.print(" Percentage: ");
  Serial.print(lipo.getSOC(), 2); // Print the battery state of charge with 2 decimal places
  Serial.print("%");

  Serial.print(" Change Rate: ");
  Serial.print(lipo.getChangeRate(), 2); // Print the battery change rate with 2 decimal places
  Serial.print("%/hr");
  
  Serial.println();

  // first update should be full refresh
  Display();
  delay(1000);

  display.powerOff();

  Serial.println("setup done");

  goToSleep();
}

void goToSleep(){
  Serial.println("going to sleep " + String(SLEEP_SEC) + " sek");
  Serial.print("enableHibernate (Output: 0 on success, positive integer on fail): ");
  Serial.println(lipo.enableHibernate());

  // ESP Deep Sleep 
  digitalWrite(POWER, LOW);   // turn the LED on (HIGH is the voltage level)
  Serial.println("Display power OFF");
  Serial.println("ESP in sleep mode");
  Serial.flush(); 
  esp_sleep_enable_timer_wakeup(SLEEP_SEC * 1000000);
  esp_deep_sleep_start();
}

void loop()
{
}

const char HelloWorld[] = "Hello World!";

void Display()
{
  //Serial.println("helloWorld");
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  if (display.epd2.WIDTH < 104) display.setFont(0);
  display.setTextColor(GxEPD_BLACK);

  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(5, 20);
    display.print("Voltage: " + String(lipo.getVoltage()) + "V");
    display.setCursor(5, 50);
    display.print("Percentage: " + String(lipo.getSOC(), 2) + "%");
    display.setCursor(5, 80);
    display.print("Change Rate: " + String(lipo.getChangeRate(), 2) + "%/hr");
  }
  while (display.nextPage());
  Serial.println("Writing done");
}
