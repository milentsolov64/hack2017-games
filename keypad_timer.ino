#include <Key.h>
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);


//KEYPAD Code
const int ROW_1 = 9;
const int ROW_2 = 8;
const int ROW_3 = 7;
const int ROW_4 = 6;
const int COL_1 = 5;
const int COL_2 = 4;
const int COL_3 = 3;
const int COL_4 = 2;
const byte COLS = 4;
const byte ROWS = 4;

const int ALARM = 12;
const int LED = 13;

char keys [COLS][ROWS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }

};

byte rowPins[ROWS] = { ROW_1, ROW_2, ROW_3, ROW_4 };
byte colPins[COLS] = { COL_1, COL_2, COL_3, COL_4 };

Keypad klav = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

String pass = "123A";
String pressedString = "";
int stringLength = 0;

int i = 0;
int minutes = 4;
int seconds = 60;

void setup() {
  // put your setup code here, to run once:
  pinMode(ALARM, OUTPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);

  lcd.begin (16, 2);
  lcd.setCursor(9, 0);
  lcd.print("io7g4SYv");

}

void loop() {
  // put your main code here, to run repeatedly:
  
  char pressedKey = klav.getKey();
  if (pressedKey) {
    Serial.println(pressedKey);
    lcd.setCursor(0,1);
    pressedString = pressedString + pressedKey;
    lcd.print(pressedString);
    stringLength++;
    if (stringLength == 4 && pressedString == pass) {
      digitalWrite(LED, HIGH);
      lcd.setCursor(0,1);
      lcd.print("CORRECT");
    }
    if (stringLength == 4 && pressedString != pass) {
      digitalWrite(ALARM, HIGH);
      lcd.setCursor(0,1);
      lcd.print("GAME OVER");
    }
  }

  unsigned long currentMillis = millis();
  if (currentMillis % 100 == 0 && i == 0) {
    if (minutes >= 0) {
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
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("GAME OVER");
    }
    i = 1;
  }
  else {
    if (currentMillis % 100 != 0 && i == 1) 
      i = 0;
  }
}
