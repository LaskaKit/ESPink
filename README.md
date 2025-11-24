![ESPink top](https://github.com/LaskaKit/ESPink/blob/main/img/ESPink_pinout.JPG)

# ESPink - versatile and low power board with ESP32 for ePaper/eInk

[ePaper displays](https://www.laskakit.cz/e-ink/) are becoming more and more popular mainly thanks to their low power consumption and wide viewing angle. 
But which board you should use to control your E-Paper display? We designed a board to answer this very question: The ESPink, a small board focused on the lowest possible power consumption and with plenty of memory for large, complicated graphics. 
The ESPink is based on ESP32, one of the most popular and widely accepted development boards in the world. 

What makes this board so special? First of all, a dedicated connect onnector for connection of an ePaper/eInk display. EPaper displays consume very little power, but it is drawing current during sleep (a few uA). To achieve the lowest current, we added a transistor between power and input of ePaper. Thanks to this, the current through ePaper during the sleep is zero. This same tranzistor is also used to switch the µŠup I2C and µŠup SPI power.

One more feature is the built-in programmer, where we used really low power programmer.

The board is powered from [lipol battery](https://www.laskakit.cz/baterie-a-akumulatory/) which is chargered from USB-C, no longer micro USB. As is standard with our boards, we've included a voltage divider (coef. 1.769388) which allows you to measure the voltage of the connected battery.

The connection of sensors is simple and secure thanks to our I2C μŠup connector, which includes a mechanical lock and a pinout compatible with all sensors and boards made by laskakit.cz, in addition to Adafruit STEMMA and Sparkfun QWIIC boards.  
Examples of boards with the μŠup connector are [LaskaKit SHT40 Sensor of temperature and humidity](https://www.laskakit.cz/laskakit-sht40-senzor-teploty-a-vlhkosti-vzduchu/) and  [LaskaKit SCD41 Sensor CO2, temperature and humidity ](https://www.laskakit.cz/laskakit-scd41-senzor-co2--teploty-a-vlhkosti-vzduchu/).
We also added an SPI μŠup connector for adding more data-hungry devices, such as SD card readers. 

The ESP32 has a lot of available GPIO pins which we didn't use, which are accesible via solder pads, allowing you to connect any and all modules you can think of.

![ESPink top](https://github.com/LaskaKit/ESPink/blob/main/img/ESPink_back_popis.JPG)

The ESPink was precisly designed for low power, but also the labeled GPIO what we used on board. On the bottom side is solder bridge, which defines the charging current. By default it is set 400 mA, but you can choose 260 mA. Just cut the this track and put a drop of solder on the oposite side of solder bridge.

ESPink is available on https://www.laskakit.cz/laskakit-espink-esp32-e-paper-pcb-antenna/
We prepared example codes available here: https://github.com/LaskaKit/ESPink/tree/main/SW

## Pinout
### Board

| Function | Board Version 2.7 | Board Version 3.5 |
| ------------- |:------------------:|:--------------------------:|
| MOSI/SDI | 23 | 11 |
| CLK/SCK | 5 | 10 |
| CS2 | - | 35 |
| DC | 17 | 48 |
| RST | 16 | 45 |
| BUSY | 4 | 38 |
| Voltage divider | 34 | 9 |

### µŠup I2C

| Function | Board Version 2.7 | Board Version 3.5 |
| ------------- |:------------------:|:--------------------------:|
|SDA|21|42|
|SCL|22|2|

### µŠup SPI

| Function | Board Version 2.7 | Board Version 3.5 |
| ------------- |:------------------:|:--------------------------:|
|MOSI/SDI|13|3|
|MISO/SDO|12|21|
|SCK|14|14|
|CS|15|46|
