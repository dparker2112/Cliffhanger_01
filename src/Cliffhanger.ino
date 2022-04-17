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

6)Sound track lose…losing sound, and music

7)Idle music.

********************************Electromagnetic triggers***************************************

An electromagnet creates a “start of game” sound when he crosses position one.

An electromagnet at the top of the mountain would trigger a sound effect - falling yodel sound

Perhaps another electromagnet could trigger red flashing lighting 
    and a sound effect that warns that the goat is going to fall off when it passes.
*/

byte stepPin = 22;                      //Stepper Motor Control
byte directionPin = 23;

                                        //Lectern Buttons
byte resetPin = 4;                      //Button #1
byte startPin = 5;                      //Button #2
byte space24Pin = 6;                    //Button #3                 
byte manualRunPin = 7;                  //Button #4
byte winningSoundPin = 8;               //Button #5
byte losingSoundPin = 9;                //Button #6
byte idleMusicPin = 10;                 //Button #7

                                        //Sound Trigger Pins -> Sound Board
byte fallSoundPin = 31;                 //pin 1 on sound board
byte yodelPin = 30;                     //pin 2 on sound board
byte dingSoundPin = 32;                 //pin 3 on sound board
byte winSoundPin = 33;                  //pin 4 on sound board
byte idlesoundPin = 34;                 //pin 5 on sound board

byte startlocationPin = 24;             //IR position Sensors
byte dangerlocationPin = 25;
byte fallPin = 26;
byte ledPin = 13;                       //Used for testing

boolean buttonCWpressed = false;        //Starting States
boolean buttonCCWpressed = false;
boolean fallpinActive = false;

unsigned long curMillis;
unsigned long prevStepMillis = 0;
unsigned long millisBetweenSteps = 5; // milliseconds

void setup() { 

     Serial.begin(9600);
     Serial.println("Starting Cliffhanger");
     
     pinMode(manualRunpin, INPUT_PULLUP);
     pinMode(buttonCCWpin, INPUT_PULLUP);
     pinMode(startlocationPin, INPUT_PULLUP);
     pinMode(fallPin, INPUT_PULLUP);

     pinMode(directionPin, OUTPUT);
     pinMode(stepPin, OUTPUT);
     pinMode(ledPin, OUTPUT);
     pinMode(yodelPin, OUTPUT);
     pinMode(fallsoundPin, OUTPUT);
     
}

void loop() { 
    
    curMillis = millis();
    readButtons();
    actOnButtons();
    readfallPin();
    playYodelSound();
    playFallSound();
}

void readButtons() {
    
    buttonCCWpressed = false;
    buttonCWpressed = false;
    
    if (digitalRead(manualRunpin) == LOW) {
        buttonCWpressed = true;
    }
    if (digitalRead(buttonCCWpin) == LOW) {
        buttonCCWpressed = true;
    }
}

void readfallPin() {

    fallpinActive = false;

    if (digitalRead(fallPin) == LOW) {
        fallpinActive = true;
    }
    if (digitalRead(fallPin) == HIGH) {
        fallpinActive = false;
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

void playfallSound() {

    if (fallpinActive == true) {
        digitalWrite(fallsoundPin, LOW);
    }
    if (fallpinActive == false) {
        digitalWrite(fallsoundPin, HIGH);
    }
}
