#include <LCD-I2C.h>
#include <Wire.h>

LCD_I2C lcd(0x27, 16, 2); // Default address of most PCF8574 modules, change according
String mymessage = "Bonjour ! ";
int currentLoop = 0;
int result = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(7, INPUT);
  Serial.begin(9600);

  Wire.begin();
      lcd.begin(&Wire);
      lcd.display();
      lcd.backlight();
}

void loop() {
  // put your main code here, to run repeatedly:


  result = digitalRead(7);

if(result == 1 ){
  mymessage = mymessage.substring(1, mymessage.length()) + mymessage[0];
  currentLoop++;
  lcd.clear();
    lcd.print(mymessage); // You can make spaces using well... spaces
        lcd.setCursor(5, 1); // Or setting the cursor in the desired position.
        lcd.print("World!");
      
}
delay(50);



  

}
