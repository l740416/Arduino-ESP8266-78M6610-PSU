#include <Wire.h>
#include <MI78M6610PSU.h>


MI78M6610PSU mi78m6610psu;
  
void setup() {
  Serial.begin(57600);
  if (!mi78m6610psu.begin(5,4)) {
  	Serial.println("\n\nCould not find a valid 78M6610PSU controller, check wiring!");
  }
}

bool relay = 0;
void loop() {

  if( mi78m6610psu.exist() ) {
      
    Serial.printf("78M6610PSU firmware: %X\n", mi78m6610psu.Firmware());
    Serial.printf("78M6610PSU Vrms: %d, unscale: %d\n", mi78m6610psu.Vrms(), mi78m6610psu.VrmsUnscale());
    Serial.printf("78M6610PSU Irms: %d, unscale: %d\n", mi78m6610psu.Irms(), mi78m6610psu.IrmsUnscale());
    Serial.printf("78M6610PSU Freq: %d, unscale: %d\n", mi78m6610psu.Freq(), mi78m6610psu.FreqUnscale());
    Serial.printf("78M6610PSU PF: %d\n", mi78m6610psu.PwrFactor());
    Serial.printf("78M6610PSU Watt: %d\n", mi78m6610psu.Watt());
 
    Serial.printf("78M6610PSU DIO: %08X\n", mi78m6610psu.DioState());
    Serial.printf("78M6610PSU AlarmStatus: %08X\n", mi78m6610psu.AlarmState());


    mi78m6610psu.setVscale( 666 * 1000 );
    mi78m6610psu.setIscale( 53.364 * 1000 );
    mi78m6610psu.setPscale( 666 * 53.364 * 1 );
    
    
    //mi78m6610psu.setRelay(relay);
    //relay = !relay;

  } else {
    Serial.println("Could not find a valid 78M6610PSU controller, check wiring!");
  }
  
  delay(10000);
}