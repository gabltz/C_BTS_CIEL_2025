#include <OneWire.h>

/*Semaine projet Escape Game
  Module 4 : capteur de temperature
  Mougin Léane
  19/02/24
  version 1
*/

/************************Cablage****************************
  +(rouge) -> 3V3
  -(jaune) -> D5
  GND(noir) -> GND
************************************************************/

int pin_sortie = 5; //pin sortie sur D5

//Temperature chip i/o
OneWire ds(pin_sortie); 

void setup(void) {
  Serial.begin(9600);
  delay(400);

}

void loop(void) {
  float temperature = getTemp();    //relève la temperature
  Serial.println(temperature);

  delay(1000); //delay toute les 1s

}


float getTemp(){
  //renvoie la temperature en degrés celcius

  byte data[12];
  byte addr[8];

  if ( !ds.search(addr)) {
      //no more sensors on chain, reset search
      ds.reset_search();
      return -1000;
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.println("CRC n'est pas valide!");
      return -1000;
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28) {
      Serial.print("Le service n'est pas reconnu");
      return -1000;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1); // start conversion, with parasite power on at the end

  byte present = ds.reset();
  ds.select(addr);
  ds.write(0xBE); // Read Scratchpad


  for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = ds.read();
  }

  ds.reset_search();

  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB); //using two's compliment
  float TemperatureSum = tempRead / 16;

  return TemperatureSum;

}