#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define SendKey 0  // Bouton pour envoyer des données (BTN Flash sur NodeMCU)
int port = 5001;  // Numéro de port
WiFiUDP udp;

const char *ssid = "Cisco24G";  // Entrez votre SSID WiFi
const char *password = "";  // Entrez votre mot de passe WiFi

const int KlaxonPin = 4; // Définir le pin pour le klaxon

void setup() {
  Serial.begin(115200);
  pinMode(SendKey, INPUT_PULLUP);  // Bouton pour envoyer des données
  pinMode(KlaxonPin, OUTPUT); // Définir le pin du klaxon en sortie
  Serial.println();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);  // Connexion au WiFi

  Serial.println("Connexion au WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.print("Connecté à ");
  Serial.println(ssid);

  Serial.print("Adresse IP: ");
  Serial.println(WiFi.localIP());

  Serial.print("Ouvrir un logiciel et se connecter à l'adresse IP: ");
  Serial.print(WiFi.localIP());
  Serial.print(" sur le port ");
  Serial.println(port);

  udp.begin(port);  // Démarrer le serveur UDP sur le port spécifié
}

void loop() {
  if (Serial.available() > 0) {
    udp.beginPacket(udp.remoteIP(), udp.remotePort()); // Début du paquet UDP avec l'adresse IP et le port du client distant
    while (Serial.available() > 0) {
      udp.write(Serial.read()); // Écriture des données de série dans le paquet UDP
    }
    udp.endPacket(); // Fin du paquet UDP
  }

  int packetSize = udp.parsePacket(); // Vérifier s'il y a des données UDP entrantes

  if (packetSize) {
    char packetBuffer[255];
    udp.read(packetBuffer, packetSize);
    packetBuffer[packetSize] = '\0';

    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("Contents:");
    Serial.println(packetBuffer);

    // Extraire les trois derniers caractères de la trame
    char lastThreeValues[4]; // Pour stocker "1,1,"
    strncpy(lastThreeValues, packetBuffer + strlen(packetBuffer) - 4, 3); // Copie les trois derniers caractères
    lastThreeValues[3] = '\0'; // Ajoute le caractère de fin de chaîne

    // Comparer les trois derniers caractères avec "1,1,"
    if (strcmp(lastThreeValues, "1,1") == 0) {
      Serial.println("Last three values are 1,1");
      // Activer le relai pour envoyer du courant vers le klaxon
      digitalWrite(KlaxonPin, HIGH);
      delay(1000); // Temps pendant lequel le klaxon est activé (en millisecondes)
      digitalWrite(KlaxonPin, LOW); // Désactiver le relai
    } else {
      Serial.println("Last three values are not 1,1");
    }
  }
}