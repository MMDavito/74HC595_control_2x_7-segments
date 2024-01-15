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
  Serial.begin(9600);
  Serial.println("SETUP");
  pinMode(pinLowerDisplay, OUTPUT);
  pinMode(pinUpperDisplay, OUTPUT);

  digitalWrite(pinLowerDisplay, HIGH);
  digitalWrite(pinUpperDisplay, HIGH);

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {

  byte b_char = 'A';
  for (int i = 0; i < 10; i++) {
    //Serial.println(i);
    char temp = b_char;
    //Serial.println(temp);
    long start = millis();

    while (millis() - start < 1000)
    {
      display.set(i);
      digitalWrite(pinLowerDisplay, LOW);
      //Disable lower display, then shift/latch the shift-register to new value and enable upper:
      display.update();
      digitalWrite(pinUpperDisplay, HIGH);
      delay(5);


      //ground latchPin and hold low for as long as you are transmitting

      display.set(temp);
      //Disable upper display, then shift/latch the shift-register to new value and enable lower:
      digitalWrite(pinUpperDisplay, LOW);
      display.update();
      digitalWrite(pinLowerDisplay, HIGH);
      delay(4);
    }
    b_char += 1;
  }
}
