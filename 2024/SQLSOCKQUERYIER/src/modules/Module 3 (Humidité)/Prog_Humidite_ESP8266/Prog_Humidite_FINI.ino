#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

/*
 Nom : Prog_Humidite
 Créateur : Lylou BALLAND
 Description : Permet de relever la valeur d'humidité prise par le capteur DHT22 (ATTENTION TRANSFERT VERS SERVEUR NON FAIT)
 Cablage : (Voir schema)
 Transfert vers serveur fait par Enzo TERNIER
 Infos Complémentaire: Type de carte : NodeMCU 1.0 (ESP-12E Module)
 Date : 20/02/24 
 Derniere modif : 20/02/24 12h05
 */

const char* ssid = "Cisco24G";
const char* password = ""; // Mot de passe vide

const char* serverIP = "172.18.30.150";
const uint16_t serverPort = 5000;

WiFiUDP udp;

#define DHTPIN D2 // Digital pin connected to the DHT sensor 
#define DHTTYPE DHT22 // DHT 22 (AM2302)

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;
bool dataSent = false; // Variable pour garder une trace de si les données ont été envoyées

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Initialize WiFi
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

  // Initialize DHT sensor
  dht.begin();

  // Set delay between sensor readings based on sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;
}

void loop() {
  // Delay between measurements.
  delay(delayMS);

  // Get humidity event and print its value.
  sensors_event_t event;
  dht.humidity().getEvent(&event);

  if (!isnan(event.relative_humidity)) {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));

    // Check if humidity is 65% or more, then send data to server
    if (event.relative_humidity >= 65 && !dataSent) {
      // Send data to server
      udp.beginPacket(serverIP, serverPort);
      udp.print("3,2,0,1");
      udp.endPacket();
      
      // Set dataSent to true to indicate that data has been sent
      dataSent = true;
    }
  } else {
    Serial.println(F("Error reading humidity!"));
  }
}