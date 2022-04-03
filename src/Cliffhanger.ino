#include <Arduino.h>
/*
  Stepper Motor Demonstration 4
  Stepper-Demo4.ino
  Demonstrates NEMA 17 Bipolar Stepper with A4988 Driver

  DroneBot Workshop 2018
  https://dronebotworkshop.com
  https://dronebotworkshop.com/stepper-motors-with-arduino/
*/

// Define Constants

// Connections to A4988
const int dirPin = 12;  // Direction
const int stepPin = 13; // Step

// Motor steps per rotation
const int STEPS_PER_REV = 200;
 
void setup() {
  
  // Setup the pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
}
void loop() {
  
  // Set motor direction clockwise
  digitalWrite(dirPin,HIGH); 
  
  // Spin motor one rotation slowly
  for(int x = 0; x < STEPS_PER_REV; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(2000); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(2000); 
  }
  
  // Pause for one second
  delay(3000); 
  
  // Set motor direction counterclockwise
  digitalWrite(dirPin,LOW);
  
  // Spin motor two rotations quickly
  for(int x = 0; x < (STEPS_PER_REV * 2); x++) {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(1000);
  }
  
  // Pause for one second
  delay(3000);
}
