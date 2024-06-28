/* Battery percentage test for LaskaKit ESPink from ver. 3.2"
 *
 * -------------------------------
 * Email:podpora@laskakit.cz
 * Web:laskakit.cz
 */


#include <Wire.h>
#include "MAX17048.h" // https://github.com/hideakitai/MAX17048

#define SDA   42
#define SCL   2

MAX17048 pwr_mgmt;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  Wire.begin (SDA, SCL);
  pwr_mgmt.attatch(Wire); //připojí čip MAX17048 k desce

  Serial.println("Start...");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println((String)"VCELL ADC : "+pwr_mgmt.adc()); //Vypíše hodnotu na ADC pinu 
  Serial.println((String)"VCELL V   : "+pwr_mgmt.voltage()+"V"); //Vypíše napětí na baterii
  Serial.println((String)"VCELL SOC : "+pwr_mgmt.percent()+" \%"); //Vypíše přibližné nabití baterie
  Serial.println((String)"VCELL SOC : "+pwr_mgmt.accuratePercent()+" \%"); //Vypíše přesné nabití baterie 
  Serial.println();
  delay(1000);
}
