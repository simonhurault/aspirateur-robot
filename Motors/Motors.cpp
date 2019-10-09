#include "Motors.h"
#include <Arduino.h>


Motors::Motors()
{
  //pins for the A motor
  int PWM_A = 3;
  int DIR_A = 12;
  int BRAKE_A = 9;
  int SNS_A  = A0;

  //pins for the B motor
  int PWM_B   = 11;
  int DIR_B   = 13;
  int BRAKE_B = 8;
  int SNS_B   = A1;

  pinMode(BRAKE_A, OUTPUT);  // Brake pin on channel A
  pinMode(DIR_A, OUTPUT);    // Direction pin on channel A
  pinMode(BRAKE_B, OUTPUT);  // Brake pin on channel B
  pinMode(DIR_B, OUTPUT);    // Direction pin on channel B
}

void Motors::move(int direction, int speed)
{
  // setting the brakes LOW disable motors brake
    digitalWrite(BRAKE_A, LOW);
    digitalWrite(BRAKE_B, LOW);
    
    // setting the direction of the motors
    digitalWrite(DIR_A, direction);
    digitalWrite(DIR_B, direction);

    
     // setting the speed of the motors
     analogWrite(PWM_A, speed);
     analogWrite(PWM_B, speed); 
}


void Motors::stop()
{
    // raising the brake pin to stop the motor faster than the stop by inertia
    digitalWrite(BRAKE_A, HIGH);  // raise the brake for motor A
    digitalWrite(BRAKE_B, HIGH);  // raise the brake for motor B
}


void Motors::turn(int speed)
{
  // setting the brakes LOW disable motors brake
    digitalWrite(BRAKE_A, LOW);
    digitalWrite(BRAKE_B, LOW);
    
    // setting the direction of the motors
    digitalWrite(DIR_A, HIGH);
    digitalWrite(DIR_B, LOW);

    // setting the speed to its "speed" value
    analogWrite(PWM_B, speed);
    analogWrite(PWM_A, speed);
}