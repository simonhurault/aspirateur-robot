// Define Trig and Echo pin:
#define EMITTER_PIN 2
#define RECEIVER_PIN 4
#include <Motors.h>


Motors motors; //Creation of a Motors object to control the 2


/*
 * This function allows you the get the distance between the captor and an obstacle
 * Output : the distance between captor and obstacle(int)
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
  randomSeed(analogRead(3));

}

void loop() {
  if(get_distance()<= 10)    //if the robot will met an obstacle we turn
  {
    motors.stop();
    delay(1000);
    motors.turn(105);
    delay(random(800,1500));
  }
  else                      //else we go forward
  {
    motors.move(1,105 );
  }
}
