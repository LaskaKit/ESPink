![ESPink top](https://github.com/LaskaKit/ESPink/blob/main/img/ESPink_top_popis.JPG)

# ESPink - versatile and low power board with ESP32 for ePaper/eInk

[ePaper displays](https://www.laskakit.cz/e-ink/) are more and more popular mainly thanks to low power consumption and wide viewing angle. 
But what board you should use to control it? We designed ESPink, small board focused on the lowest power consumption, easy connection of sensors and big memory for graphics. 
The ESPink is based on ESP32 what is one of the most popular Wi-Fi and Bluetooth modules. 

What is on board? Connector for connection of ePaper/eInk. The ePaper is very low power but it is drawing current during sleep (a few uA). To achieve the lowest current, we assembled transistor between power and input of ePaper. Thanks to this, the current through ePaper during the sleep is zero. The gate of transistor is connected to GPIO2 and the power supply for ePaper is enabled in case GPIO2 is set to HIGH.

One more feature how to decrease the current is the external [LaskaKit CH340 programmer](https://www.laskakit.cz/laskakit-ch340-programmer-usb-c--microusb--uart/),
what we are using for all of our boards. So only one programmer may upload code to all of our low power boards.

The board is powered from [lipol battery](https://www.laskakit.cz/baterie-a-akumulatory/) what is chargered from USB-C, no longer micro USB.
The design is ready for measurement of battery voltage. The voltage divider is connected to battery and GPIO34 where is ADC input.

The connection of sensors is so easy and safe thanks to our μŠup connector. The connector includes and lock and the pinout is the same for all sensors and board made by laskakit.cz.  
The sensors what include μŠup connector are [LaskaKit SHT40 Senzor of temperature and humidity](https://www.laskakit.cz/laskakit-sht40-senzor-teploty-a-vlhkosti-vzduchu/) and  [LaskaKit SCD41 Senzor CO2, temperature and humidity ](https://www.laskakit.cz/laskakit-scd41-senzor-co2--teploty-a-vlhkosti-vzduchu/).

ESP32 includes a lot of GPIO what we didn't use, but we keep them for custom purpose. So you can solder what you want.

![ESPink top](https://github.com/LaskaKit/ESPink/blob/main/img/ESPink_back_popis.JPG)

The ESPink was precisly designed for low power but also the labeled GPIO what we used on board. On the bottom side is solder bridge what defines the charging current. By default is set 400mA, but you can choose 260mA. Just cut the this track and put a drop of thin on the oposite side of solder bridge.

ESPink is available on https://www.laskakit.cz/laskakit-espink-esp32-e-paper-pcb-antenna/
We prepared example codes available on this link https://github.com/LaskaKit/ESPink/tree/main/SW
