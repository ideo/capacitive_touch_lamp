// https://github.com/wayoda/LedControl
#include "LedControl.h"

// easier to remember inputs as pads, not pin numbers
int PADC = 10;
int PAD1 = 11;
int PAD2 = 12;
int PAD3 = 13;
int PAD4 = 9;
int PAD5 = 8;
int PAD6 = 7;
int PAD7 = 6;
int PAD8 = 5;

// communication lines for MAX72XX
int LCDATA = 2;
int LCLOAD = 3;
int LCCLK = 4;

// LedControl library is used to control MAX727
LedControl lc=LedControl(LCDATA,LCCLK,LCLOAD,1);

void setup() {
  Serial.begin(9600);

  pinMode(PADC, INPUT); // set PADC to input
  pinMode(PAD1, INPUT); // set PAD1 to input
  pinMode(PAD2, INPUT); // set PAD2 to input
  pinMode(PAD3, INPUT); // set PAD3 to input
  pinMode(PAD4, INPUT); // set PAD3 to input
  pinMode(PAD5, INPUT); // set PAD3 to input
  pinMode(PAD6, INPUT); // set PAD3 to input
  pinMode(PAD7, INPUT); // set PAD3 to input
  pinMode(PAD8, INPUT); // set PAD3 to input

  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,15);
  /* and clear the display */
  lc.clearDisplay(0);
}

void loop() {
  // MAX72XX accepts binary LED controls, so only add LEDs to turn on
  byte row0 = B00000000;
  byte row1 = B00000000;
  byte row2 = B00000000;
  byte row3 = B00000000;

  // listen for any capacitive touch events and control LEDs accordingly
  if (digitalRead(PADC)) {
    row0 = B11110000;
    row1 = B11110000;
    row2 = B11110000;
    row3 = B11110000;
  }
  if (digitalRead(PAD1)) {
    row2 += B11000000;
  }
  if (digitalRead(PAD2)) {
    row2 += B00110000;
  }
  if (digitalRead(PAD3)) {
    row3 += B00110000;
  }
  if (digitalRead(PAD4)) {
    row3 += B11000000;
  }
  if (digitalRead(PAD5)) {
    row1 += B00110000;
  }
  if (digitalRead(PAD6)) {
    row1 += B11000000;
  }
  if (digitalRead(PAD7)) {
    row0 += B11000000;
  }
  if (digitalRead(PAD8)) {
    row0 += B00110000;
  }

  // turn LEDs on or off depending on what's touched
  lc.setRow(0,0,row0);
  lc.setRow(0,1,row1);
  lc.setRow(0,2,row2);
  lc.setRow(0,3,row3);
}
