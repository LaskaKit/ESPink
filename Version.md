### Version 3.4
- Reset button and ESP32 moved about 1.5mm
#### Version 3.3
- Changed pull-ups R14, R19 +3.3V to VSENSOR
#### Version 3.1
- Updated, more configurable driver schématic for display, based on displays datasheet and adapters from Good Display.
- Simplified power switching for display.
- Switching Battery ADC on GPIO09
- TODO: rethink charging, charging alert
#### Version 2.6
- Resistor R12 changed to 2.55 Ohm
#### Version 2.5
- Programming chip (CH9102) added. Still about 10µA in deep sleep ;)
- New µŠUP SPI connector (need to be powered by pin IO02)
- Separated LDO with Enable pin IO02 for uSup connector, 500mA max on 3.3V
#### Version 1.3
- ADC jumper moved and default closed | Propojka ADC se přesunula a ve výchozím nastavení uzavřena
- Error fixed, pins 13 and GND were swapped | Opravené chybá popisu, prohození pinů 13 a GND
#### Version 1.2
Adjusted resistor values in the resistance divider to 1M/1.3M, ADC max. input voltage stays the same.| Upraveny hodnoty rezistorů v odporovém děliči na 1M/1.3M, ADC max. vstupní napětí zůstává stejné.
#### Version 1.1
- Minor update, description, shape  | Malé změny, popis, tvar...
#### Version 1.0
- Initial | Počáteční