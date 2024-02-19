#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "Cisco24G";
const char* password = ""; // Mot de passe vide

const char* serverIP = "172.18.30.150";
const uint16_t serverPort = 5000;

/// Définir values pour sendPacket avec récupération auto des ES

values = "";

WiFiUDP udp;


void sendPacket(values){
  udp.beginPacket(serverIP, serverPort);
  udp.print(values);
  udp.endPacket();
}

void setup() {
  Serial.begin(115200);
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

void loop() {
  // Envoi des données au serveur
  sendPacket(values)

  }
  
}
