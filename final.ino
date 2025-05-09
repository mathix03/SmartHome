#include <LCD-I2C.h>
#include <Wire.h>

// Écran LCD
LCD_I2C lcd(0x27, 16, 2);
String mymessage = "bienvenu a";

// Pins
const int pinLED = 13;               // LED rouge
const int pinBouton = 3;             // Bouton LED rouge
const int pinEcran = 7;              // Bouton écran LCD
const int pinCapteurMouvement = 11;   // Capteur PIR
const int pinLedJaune = 8;          // LED jaune (mouvement)

// États
bool allumer = false;
bool ecranAffiche = false;
unsigned long lastButtonPress = 0;
int mouvementDetecte = LOW;

//////////////////// Setup ////////////////////
void setup() {
  Serial.begin(9600);

  ecran_setup();
  LedB_setup();
  moove_setup();
}

//////////////////// Loop ////////////////////
void loop() {
  ecran_loop();
  LedB_loop();
  moove_loop();
}

//////////////////// LED et bouton ////////////////////
void LedB_setup() {
  pinMode(pinLED, OUTPUT);
  pinMode(pinBouton, INPUT);
  digitalWrite(pinLED, LOW);
}

void LedB_loop() {
  int etatBouton = digitalRead(pinBouton);

  // Anti-rebond simple
  if (etatBouton == LOW && (millis() - lastButtonPress) > 500) {
    lastButtonPress = millis();
    allumer = !allumer;
    digitalWrite(pinLED, allumer);
  }
}

//////////////////// Écran LCD ////////////////////
void ecran_setup() {
  pinMode(pinEcran, INPUT);

  Wire.begin();
  lcd.begin(&Wire);
  lcd.display();
  lcd.backlight();
  lcd.clear();
}

void ecran_loop() {
  int boutonEtat = digitalRead(pinEcran);

  if (boutonEtat == LOW && !ecranAffiche) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(mymessage);
    lcd.setCursor(3, 1);
    lcd.print("la maison");
    ecranAffiche = true;
    lastButtonPress = millis();
  }

  if (ecranAffiche && (millis() - lastButtonPress) > 10000) {
    lcd.clear();
    ecranAffiche = false;
  }
}

//////////////////// Capteur de mouvement ////////////////////
void moove_setup() {
  pinMode(pinCapteurMouvement, INPUT); // ou INPUT_PULLUP selon ton capteur
  pinMode(pinLedJaune, OUTPUT);
  digitalWrite(pinLedJaune, LOW);
}

void moove_loop() {
  mouvementDetecte = digitalRead(pinCapteurMouvement);

  if (mouvementDetecte == HIGH) {
    digitalWrite(pinLedJaune, HIGH);
    Serial.println("Mouvement détecté !");
  } else {
    digitalWrite(pinLedJaune, LOW);
  }

  // Pour déboguer : afficher la valeur brute du capteur
  Serial.print("Valeur capteur : ");
  Serial.println(mouvementDetecte);

  delay(50); // Anti-bruit
}
