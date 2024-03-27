
/*
 Nom : Prog_Humidite
 Créateur : Lylou BALLAND
 Description : Permet de relever la valeur d'humidité prise par le capteur DHT11 (ATTENTION TRANSFERT VERS SERVEUR NON FAIT)
 Cablage : (Voir schema)
 Date : 18/02/24
 Derniere modif : 19/02/24
 */
 
#include <DHT11.h>  // Bibliotheque DHT11

DHT11 dht11(23); // Pin 23 de l'ESP32

void setup()
{
    // Initialise la communication série pour permettre le débogage et la lecture des données.
    // Utilisant un débit en bauds de 9 600.
    Serial.begin(9600);
}

void loop()
{
    // Tentative de lecture de la valeur d'humidité du capteur DHT11.
    int humidity = dht11.readHumidity();
    
    // Vérifiez le résultat de la lecture.
    // S'il n'y a pas d'erreur, affiche la valeur d'humidité.
    // S'il y a une erreur, affiche le message d'erreur approprié.
    if (humidity != DHT11::ERROR_CHECKSUM && humidity != DHT11::ERROR_TIMEOUT)
    {
        Serial.print("Humidity: "); 
        Serial.print(humidity);
        Serial.println(" %"); 
    }
    else
    {
        Serial.println(DHT11::getErrorString(humidity));
    }

    // Attendez 1 seconde avant la prochaine lecture.
    delay(1000);
}
