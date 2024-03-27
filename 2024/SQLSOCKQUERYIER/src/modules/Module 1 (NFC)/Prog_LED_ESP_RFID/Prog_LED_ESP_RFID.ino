/*
Nom : Prog_LED_ESP_RFID
Créateur : Lylou BALLAND
Description : Programme de l'ESP8266 pour liaison entre l'arduino (Recupere info RFID) et le serveur, le signal OK se fait par l'allumage de la LED (L'ESP recupère le 0V ou 5V de la LED)
Infos Complémentaire: Type de carte : NodeMCU 1.0 (ESP-12E Module)
Cablage : (Voir schema)
Date : 21/02/24
Derniere modif : 21/02/24 13h30
 */

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "Cisco24G";
const char* password = ""; // Mot de passe vide

const char* serverIP = "172.18.30.150";
const uint16_t serverPort = 5000;

WiFiUDP udp;

// Déclaration de la broche utilisée pour la LED entre l'Arduino et l'ESP
const int LEDVerte = D0; // Broche à laquelle est connectée la LED

// Variable pour stocker l'état précédent du bouton
int LEDEtat = LOW;

void setup() {
  // Initialisation des broches de la LED 
  pinMode(LEDVerte, OUTPUT);

  // Initialisation de la communication série pour afficher les messages
  Serial.begin(9600);

  // Configuration de l'adresse IP statique
  IPAddress ip(172, 18, 30, 157);
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

void loop() {
  // Lecture de l'état actuel du bouton
  int LEDEtat = digitalRead(LEDVerte);
  
    // Si la LED est allumée
    if (LEDEtat == HIGH ) {
      // Envoyer un message au serveur
      Serial.println("LED BONJOUR");
      udp.beginPacket(serverIP, serverPort);
      udp.print("1,0,0,1"); // N° module , N° entrée , N° Sortie , Etat
      udp.endPacket();
      delay (9000);
    }
     delay(1000);
  }
