/* display

    CSE 132 - Assignment 7

    Fill this out so we know whose assignment this is.

    Name: Moises Daboin
    WUSTL Key: 473091

    Name:
    WUSTL Key:

*/

#include "font.h"

int row1 = 2;
int row2 = 3;
int row3 = 4;
int row4 = 5;
int row5 = 6;
int row6 = 7;
int row7 = 8;
int col1 = 9;
int col2 = 10;
int col3 = 11;
int col4 = 12;
int col5 = 13;
int but1 = A1;
int but2 = A2;
int count = -1;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
unsigned long secdebounceDelay = 50;
unsigned long seclastDebounceTime = 0;
int lastButtonState = LOW;
int buttonState;
int LEDState = HIGH;
int secButtonState;
int seclastButtonState = LOW;

void setup () {
  Serial.begin(9600);

  pinMode(row1, OUTPUT);
  pinMode(row2, OUTPUT);
  pinMode(row3, OUTPUT);
  pinMode(row4, OUTPUT);
  pinMode(row5, OUTPUT);
  pinMode(row6, OUTPUT);
  pinMode(row7, OUTPUT);
  pinMode(col1, OUTPUT);
  pinMode(col2, OUTPUT);
  pinMode(col3, OUTPUT);
  pinMode(col4, OUTPUT);
  pinMode(col5, OUTPUT);
  pinMode(but1, INPUT_PULLUP);
  pinMode(but2, INPUT_PULLUP);
  digitalWrite(col1, HIGH);
  digitalWrite(col2, HIGH);
  digitalWrite(col3, HIGH);
  digitalWrite(col4, HIGH);
  digitalWrite(col5, HIGH);
  digitalWrite(row1, LOW);
  digitalWrite(row2, LOW);
  digitalWrite(row3, LOW);
  digitalWrite(row4, LOW);
  digitalWrite(row5, LOW);
  digitalWrite(row6, LOW);
  digitalWrite(row7, LOW);
}

void loop () {
  //debounce? first one
  for (int i = 0; i < 7; ++i) {
    digitalWrite(i + 2, HIGH);
    for (int j = 0; j < 5; ++j) {
      boolean rowThing = font_5x7[count][j] & (0x02 << i);
      digitalWrite(9 + (5 - j - 1), !rowThing);
    }
    delay(3);
    digitalWrite(i + 2, LOW);
  }

  int reading = digitalRead(but1);
  int secReading = digitalRead(but2);
  if (reading != lastButtonState && secReading != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      LEDState = !LEDState;
      if (LEDState == true) {
        count = count + 1;
        if (count == 96) {
          count = 0;
        }
      }
    }
    if (reading != lastButtonState && secReading != lastButtonState) {
      lastDebounceTime = millis();
    }
  }
  lastButtonState = reading;
  
  if ((millis() - seclastDebounceTime) > secdebounceDelay) {
    if (secReading != secButtonState) {
      secButtonState = secReading;
      LEDState = !LEDState;
      if (LEDState == true) {
        count = count - 1;
        if(count < 0) {
          count = 95;
        }
      }
    }
  }
  seclastButtonState = secReading;
}
