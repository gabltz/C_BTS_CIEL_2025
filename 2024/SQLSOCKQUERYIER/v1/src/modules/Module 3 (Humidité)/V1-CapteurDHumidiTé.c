/*
 Nom : Prog_Humidite
 Créateur : Lylou BALLAND
 Description : Permet de relever la valeur d'humidité prise par le capteur DHT11 (ATTENTION TRANSFERT VERS SERVEUR NON FAIT)
 Cablage : (Voir schema)
 Date : 18/02/24
 Derniere modif : 19/02/24
 */
 
#include <WiFi.h>
#include <WiFiUdp.h>
#include <DHT.h>  // Bibliothèque DHT

const char* ssid = "Cisco24G";
const char* password = ""; // Mot de passe vide

const char* serverIP = "172.18.30.150";
const uint16_t serverPort = 5000;

WiFiUDP udp;

const int DHTPin = 23;     // Pin du capteur DHT
const int DHTType = DHT11; // Type de capteur DHT

DHT dht(DHTPin, DHTType);

void sendPacket(values){
  udp.beginPacket(serverIP, serverPort); //Début du packet avec initialisation au serveur 
  udp.print(values); // Envoi sur le socket  
  udp.endPacket(); // Fermeture et signature du packet UDP
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Configuration de l'adresse IP statique
  IPAddress ip(172, 18, 30, 142);
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

  // Initialisation du capteur DHT
  dht.begin();
}

void loop() {
  // Lecture de l'humidité
  float humidity = dht.readHumidity();
  
  // Vérification de l'humidité
  if (!isnan(humidity) && humidity >= 65.0) {
    // Envoi des données au serveur
    sendpacket("3,23,0,1")

    Serial.println("3,23,0,1");
  }
  
  // Attente d'une seconde avant la prochaine lecture
  delay(1000);
}