// Déclaration des pins
const int pinCapteurMouvement = 11;
const int pinLedJaune = 8;

void setup() {
  // Initialisation du capteur de mouvement en entrée
  pinMode(pinCapteurMouvement, INPUT);
  
  // Initialisation de la LED en sortie
  pinMode(pinLedJaune, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // Lire l'état du capteur de mouvement
  int mouvementDetecte = digitalRead(pinCapteurMouvement);

  if (mouvementDetecte == HIGH) {
    // Allumer la LED
    digitalWrite(pinLedJaune, HIGH);
    Serial.println("Mouvement détecté !");
  } else {
    // Éteindre la LED
    digitalWrite(pinLedJaune, LOW);
  }

  // Petite pause pour éviter les rebonds
  delay(100);
}
