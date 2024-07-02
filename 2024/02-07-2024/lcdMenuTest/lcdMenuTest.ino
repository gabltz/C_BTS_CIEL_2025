#include <LiquidCrystal.h>

// Initialisation des broches du LCD
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// Définir les messages du menu
const char* messages[] = {
  "Message 1: Bonjour!",
  "Message 2: Bienvenue",
  "Message 3: Arduino",
  "Message 4: Menu"
};

int numMessages = sizeof(messages) / sizeof(messages[0]);
int currentMessage = 0;

void setup() {
  // Initialiser l'écran LCD
  lcd.begin(16, 2);
  lcd.print("LCD Keypad Menu");

  // Afficher le premier message
  lcd.setCursor(0, 1);
  lcd.print(messages[currentMessage]);
}

void loop() {
  int button = read_LCD_buttons();

  // Vérifier quel bouton est appuyé
  if (button == btnRIGHT) {
    currentMessage++;
    if (currentMessage >= numMessages) {
      currentMessage = 0;
    }
    displayMessage();
  } else if (button == btnLEFT) {
    currentMessage--;
    if (currentMessage < 0) {
      currentMessage = numMessages - 1;
    }
    displayMessage();
  }

  delay(200); // Anti-rebond pour les boutons
}

void displayMessage() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LCD Keypad Menu");
  lcd.setCursor(0, 1);
  lcd.print(messages[currentMessage]);
}

// Définir les valeurs de retour des boutons
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

int read_LCD_buttons() {
  int adc_key_in = analogRead(0);   // Lire la valeur ADC sur A0

  // La valeur de retour varie en fonction de la pression du bouton
  if (adc_key_in > 1000) return btnNONE;
  if (adc_key_in < 50)   return btnRIGHT;
  if (adc_key_in < 195)  return btnUP;
  if (adc_key_in < 380)  return btnDOWN;
  if (adc_key_in < 555)  return btnLEFT;
  if (adc_key_in < 790)  return btnSELECT;

  return btnNONE;
}