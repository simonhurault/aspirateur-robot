#include "Motors.h"
#include <Arduino.h>


Motors::Motors()
{
  //pins for the A motor
  PWM_A = 3;
  DIR_A = 12;
  BRAKE_A = 9;
  SNS_A  = A0;

  //pins for the B motor
  PWM_B   = 11;
  DIR_B   = 13;
  BRAKE_B = 8;
  SNS_B   = A1;

  pinMode(BRAKE_A, OUTPUT);  // Brake pin on channel A
  pinMode(DIR_A, OUTPUT);    // Direction pin on channel A
  pinMode(BRAKE_B, OUTPUT);  // Brake pin on channel B
  pinMode(DIR_B, OUTPUT);    // Direction pin on channel B
}


void Motors::move(int direction, int speed, int corrector)
{
  // setting the brakes LOW disable motors brake
    digitalWrite(BRAKE_A, LOW);
    digitalWrite(BRAKE_B, LOW);
    
    // setting the direction of the motors
    digitalWrite(DIR_A, direction);
    digitalWrite(DIR_B, direction);

    
     // setting the speed of the motors
	if (corrector + speed > 255)
		analogWrite(PWM_A, 255);

	else if(corrector + speed < 0)
		analogWrite(PWM_A, 0);
    
	else
		analogWrite(PWM_A, speed + corrector);

    analogWrite(PWM_B, speed); 
}


void Motors::stop()
{
    // raising the brake pin to stop the motor faster than the stop by inertia
    digitalWrite(BRAKE_A, HIGH);  // raise the brake for motor A
    digitalWrite(BRAKE_B, HIGH);  // raise the brake for motor B
}


void Motors::turn(char direction, int speed)
{
	if (direction == 'L')
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
	else if (direction == 'R')
	{
		// setting the brakes LOW disable motors brake
		digitalWrite(BRAKE_A, LOW);
		digitalWrite(BRAKE_B, LOW);

		// setting the direction of the motors
		digitalWrite(DIR_A, LOW);
		digitalWrite(DIR_B, HIGH);

		// setting the speed to its "speed" value
		analogWrite(PWM_B, speed);
		analogWrite(PWM_A, speed);
	}
}
