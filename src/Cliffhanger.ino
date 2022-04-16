#include <Arduino.h>

// Control for Cliffhanger game.  Made by David Parker nlightn0@gmail.com 04/01/2022

/*
*******************************Overview of button behaviors*************************************

1)Resets game to start position moves goat to starting position. No sound. 

2)Start button: Random goat move 1-12 spaces along the track. Each move different. 
    Beginning yodel to start, then Traveling music track plays during movement. 
    When the figure stops, a bell “DING”

3)Go directly to space #24. Beginning yodel to start, then plays music while it travels 
    and when the figure stops a bell “Ding”

4)Manual run. Beginning yodel to start, character moves until host 
    takes finger off button then the stop DING

5)Sound track win..play sound ding ding ding ding and winning music

6)Sound track loose…losing sound, and music

7)Idle music.

********************************Electromagnetic triggers***************************************

An electromagnet creates a “start of game” sound when he crosses position one.

An electromagnet at the top of the mountain would trigger a sound effect - falling yodel sound

Perhaps another electromagnet could trigger red flashing lighting 
    and a sound effect that warns that the goat is going to fall off when it passes.
*/

byte stepPin = 22;
byte directionPin = 23;

byte buttonCWpin = 4;
byte buttonCCWpin = 5;

byte yodelPin = 30;
byte fallPin = 31;

byte startlocationPin = 24;
byte dangerlocationPin = 25;
byte falllocationPin = 26;

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