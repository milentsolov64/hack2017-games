#include "SevSeg.h"
SevSeg sevseg;
SevSeg sevseg2;

void setup() {
  byte numDigits = 2;
  byte digitPins[] = {9, 7};
  byte digitPins2[] = {A1, 10, A1};
  byte segmentPins[] = {12, 8, 5, 3, 2, 11, 6};
  Serial.begin(9600);
  sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(100);

  sevseg2.begin(COMMON_ANODE, numDigits, digitPins2, segmentPins);
  sevseg2.setBrightness(100);
}

void loop() {
  static unsigned long timer = millis();
  static int s = 10;
  static int m = 0;
  sevseg.setNumber(s, 1);
  sevseg2.setNumber(m, 2);
  while (millis() >= timer) {

    s--;
    timer = timer + 1000;
    if (s == 0)
    {
      if (m == 0)
      {
        timer = 0;
      }
      else
      {
        m = m - 1;
        s = 59;
      }
    }

  }
  sevseg.refreshDisplay();
  sevseg2.refreshDisplay();
}

/// END ///
