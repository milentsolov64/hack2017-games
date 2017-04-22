#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup()
{
  lcd.begin (16, 2);
  lcd.setCursor(9,0);
  lcd.print("io7g4SYv");
}

int i = 0;
int minutes = 4;
int seconds = 60;
void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis();
  if (currentMillis % 1000 == 0 && i == 0) {
    if (minutes > 0) {
      seconds = seconds - 1;
      if ( seconds == 0) {
        minutes--;
        seconds = 59;
      }
      if (seconds >= 10) {
        lcd.setCursor ( 0, 0 );
        lcd.print("0");
        lcd.setCursor ( 1, 0 );
        lcd.print(minutes);
        lcd.setCursor ( 2, 0 );
        lcd.print(":");
        lcd.setCursor ( 3, 0 );
        lcd.print(seconds);
      }
      else {
        lcd.setCursor ( 0, 0 );
        lcd.print("0");
        lcd.setCursor ( 1, 0 );
        lcd.print(minutes);
        lcd.setCursor ( 2, 0 );
        lcd.print(":");
        lcd.setCursor ( 3, 0 );
        lcd.print("0");
        lcd.setCursor ( 4, 0 );

        lcd.print(seconds);
      }

    
  }
  else {
    Serial.println("GAME OVER");
  }
  i = 1;
}
else {
  if (currentMillis % 1000 != 0 && i == 1) i = 0;
}

}
