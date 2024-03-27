#include <SPI.h>
#include <MFRC522.h>

/*
Titre : RFID TEST OUVERTURE
Descrition: Permet de lire des badge (Badge rond et carré défini au debut) si les badges sont passé dans l'ordre R C R R C on peut sortir, sinon on reste enfermé
Noms : Lylou BALLAND & Léane MOUGIN
Date création : 16/01/24
Date dernière modif: 16/01/24
*/

#define SS_PIN 10  // Broche du Slave Select (SS) du module RC522
#define RST_PIN 9  // Broche de reset du module RC522

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600); // Initialiser la communication série
  SPI.begin();        // Initialiser la communication SPI
  mfrc522.PCD_Init(); // Initialiser le module RC522
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

  Serial.println("Approchez un badge RFID pour le lire...");
}

// Faire les tests pour avoir la suite R C R R C  --------------------------------------------------------------------------------------------------------

byte carreID[] = {0x60, 0x7D, 0x73, 0x30};
byte rondID[] = {0x5A, 0x88, 0x92, 0x7F};
int sequence[] = {1, 0, 1, 1, 0}; // 1 pour rond, 0 pour carré
int sequenceIndex = 0;

void loop() {
  // Vérifier la présence d'un badge RFID --------------------------------------------------------------------------------------------------------
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    Serial.print("ID du badge RFID : ");

    // Afficher l'identifiant du badge --------------------------------------------------------------------------------------------------------
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
    }

    // Vérifier si l'ID correspond à celui du badge carré --------------------------------------------------------------------------------------------------------
    if (compareID(mfrc522.uid.uidByte, carreID)) {
      Serial.println("\nBadge Carré");
    }
    // Vérifier si l'ID correspond à celui du badge rond --------------------------------------------------------------------------------------------------------
    else if (compareID(mfrc522.uid.uidByte, rondID)) {
      Serial.println("\nBadge Rond");
    } else {
      Serial.println("\nBadge Inconnu");
    }
    // Vérifier si l'ID correspond à celui de la séquence actuelle --------------------------------------------------------------------------------------------------------
    if (compareID(mfrc522.uid.uidByte, sequence[sequenceIndex] == 1 ? rondID : carreID)) {
      Serial.println("\n Ordre Correct");

      // Passer à la prochaine étape de la séquence --------------------------------------------------------------------------------------------------------
      sequenceIndex++;

      // Si la séquence est complète, afficher le message approprié  --------------------------------------------------------------------------------------------------------
      if (sequenceIndex == 5) {
          digitalWrite(8, HIGH);
          delay(2000); // Wait for 2000 millisecond(s)
          digitalWrite(8, LOW);
        Serial.println("\n Vous pouvez sortir ! \n");
        sequenceIndex = 0; // Réinitialiser la séquence
      }
    } else {
        digitalWrite(7, HIGH);
        delay(2000); // Wait for 2000 millisecond(s)
        digitalWrite(7, LOW);
      Serial.println("\n Ordre Incorrect");
      sequenceIndex = 0; // Réinitialiser la séquence en cas de badge incorrect
    }
    delay(1000); // Délai pour éviter la détection continue du même badge
  }

  mfrc522.PICC_HaltA(); // Arrêter la communication avec le badge actuel
  mfrc522.PCD_StopCrypto1(); // Arrêter le chiffrement
}

// Fonction pour comparer deux tableaux d'octets (byte) --------------------------------------------------------------------------------------------------------
bool compareID(byte* ID1, byte* ID2) {
  for (int i = 0; i < 4; i++) {
    if (ID1[i] != ID2[i]) {
      return false; // Les ID ne correspondent pas
    }
  }
  return true; // Les ID correspondent
}
