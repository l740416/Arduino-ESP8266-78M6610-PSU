#include <Wire.h>
#include <MI78M6610PSU.h>


MI78M6610PSU mi78m6610psu;
  
void setup() {
  Serial.begin(57600);
  if (!mi78m6610psu.begin()) {
  	Serial.println("Could not find a valid 78M6610PSU controller, check wiring!");
  	while (1) {}
  }
}

bool relay = 0;
void loop() {
    
  Serial.printf("78M6610PSU firmware: %X\n", mi78m6610psu.firmware());
  Serial.printf("78M6610PSU Vrms: %d, unscale: %d\n", mi78m6610psu.Vrms(), mi78m6610psu.VrmsUnscale());
  Serial.printf("78M6610PSU Irms: %d, unscale: %d\n", mi78m6610psu.Irms(), mi78m6610psu.IrmsUnscale());
  Serial.printf("78M6610PSU Watt: %d\n", mi78m6610psu.Watt());
  
  mi78m6610psu.setRelay(relay);
  relay = !relay;
  
  delay(10000);
}
