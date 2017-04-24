#include <Key.h>
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inicializa///////////
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);


int keypadTrue = 0;
int potsTrue = 0;
int simeonTrue = 0;
int buttonDigitTrue = 0;
int wireTrue = 0;
int morseTrue = 0;
int alarmTrue = 0;


//KEYPAD Code/////////////////
const int ROW_1 = 22;
const int ROW_2 = 24;
const int ROW_3 = 26;
const int ROW_4 = 28;
const int COL_1 = 23;
const int COL_2 = 25;
const int COL_3 = 27;
const int COL_4 = 29;
const byte COLS = 4;
const byte ROWS = 4;

const int ALARM = 12;
const int LED_Keypad = 51;

char keys [COLS][ROWS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }

};

byte rowPins[ROWS] = { ROW_1, ROW_2, ROW_3, ROW_4 };
byte colPins[COLS] = { COL_1, COL_2, COL_3, COL_4 };

Keypad klav = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

String pass = "086A";
String pressedString = "";
int stringLength = 0;

int intervalKeypad = 1000;
unsigned long previousMillisKeypad = 0;


int minutes = 4;
int seconds = 60;

//POTS
int potsGOTOV = 0;
const int pot1 = A0;
const int pot2 = A1;
const int pot3 = A2;
const int ledPots = 49;
const int st1 = 300;
const int st2 = 600;
const int st3 = 400;
int state4 = 0;
int seconds2 = 0;
unsigned long previousMillisPots = 0;
int intervalPots = 1000;

//SIMEON//////////////////////////

const int button1 = 30;
const int button2 = 32;
const int button3 = 34;
const int button4 = 36;
const int button5 = 38;
const int LED1 = 40;
const int LED2 = 42;
const int LED3 = 44;
const int LED4 = 46;
String sequence = "abcb";
String entered = "";
int flag = 0;
int flag1 = 0;
int flag2 = 0;
int flag3 = 0;
int flag4 = 0;
int ledSimeon = 47;

////////BUTTON DIGITS/////////////////////
int digitButton = 31;
int ledDigitButton = 45;
int buttonStateDigit;
int digit1;
int digit2;

////////MORSE////////////
int piezo = 11;
int ledMorse = 43;
int onoff2 = 35;
int onoff3 = 37;
int onoff4 = 39;
int buttonState2Morse = 0;
int buttonState3Morse = 0;
int buttonState4Morse = 0;
bool flag1Morse;
bool flag2Morse;
bool flag3Morse;
bool flag4Morse;
int intervalMorse = 500;
unsigned long previousMillisMorse = 0;
int count = 0;

////////JICI////////

bool jica = 0;              // easy integration
const int Wire1Pin = 7;     // the number of the Wire pin
const int Wire2Pin = 6;     // the number of the Wire pin
const int Wire3Pin = 5;     // the number of the Wire pin
const int Wire4Pin = 4;     // the number of the Wire pin
const int Wire5Pin = 3;     // the number of the Wire pin
const int Wire6Pin = 2;     // the number of the Wire pin
const int ledJici = 41;      // if the module is done

int Wire_State1 = 0;         // variable for reading the Wire status
int Wire_State2 = 0;         // variable for reading the Wire status
int Wire_State3 = 0;         // variable for reading the Wire status
int Wire_State4 = 0;         // variable for reading the Wire status
int Wire_State5 = 0;         // variable for reading the Wire status
int Wire_State6 = 0;         // variable for reading the Wire status

void setup() {
  // KEYPAD
  pinMode(ALARM, OUTPUT);
  pinMode(LED_Keypad, OUTPUT);
  Serial.begin(9600);
  ////////POTS/////
  pinMode(ledPots, OUTPUT);
  pinMode(pot1, INPUT);
  pinMode(pot2, INPUT);
  pinMode(pot3, INPUT);

  lcd.begin (16, 2);
  lcd.setCursor(9, 0);
  lcd.print("io7g4SYv");
  //////////SIMEON////////
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  pinMode(button5, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(ledSimeon, OUTPUT);

  /////////////DIGIT BUTTON/////
  pinMode(digitButton, INPUT);
  pinMode(ledDigitButton, OUTPUT);
  digitalWrite(ledDigitButton, LOW);
  digitalWrite(ALARM, LOW);

  ////////MORSE////////
  pinMode(piezo, OUTPUT);
  pinMode(onoff2, INPUT);
  pinMode(onoff3, INPUT);
  pinMode(onoff4, INPUT);

  //////////////////JICI////////////////
  pinMode(Wire1Pin, INPUT);
  pinMode(Wire2Pin, INPUT);
  pinMode(Wire3Pin, INPUT);
  pinMode(Wire4Pin, INPUT);
  pinMode(Wire5Pin, INPUT);
  pinMode(Wire6Pin, INPUT);


}

void loop() {
  if (alarmTrue == 0) {
    // put your main code here, to run repeatedly:
    //////////////KEYPAD//////////////
    char pressedKey = klav.getKey();
    if (pressedKey) {
      ////Serial.println(pressedKey);
      lcd.setCursor(0, 1);
      pressedString = pressedString + pressedKey;
      lcd.print(pressedString);
      stringLength++;
      if (stringLength == 4 && pressedString == pass) {
        digitalWrite(LED_Keypad, HIGH);
        lcd.setCursor(0, 1);
        lcd.print("CORRECT");
        keypadTrue = 1;
      }
      if (stringLength == 4 && pressedString != pass && keypadTrue == 0) {
        digitalWrite(ALARM, HIGH);
        lcd.setCursor(0, 1);
        lcd.print("GAME OVER");
        alarmTrue = 1;
      }
    }
    ////////////////TIMER//////////////////
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillisKeypad >= intervalKeypad) {
      previousMillisKeypad = currentMillis;
      //////Serial.println("neshto");
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
        lcd.setCursor(0, 0);
        lcd.print("GAME OVER");
        alarmTrue = 1;
      }

    }

    //POTS
    //pot1 = 300
    //pot2 = 600
    //pot3 = 400
    int state1 = analogRead(pot1);
    int state2 = analogRead(pot2);
    int state3 = analogRead(pot3);
  Serial.print(state1);
  Serial.print(" ");
  Serial.print(state2);
  Serial.print(" ");
  Serial.print(state3);
  Serial.print(" ");
  Serial.print(seconds2);
  Serial.print(" ");
    ////Serial.println();
    if (state1 > 5 || state2 > 5 || state3 > 5 || state4 != 0) {
      state4 = 1;

      if (currentMillis - previousMillisPots >= intervalPots) {
        previousMillisPots = currentMillis;
        seconds2++;
      }

      if (seconds2 < 45) {
        if ( state1 > 290 && state1 < 310) {
          if ( state2 > 590 && state2 < 610) {
            if ( state3 > 790 && state3 < 810) {
              digitalWrite(ledPots, HIGH);
              potsGOTOV = 1;
              potsTrue = 1;
            }
          }

        }
      }
      if (seconds2 >= 45   && potsGOTOV == 0 && potsTrue == 0) {
        digitalWrite(ALARM, HIGH);
        alarmTrue = 1;
      }
    }


    ///////SIMEON////////
    int buttonState1 = digitalRead(button1);
    int buttonState2 = digitalRead(button2);
    int buttonState3 = digitalRead(button3);
    int buttonState4 = digitalRead(button4);
    int buttonState5 = digitalRead(button5);

    if (buttonState1 == HIGH && flag1 == 0) {
      entered = entered + "a";
      flag1 = 1;
      flag2 = 0;
      flag3 = 0;
      flag4 = 0;
    }
    if (buttonState2 == HIGH && flag2 == 0) {
      entered = entered + "b";
      flag1 = 0;
      flag2 = 1;
      flag3 = 0;
      flag4 = 0;
    }
    if (buttonState3 == HIGH && flag3 == 0) {
      entered = entered + "c";
      flag1 = 0;
      flag2 = 0;
      flag3 = 1;
      flag4 = 0;
    }
    if (buttonState4 == HIGH && flag4 == 0) {
      entered = entered + "d";
      flag1 = 0;
      flag2 = 0;
      flag3 = 0;
      flag4 = 1;
    }

    if (buttonState5 == HIGH && flag == 0) {
      flag = 1;
      digitalWrite(LED1, HIGH);
      delay(500);
      digitalWrite(LED1, LOW);
      delay(500);
      digitalWrite(LED2, HIGH);
      delay(500);
      digitalWrite(LED2, LOW);
      delay(500);
      digitalWrite(LED3, HIGH);
      delay(500);
      digitalWrite(LED3, LOW);
      delay(500);
      digitalWrite(LED2, HIGH);
      delay(500);
      digitalWrite(LED2, LOW);
      delay(500);
    }
    int enteredSize = entered.length();
    ////Serial.println(enteredSize);
    if (enteredSize == 4) {
      ////Serial.println("AAAAAAAAAAAAAAAAAAAAAAA");
      if (entered == sequence) {
        digitalWrite(ledSimeon, HIGH);
        ////Serial.println("GOOD");
        simeonTrue == 0;
      }
      else {
        digitalWrite(ALARM, HIGH);
        ////Serial.println("BAAD");
        alarmTrue = 1;
      }
    }
    ////Serial.println(entered);

    //////////BUTTON DIGIT////////

    buttonStateDigit = digitalRead(digitButton);
    digit1 = seconds % 10;
    digit2 = seconds / 10;
    Serial.print(digit1);
    Serial.print(digit2);
    if (buttonStateDigit == 1 && (digit1 == 5 or digit2 == 5)) {
      digitalWrite(ledDigitButton, HIGH);
      buttonDigitTrue = 1;
      Serial.print("DIIGGGGGGGGGGGGGGGGGGGGGGGGIT");
    } else {
      if (buttonStateDigit == 1 && (digit1 != 5 || digit2 != 5)) {
        digitalWrite(ALARM, HIGH);
        alarmTrue = 1;
        Serial.print("DDDDDDDDDDDDDDDDDDDDDDDDDDDIIIIIGIT");
      }
    }

    ///////////MORSE////////

    if (currentMillis - previousMillisMorse >= intervalMorse) {
      previousMillisMorse = currentMillis;

      count++;
      if (count == 1) digitalWrite(piezo, HIGH);
      if (count == 2) digitalWrite(piezo, HIGH);
      if (count == 3) digitalWrite(piezo, LOW);
      if (count == 4) digitalWrite(piezo, HIGH);
      if (count == 5) digitalWrite(piezo, LOW);
      if (count == 6) digitalWrite(piezo, HIGH);
      if (count == 7) digitalWrite(piezo, LOW);
      if (count == 8) digitalWrite(piezo, HIGH);
      if (count == 9) digitalWrite(piezo, LOW);
      if (count == 10) digitalWrite(piezo, HIGH);
      if (count == 11) digitalWrite(piezo, LOW);
      if (count == 12) digitalWrite(piezo, LOW);
      if (count == 13) digitalWrite(piezo, LOW);
      if (count == 14) digitalWrite(piezo, LOW);
      if (count >= 15) count = 0;

    }

    buttonState2Morse = digitalRead(onoff2);
    buttonState3Morse = digitalRead(onoff3);
    buttonState4Morse = digitalRead(onoff4);

    Serial.print("    ");
    Serial.print(buttonState2Morse);
    Serial.print(" ");
    Serial.print(buttonState3Morse);
    Serial.print(" ");
    Serial.print(buttonState4Morse);
    Serial.print(" ");
    Serial.println();


    if (buttonState2Morse == HIGH && buttonState3Morse == HIGH) {
      digitalWrite(ledMorse, HIGH);
      digitalWrite(piezo, LOW);
      morseTrue = 1;
      Serial.println("MOOOOOOOOOOOOOOOOOOOOOOORSE");
    }
    else if ( buttonState4Morse == HIGH ) {
      digitalWrite(ALARM, HIGH);
      Serial.println("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMOORSE");
      alarmTrue = 1;
    }


    ////////////////JICI//////////////////

    // read the state of the Wire value:
    Wire_State1 = digitalRead(Wire1Pin);
    Wire_State2 = digitalRead(Wire2Pin);
    Wire_State3 = digitalRead(Wire3Pin);
    Wire_State4 = digitalRead(Wire4Pin);
    Wire_State5 = digitalRead(Wire5Pin);
    Wire_State6 = digitalRead(Wire6Pin);
    /*
      Serial.print(Wire_State1);
      Serial.print(" ");
      Serial.print(Wire_State2);
      Serial.print(" ");
      Serial.print(Wire_State3);
      Serial.print(" ");
      Serial.print(Wire_State4);
      Serial.print(" ");
      Serial.print(Wire_State5);
      Serial.print(" ");
      Serial.print(Wire_State6);
      Serial.println();*/

    // check if the Wire is pressed.
    // if it is, the buttonState is HIGH:
    if (Wire_State3 == LOW && Wire_State5 == LOW) {
      // turn LED on:
      digitalWrite(ledJici, HIGH);
      ////Serial.println("JIIIIIIIICCCCCCCCCCCCCIIIIIIII");
      jica = 1;
      wireTrue = 1;
    }

    if (Wire_State2 == LOW && jica == 0) {
      // turn alarm on:
      digitalWrite(ALARM, HIGH);
      alarmTrue = 1;
      ////Serial.println("JJJJJJJJJJJJJJJJJJJIIIIICCCIIIIII");
    }
    if (Wire_State4 == LOW && jica == 0) {
      // turn alarm on:
      digitalWrite(ALARM, HIGH);
      alarmTrue = 1;
      ////Serial.println("JJJJJJJJJJJJJJJJJJJIIIIICCCIIIIII");
    }
    if (Wire_State6 == LOW && jica == 0) {
      // turn alarm on:
      digitalWrite(ALARM, HIGH);
      alarmTrue = 1;
      //Serial.println("JJJJJJJJJJJJJJJJJJJIIIIICCCIIIIII");
    }

    if (keypadTrue == 1 && potsTrue == 1 && simeonTrue == 1 && buttonDigitTrue == 1 && wireTrue == 1 && buttonDigitTrue == 1) {
      lcd.clear();
      lcd.setCursor(0, 7);
      lcd.print("GG");
      lcd.setCursor(1, 1);
      lcd.print("WELL PLAYED!");



    }
  }
  else {
    lcd.clear();
    lcd.setCursor(0, 7);
    lcd.print("GG");
    lcd.setCursor(1, 2);
    lcd.print("SORRY BRO :(");
    digitalWrite(piezo, HIGH);
  }
}
