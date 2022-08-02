#include <Arduino.h>

void setup() { 
    pinMode(8, INPUT_PULLUP);                   //Cue 4 winning sound 1x
    pinMode(9, INPUT_PULLUP);                   //Cue 5 losing sound 1x
    pinMode(10, INPUT_PULLUP);                  //Cue 6 idle music loop
    pinMode(33, OUTPUT);
    pinMode(34, OUTPUT);
    pinMode(35, OUTPUT);
}

void loop() {
    //read the buttons into variables

    //Cue #4, Sound track win, Button 4 > Pin 8 INPUT > Pin 33 OUTPUT > Pin 3 on sound board
        int sensor4Val = digitalRead(8);
        if (sensor4Val == HIGH) {
            digitalWrite(33, HIGH);
        }
        else {
            digitalWrite(33, LOW);
        }

    //Cue #5, Sound track lose, Button 5 > Pin 9 INPUT > Pin 34 OUTPUT > Pin 2 on sound board
        int sensor5Val = digitalRead(9);
        if (sensor5Val == HIGH) {
            digitalWrite(34, HIGH);
        }
        else {
            digitalWrite(34, LOW);
    }

    //Cue #6, Sound track idle music, Button 6 > Pin 10 INPUT > Pin 35 OUTPUT > Pin 6 on sound board
        int sensor6Val = digitalRead(10);
        if (sensor6Val == HIGH) {
            digitalWrite(35, HIGH);
        }
        else {
            digitalWrite(35, LOW);
    }
}