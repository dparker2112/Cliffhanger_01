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
byte winningPin = 8;                    //Button #5
byte losingPin = 9;                     //Button #6
byte idleMusicPin = 10;                 //Button #7

                                        //Sound Trigger Pins -> Sound Board
byte yodelSoundPin = 30;                //pin 1 on sound board
byte fallSoundPin = 31;                 //pin 2 on sound board
byte dingSoundPin = 32;                 //pin 3 on sound board
byte winSoundPin = 33;                  //pin 4 on sound board
byte loseSoundPin = 34;                 //pin 5 on sound board
byte idleSoundPin = 35;                 //pin 6 on sound board
byte dangerSoundPin = 36;               //pin 7 on sound board

byte startlocationPin = 24;             //IR position Sensors
byte dangerlocationPin = 25;
byte fallPin = 26;
byte ledPin = 13;                       //Used for testing

boolean buttonCWpressed = false;        //Starting States
boolean buttonCCWpressed = false;
boolean fallpinActive = false;
boolean winSoundPlaying = false;
boolean loseSoundPlaying = false;
boolean idleSoundPlaying = false;

unsigned long curMillis;
unsigned long prevStepMillis = 0;
unsigned long millisBetweenSteps = 5;   // milliseconds

void setup() { 

     Serial.begin(9600);
     Serial.println("Starting Cliffhanger");
     
     pinMode(resetPin, INPUT_PULLUP);
     pinMode(startPin, INPUT_PULLUP);
     pinMode(space24Pin, INPUT_PULLUP);
     pinMode(manualRunPin, INPUT_PULLUP);
     pinMode(winningPin, INPUT_PULLUP);
     pinMode(losingPin, INPUT_PULLUP);
     pinMode(idleMusicPin, INPUT_PULLUP);

     pinMode(startlocationPin, INPUT_PULLUP);
     pinMode(dangerlocationPin, INPUT_PULLUP);
     pinMode(fallPin, INPUT_PULLUP);

     pinMode(directionPin, OUTPUT);
     pinMode(stepPin, OUTPUT);
     pinMode(ledPin, OUTPUT);
     pinMode(yodelSoundPin, OUTPUT);
     pinMode(fallSoundPin, OUTPUT);
     pinMode(dingSoundPin, OUTPUT);
     pinMode(winSoundPin, OUTPUT);
     pinMode(loseSoundPin, OUTPUT);
     pinMode(idleSoundPin, OUTPUT);
     pinMode(dangerSoundPin, OUTPUT);
     pinMode(ledPin, OUTPUT);
     
}

void loop() { 
    
    curMillis = millis();
    readButtons();
    actOnButtons();
    readSensors();
    actOnSensors();
    playYodelSound();
    playFallSound();
    playWinSound();
    playLoseSound();
    playIdleSound();
}

void readButtons() {
    
    buttonCCWpressed = false;
    buttonCWpressed = false;
    winSoundPlaying = false;
    loseSoundPlaying = false;
    idleSoundPlaying = false;
    
    if (digitalRead(resetPin) == LOW) {
        buttonCCWpressed = true;
    }
    if (digitalRead(startPin) == LOW) {
        buttonCWpressed = true;
    }
    if (digitalRead(space24Pin) == LOW) {
        buttonCWpressed = true;
    }
    if (digitalRead(manualRunPin) == LOW) {
        buttonCWpressed = true;
    }
    if (digitalRead(winningPin) == LOW) {
        winSoundPlaying = true;
    }
    if (digitalRead(losingPin) == LOW) {
        loseSoundPlaying = true;
    }
    if (digitalRead(idleMusicPin) == LOW) {
        idleSoundPlaying = true;
    }
}

void readSensors() {

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
    if (winSoundPlaying == true) {
        playWinSound();
    }
    if (loseSoundPlaying == true) {
        playLoseSound();
    }
    if (idleSoundPlaying == true) {
        playIdleSound();
    }
}
void actOnSensors() {
    if (fallpinActive == true) {
        playFallSound();
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
        digitalWrite(yodelSoundPin, HIGH);
    }
    if (buttonCWpressed == true) {
        digitalWrite(yodelSoundPin, LOW);
    }
}

void playFallSound() {

    if (fallpinActive == true) {
        digitalWrite(fallSoundPin, LOW);
    }
    if (fallpinActive == false) {
        digitalWrite(fallSoundPin, HIGH);
    }
}
void playWinSound() {
    if (winSoundPlaying == false) {
        digitalWrite(winSoundPin, HIGH);
    }
    if (winSoundPlaying == true) {
        digitalWrite(winSoundPin, LOW);
    }
}
void playLoseSound() {
    if (loseSoundPlaying == false) {
        digitalWrite(loseSoundPin, HIGH);
    }
    if (loseSoundPlaying == true) {
        digitalWrite(loseSoundPin, LOW);
    }
}
void playIdleSound() {
    if (idleSoundPlaying == false) {
        digitalWrite(idleSoundPin, HIGH);
    }
    if (idleSoundPlaying == true) {
        digitalWrite(idleSoundPin, LOW);
    }
}