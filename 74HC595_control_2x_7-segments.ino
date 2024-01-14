//https://github.com/pmiguelpinto90/ShiftDisplay
#include <ShiftDisplay2.h>

const byte pinLowerDisplay = 8;
const byte pinUpperDisplay = 9;


//Pin connected to ST_CP of 74HC595
int latchPin = 6;
//Pin connected to SH_CP of 74HC595
int clockPin = 7;
////Pin connected to DS of 74HC595
int dataPin = 5;
byte dataToTransfer = 0b10000000;//== Qh on MSBFIRST, Qa on LSBFIRST

ShiftDisplay2 display(COMMON_CATHODE, 1);

void setup() {
  pinMode(pinLowerDisplay, OUTPUT);
  pinMode(pinUpperDisplay, OUTPUT);

  digitalWrite(pinLowerDisplay, HIGH);
  digitalWrite(pinUpperDisplay, HIGH);

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  display.set("F");
  digitalWrite(pinLowerDisplay, LOW);
  display.update();
  digitalWrite(pinUpperDisplay, HIGH);
  delay(5);

  //Validate that shiftOut bitwise still works (need it for LEDs later)
  //display.set("A");
  digitalWrite(latchPin, LOW);
  //delay(500);
  shiftOut(dataPin, clockPin, LSBFIRST, dataToTransfer);
  
  digitalWrite(pinUpperDisplay, LOW);
  digitalWrite(latchPin, HIGH);
  //display.update();
  digitalWrite(pinLowerDisplay, HIGH);
  delay(1);
}
