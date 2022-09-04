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

T01HOLDL.ogg                            Travel Music
T02.ogg                                 Losing (Falling Yodel) Sound
T03.ogg                                 Winning Sound
T04.ogg                                 1 Ding
T05.ogg                                 Danger Sound
T06LATCH.ogg                            Idle Music
T07.ogg                                 Buzz
T08.ogg                                 Reset Game Music
*/

const int speed1 = 1000;
const int speed2 = 500;

int buttonState = 0;                   // Current stete of the button - Used to trigger T04 1 Ding sound at end of travel move
int lastButtonState = 0;               // previous state of the button

byte stepPin = 22;                     //Stepper Motor Control
byte dirPin  = 23;                     //Stepper Motor Control
//-------------------------------------Buttons-------------------------------------------------------------------------------------
byte reset = 4;                        //Cue 7 : Moves goat to Start of game location : resetPin 
byte randomMove = 5;                   //Cue 1 : Moves goat random distance between resetPin and dangerPin
byte space24 = 6;                      //Cue 2 : Moves goat to just before dangerPin
byte manual = 7;                       //Cue 3 : Moves goat until button is released
byte win = 8;                          //Cue 4 : plays win sound
byte lose = 9;                         //Cue 5 : plays lose sound
byte idle = 10;                        //Cue 6 : plays win sound
//-------------------------------------Sound Board Triggers-------------------------------------------------------------------------------------
byte travelSoundPin = 30;              //pin 1 on sound board : Hold Looping Trigger
byte fallSoundPin = 31;                //pin 2 on sound board : Basic Trigger
byte winSoundPin = 32;                 //pin 3 on sound board : Basic Trigger
byte dingSoundPin = 33;                //pin 4 on sound board : Basic Trigger
byte loseSoundPin = 34;                //pin 5 on sound board : Basic Trigger
byte idleSoundPin = 35;                //pin 6 on sound board : Latching Loop Trigger
byte dangerSoundPin = 36;              //pin 7 on sound board : Basic Trigger
//-------------------------------------Optical Switches-------------------------------------------------------------------------------------
byte resetPin  = 24;                   //Start of game location
byte dangerPin  = 25;                   //Start of game location
byte fallPin  = 26;                   //Start of game location

void setup() { 
    
    pinMode(reset, INPUT_PULLUP);
    pinMode(randomMove, INPUT_PULLUP);
    pinMode(space24, INPUT_PULLUP);
    pinMode(manual, INPUT_PULLUP);
    pinMode(win, INPUT_PULLUP);              //Cue 4 winning sound 1x
    pinMode(lose, INPUT_PULLUP);             //Cue 5 losing sound 1x
    pinMode(idle, INPUT_PULLUP);             //Cue 6 idle music loop
    
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

}

void loop() {

    //Read the buttons

        int sensor1Val = digitalRead(5);
        if (sensor1Val == LOW) {
            int moveLength=random(100,7000);
            buttonState++;
            digitalWrite(dirPin,HIGH);                      // Enables the belt to move forward
        for(int x = 0; x < moveLength; x++) {               // Moves goat a random number of steps
            digitalWrite(stepPin,HIGH);  
            delayMicroseconds(speed1); 
            digitalWrite(stepPin,LOW); 
            delayMicroseconds(speed1);
            }
            digitalWrite(travelSoundPin,LOW);
            digitalWrite(travelSoundPin,HIGH);
            if (buttonState != lastButtonState){
                digitalWrite(dingSoundPin,LOW);
                delay(25);
                digitalWrite(dingSoundPin,HIGH);
                buttonState--;
            }
        } 
    
    //Cue #2, Space 24 Move, Button 2 > Pin 6 INPUT > STEP/DIR, Travel music then Ding sound
        int sensor2Val = digitalRead(6);
        if (sensor2Val == LOW) {
            digitalWrite(travelSoundPin,LOW);
            digitalWrite(dirPin,HIGH);                      // Enables the belt to move forward
        for(int x = 0; x < 6100; x++) {                     // Moves goat 6100 steps to Space 24 - just before Danger sensor
            digitalWrite(stepPin,HIGH);  
            delayMicroseconds(speed1); 
            digitalWrite(stepPin,LOW); 
            delayMicroseconds(speed1);
            }
            digitalWrite(travelSoundPin,HIGH);
            digitalWrite(dingSoundPin,LOW);
            delay(25);
            digitalWrite(dingSoundPin,HIGH);
        }

     //Cue #3, Manual Move, Button 3 > Pin 7 INPUT > STEP/DIR, Travel music then Ding sound
        int sensor3Val = digitalRead(7);
        if (sensor3Val == LOW) {
            buttonState++;
            digitalWrite(dirPin,HIGH); // Enables the belt to move forward
            digitalWrite(stepPin,HIGH);  
            delayMicroseconds(speed1); 
            digitalWrite(stepPin,LOW); 
            delayMicroseconds(speed1);
            digitalWrite(travelSoundPin,LOW);
            digitalWrite(travelSoundPin,HIGH);
            if (buttonState != lastButtonState){
                digitalWrite(dingSoundPin,LOW);
                delay(25);
                digitalWrite(dingSoundPin,HIGH);
                buttonState--;
            }
        }      

    //Cue #4, Sound Track WIN, Button 4 > Pin 8 INPUT > Pin 33 OUTPUT > Pin 3 on sound board
        int sensor4Val = digitalRead(8);
        if (sensor4Val == HIGH) {
            digitalWrite(winSoundPin, HIGH);
        }
        else {
            digitalWrite(winSoundPin, LOW);
        }

    //Cue #5, Sound Track LOSE, Button 5 > Pin 9 INPUT > Pin 34 OUTPUT > Pin 2 on sound board
        int sensor5Val = digitalRead(9);
        if (sensor5Val == HIGH) {
            digitalWrite(loseSoundPin, HIGH);
        }
        else {
            digitalWrite(loseSoundPin, LOW);
        }

    //Cue #6, Sound Track IDLE MUSIC, Button 6 > Pin 10 INPUT > Pin 35 OUTPUT > Pin 6 on sound board
        int sensor6Val = digitalRead(10);
        if (sensor6Val == HIGH) {
            digitalWrite(idleSoundPin, HIGH);
        }
        else {
            digitalWrite(idleSoundPin, LOW);
        }
}