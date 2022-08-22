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

5)Sound track loose…loosing sound, and music

6)Idle music.

7)Resets game to start position moves goat to starting position. No sound.

********************************Electromagnetic triggers***************************************

An electromagnet creates a “start of game” sound when he crosses position one.

An electromagnet at the top of the mountain would trigger a sound effect - falling yodel sound

Perhaps another electromagnet could trigger red flashing lighting 
    and a sound effect that warns that the goat is going to fall off when it passes.

*********************************Pinouts for Sound Board***************************************

01 Travel Music : Hold Looping Trigger.  Arduino Pin 30
01 Travel Music : Hold Looping Trigger.  Arduino Pin 30  
*/

byte travelSoundPin = 30;
byte stepPin = 22;                      //Stepper Motor Control
byte dirPin  = 23;

void setup() { 
    
    pinMode(4, INPUT_PULLUP);
    pinMode(5, INPUT_PULLUP);
    pinMode(6, INPUT_PULLUP);
    pinMode(7, INPUT_PULLUP);
    pinMode(8, INPUT_PULLUP);                   //Cue 4 winning sound 1x
    pinMode(9, INPUT_PULLUP);                   //Cue 5 losing sound 1x
    pinMode(10, INPUT_PULLUP);                  //Cue 6 idle music loop
    
    pinMode(33, OUTPUT);
    pinMode(34, OUTPUT);
    pinMode(35, OUTPUT);
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    pinMode(travelSoundPin, OUTPUT);
}

void loop() {
    //read the buttons into variables

    /*
    //Cue #1, Random Move, Button 1 > Pin 5 INPUT > STEP/DIR, Travel music then Ding sound
        int sensor1Val = digitalRead(5);
        if (sensor1Val == HIGH) {
            digitalWrite(33, HIGH);
        }
        else {
            digitalWrite(33, LOW);
        }
    */
    
    //Cue #2, Space 24 Move, Button 4 > Pin 6 INPUT > STEP/DIR, Travel music then Ding sound
        int sensor2Val = digitalRead(6);
        if (sensor2Val == LOW) {
        digitalWrite(travelSoundPin,HIGH);
        digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
        // Makes 6100 pulses to go to space 24
        for(int x = 0; x < 6100; x++) {
            digitalWrite(stepPin,HIGH);  
            delayMicroseconds(1000); 
            digitalWrite(stepPin,LOW); 
            delayMicroseconds(1000);
            digitalWrite(travelSoundPin,LOW);

        }
        }
        

    //Cue #4, Sound Track WIN, Button 4 > Pin 8 INPUT > Pin 33 OUTPUT > Pin 3 on sound board
        int sensor4Val = digitalRead(8);
        if (sensor4Val == HIGH) {
            digitalWrite(33, HIGH);
        }
        else {
            digitalWrite(33, LOW);
        }

    //Cue #5, Sound Track LOSE, Button 5 > Pin 9 INPUT > Pin 34 OUTPUT > Pin 2 on sound board
        int sensor5Val = digitalRead(9);
        if (sensor5Val == HIGH) {
            digitalWrite(34, HIGH);
        }
        else {
            digitalWrite(34, LOW);
    }

    //Cue #6, Sound Track IDLE MUSIC, Button 6 > Pin 10 INPUT > Pin 35 OUTPUT > Pin 6 on sound board
        int sensor6Val = digitalRead(10);
        if (sensor6Val == HIGH) {
            digitalWrite(35, HIGH);
        }
        else {
            digitalWrite(35, LOW);
    }
}