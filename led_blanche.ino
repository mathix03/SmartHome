// Déclaration des broches
int pinLED = 0;     
int pinBouton = 3;  
int allumer = 0;

void setup() {
  // Configuration des broches
  pinMode(pinLED, OUTPUT);      
  pinMode(pinBouton, INPUT);   
  digitalWrite(pinLED, LOW);
}

void loop() {

  int etatBouton = digitalRead(pinBouton);

  if (etatBouton == LOW) {
    if(allumer == LOW){
      allumer = HIGH;
    }
    else{
      allumer = LOW;
    }
  }
  digitalWrite(pinLED, allumer);

  delay(500);
}
