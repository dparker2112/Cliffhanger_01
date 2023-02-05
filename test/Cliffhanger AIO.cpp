#include <Arduino.h>

// Control for Cliffhanger game.  Made by David Parker nlightn0@gmail.com 04/01/2022

/*
*******************************Overview of button behaviors*************************************

1)Start button: Random goat move 1-12 spaces along the track. Each move different. 
Beginning yodel to start, then Traveling music track plays during movement. When the figure stops, a
bell “DING”

2)Go directly to space #24. Beginning yodel to start, then plays music while it travels and 
when the figure stops a bell “Ding”

3)Manual run. Beginning yodel to start, character moves until host takes finger off button then the stop DING

4)Sound track win..play sound ding ding ding ding and winning music

5)Sound track lose…loosing sound, and music

6)Idle music.

7)Resets game to start position moves goat to starting position. No sound.

********************************Electromagnetic triggers***************************************

An electromagnet creates a “start of game” sound when he crosses position one.

An electromagnet at the top of the mountain would trigger a sound effect - falling yodel sound

Perhaps another electromagnet could trigger red flashing lighting 
    and a sound effect that warns that the goat is going to fall off when it passes.

*********************************Pinouts for Sound Board***************************************

T01HOLDL.ogg                            Travel Music (Loops as long as its pin is held LOW)
T02.ogg                                 Losing (Falling Yodel) Sound
T03.ogg                                 Winning Sound
T04.ogg                                 1 Ding
T05.ogg                                 Danger Sound
T06LATCH.ogg                            Idle Music (Plays when its pin is triggered LOW, stops when it's triggered again)
T07.ogg                                 Buzz
T08.ogg                                 Reset Game Music
T09.LATCH.ogg                           Travel Music (Plays when its pin is triggered LOW, stops when it's triggered again)
*/

const int speed1 = 1000;
const int speed2 = 250;
//********************************LECTERN BUTTONS*********************************************
const int reset = 4;                         //Cue 7 : Moves goat to Start of game location : resetPin 
const int randomMove = 5;                    //Cue 1 : Moves goat random distance between resetPin and dangerPin
const int space24 = 6;                       //Cue 2 : Moves goat to just before dangerPin (space 24)
const int manual = 7;                        //Cue 3 : Moves goat until button is released
const int win = 8;                           //Cue 4 : plays win sound
const int lose = 9;                          //Cue 5 : plays lose sound
const int idle = 10;                         //Cue 6 : plays win sound
//********************************SOUND TRIGGERS**********************************************
const int travelSoundPin = 30;               //pin 1 on sound board : Hold Looping Trigger
const int fallSoundPin = 31;                 //pin 2 on sound board : Basic Trigger
const int winSoundPin = 32;                  //pin 3 on sound board : Basic Trigger
const int dingSoundPin = 33;                 //pin 4 on sound board : Basic Trigger
const int loseSoundPin = 34;                 //pin 5 on sound board : Basic Trigger
const int idleSoundPin = 35;                 //pin 6 on sound board : Latching Loop Trigger
const int dangerSoundPin = 36;               //pin 7 on sound board : Basic Trigger
//********************************SENSORS AND MOTOR CONTROL***********************************
const int resetPin  = 24;                    //Start of game location
const int dangerLocationPin = 25;            //Play Danger Sound
const int fallPin = 26;                      //Play Lose Sound
const int stepPin = 22;                      //Stepper Motor Control
const int dirPin  = 23;
//********************************Button 3 Variables******************************************
int buttonState = 1;
int lastButtonState = 1;


void setup() { 
    
    pinMode(4, INPUT_PULLUP);                   //Cue 7 return to home position                    
    pinMode(5, INPUT_PULLUP);                   //Cue 1 random move space 1 - 12
    pinMode(6, INPUT_PULLUP);                   //Cue 2 go to space 24 
    pinMode(7, INPUT_PULLUP);                   //Cue 3 manual move
    pinMode(8, INPUT_PULLUP);                   //Cue 4 winning sound 1x
    pinMode(9, INPUT_PULLUP);                   //Cue 5 losing sound 1x
    pinMode(10, INPUT_PULLUP);                  //Cue 6 idle music loop
    pinMode(24, INPUT_PULLUP);                  //optical sensor - home position
    pinMode(25, INPUT_PULLUP);                  //optical sensor - triggers DANGER sound
    pinMode(26, INPUT_PULLUP);                  //optical sensor - triggers LOSE sound

    pinMode(travelSoundPin, OUTPUT);
    pinMode(fallSoundPin, OUTPUT);
    pinMode(winSoundPin, OUTPUT);
    pinMode(dingSoundPin, OUTPUT);
    pinMode(loseSoundPin, OUTPUT);
    pinMode(idleSoundPin, OUTPUT);
    pinMode(dangerSoundPin, OUTPUT);
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);

    digitalWrite(travelSoundPin,HIGH);
    digitalWrite(fallSoundPin,HIGH);
    digitalWrite(winSoundPin,HIGH);
    digitalWrite(dingSoundPin,HIGH);
    digitalWrite(loseSoundPin,HIGH);
    digitalWrite(idleSoundPin,HIGH);
    digitalWrite(dangerSoundPin,HIGH);

    Serial.begin(9600);
}