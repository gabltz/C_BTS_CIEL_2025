#include <OneWire.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

/*Semaine projet Escape Game
  Module 4 : capteur de temperature
  Mougin Léane
  21/02/24
  version 2
*/

/************************Cablage****************************
  // carte Node MCU ESP8266
  on pin GPIO2  (D4) LS 19/02/2024 17:47 
  une resistance de 10K est necessaire vers +5V
  capteur alimenté en 5V
  +(rouge) -> 3V
  -(jaune) -> D4
  GND(noir) -> GND
************************************************************/

int pin_sortie = 2; //pin sortie sur D4
bool dataSent = false; // Variable pour garder une trace de si les données ont été envoyées


//Temperature chip i/o
OneWire ds(pin_sortie); 


//Configuration du Wifi 

const char* ssid = "Cisco24G";
const char* password = ""; // Mot de passe vide

// Configuration du socket 
const char* serverIP = "172.18.30.150";
const uint16_t serverPort = 5000;

/// Définir values pour sendPacket avec récupération auto des ES
char values[50];

WiFiUDP udp;

void setup(void) {
    Serial.begin(9600); // configure serial to talk to computer
    delay(1000);

    // Configuration de l'adresse IP statique
    IPAddress ip(172, 18, 30, 104);
    IPAddress gateway(172, 18, 30, 254);
    IPAddress subnet(255, 255, 255, 0);
    WiFi.config(ip, gateway, subnet);

    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop(void) {
  float temperature = getTemp();    //relève la temperature
  Serial.println(temperature);      //Affiche sur la temperature sur le moniteur serie

  if(temperature < 20 && !dataSent) { // Si la lumière est assez haute, comme une lampe torche devant et que l'on a pas deja envoyé à la bdd
      // Formater la chaîne avec les valeurs
      snprintf(values, 50, "4,2,0,%.2f", temperature);
      sendPacket(values);
      
      // Set dataSent à true pour indiquer que l'on a bien envoyé une donnée à la bdd
      dataSent = true;
    }

  else if(temperature >= 20 && dataSent) { //pour eviter de retransferer le programme a chaque fois
      dataSent = false;
    }

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
  ds.write(0x44,1); // convertion

  byte present = ds.reset();
  ds.select(addr);
  ds.write(0xBE); // Read Scratchpad


  for (int i = 0; i < 9; i++) { //9 bytes
    data[i] = ds.read();
  }

  ds.reset_search();

  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB); //using two's compliment
  float TemperatureSum = tempRead / 16;

  return TemperatureSum;
}

// Fonction pour envoyer les valeurs au serveur, values est une chaîne de caractère comportant (numModule[INT], numEntree[INT], numSortie[INT], ETAT[INT])
void sendPacket(const char* values){
  udp.beginPacket(serverIP, serverPort); //Début du packet avec initialisation au serveur 
  udp.print(values); // Envoi sur le socket  
  udp.endPacket(); // Fermeture et signature du packet UDP
}