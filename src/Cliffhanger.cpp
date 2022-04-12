#include <Arduino.h>
// Control for Cliffhanger game.  Made by David Parker nlightn0@gmail.com 04/01/2022

// this version uses millis() to manage timing rather than delay()
// and the movement is determined by a pair of momentary push switches
// press one and it turns CW, press the other and it turns CCW

byte stepPin = 22;
byte directionPin = 23;

byte buttonCWpin = 4;
byte buttonCCWpin = 5;

byte yodelPin = 30;
byte fallPin = 31;

byte startlocationPin = 24;
byte falllocationPin = 25;

boolean buttonCWpressed = false;
boolean buttonCCWpressed = false;

byte ledPin = 13;

unsigned long curMillis;
unsigned long prevStepMillis = 0;
unsigned long millisBetweenSteps = 5; // milliseconds

void setup() { 

     Serial.begin(9600);
     Serial.println("Starting Cliffhanger");

     pinMode(directionPin, OUTPUT);
     pinMode(stepPin, OUTPUT);
     pinMode(ledPin, OUTPUT);
     pinMode(yodelPin, OUTPUT);
     pinMode(fallPin, OUTPUT);
     
     pinMode(buttonCWpin, INPUT_PULLUP);
     pinMode(buttonCCWpin, INPUT_PULLUP);
     pinMode(startlocationPin, INPUT_PULLUP);
     pinMode(falllocationPin, INPUT_PULLUP);
     
}

void loop() { 
    
    curMillis = millis();
    readButtons();
    actOnButtons();
    playYodelSound();
    playFallSound();
}

void readButtons() {
    
    buttonCCWpressed = false;
    buttonCWpressed = false;
    
    if (digitalRead(buttonCWpin) == LOW) {
        buttonCWpressed = true;
    }
    if (digitalRead(buttonCCWpin) == LOW) {
        buttonCCWpressed = true;
    }
}

void actOnButtons() {
    if (buttonCWpressed == true) {
        digitalWrite(directionPin, HIGH);
        singleStep();
    }
    if (buttonCCWpressed == true) {
        digitalWrite(directionPin, LOW);
        singleStep();
    }
}

void singleStep() {
    if (curMillis - prevStepMillis >= millisBetweenSteps) {
            // next 2 lines changed 28 Nov 2018
        //prevStepMillis += millisBetweenSteps;
        prevStepMillis = curMillis;
        digitalWrite(stepPin, HIGH);
        digitalWrite(stepPin, LOW);
    }
}
void playYodelSound() {
    if (buttonCWpressed == false) {
        digitalWrite(yodelPin, HIGH);
    }
    if (buttonCWpressed == true) {
        digitalWrite(yodelPin, LOW);
    }
}
void playFallSound() {
    if (buttonCWpressed == false) {
        digitalWrite(fallPin, HIGH);
    }
    if (buttonCWpressed == true) {
        digitalWrite(fallPin, HIGH);
    }
}