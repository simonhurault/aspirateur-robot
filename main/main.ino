// Define Trig and Echo pin:
#define EMITTER_PIN 2
#define RECEIVER_PIN 4
#include <Motors.h>


Motors motors; //Creation of a Motors object to control the 2


/*
 * This function allow you the get the distance between the captor and the robot
 * Output : the distance
 */
int get_distance()
{
  long duration;
  int distance;
  
  digitalWrite(EMITTER_PIN, LOW);
  delayMicroseconds(5);
  
  digitalWrite(EMITTER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(EMITTER_PIN, LOW);
  
  duration = pulseIn(RECEIVER_PIN, HIGH);
  
  distance= duration*0.034/2;
  return distance >= 2? distance : 0; // the captor isn't precise for a distance less than 2cm
}



void setup() {
  pinMode(EMITTER_PIN, OUTPUT);
  pinMode(RECEIVER_PIN, INPUT);
  Serial.begin(9600);

}

void loop() {
  if(get_distance()<= 10)
  {
    motors.stop();
    delay(1000);
    motors.turn(90);
    delay(3000);
  }
  else
  {
    motors.move(1,90);
  }

}
