#include <Motors.h>
// Define Trig and Echo pin:

#define EMITTER_PIN_RIGHT 2
#define RECEIVER_PIN_RIGHT 4

#define EMITTER_PIN_LEFT 7
#define RECEIVER_PIN_LEFT 10

#define DISTANCE_MAX 15


Motors motors = Motors(); //Creation of a Motors object to control the 2

/*
 * This function allows you the get the distance between a captor and an obstacle
 * @param emitter : emitter pin
 * @param receiver : receiver pin
 * @return : the distance between captor and obstacle
 */
int get_distance(int emitter , int receiver)
{
  long duration;
  int distance;
  
  digitalWrite(emitter, LOW);
  delayMicroseconds(5);
  
  digitalWrite(emitter, HIGH);
  delayMicroseconds(10);
  digitalWrite(emitter, LOW);
  
  duration = pulseIn(receiver, HIGH);
  
  distance= duration*0.034/2;
  Serial.println(distance);
  return distance >= 2? distance : 0; // the captor isn't precise for a distance less than 2cm
}


/**
 * allow to know the direction that the robot has to go
 * @ return : 'R' if right, 'L' if left, 'M' if forward
 */
char needToTurn()
{
   if(get_distance(EMITTER_PIN_RIGHT , RECEIVER_PIN_RIGHT) <= DISTANCE_MAX)
     return 'R';
    
   if(get_distance(EMITTER_PIN_LEFT , RECEIVER_PIN_LEFT) <= DISTANCE_MAX)
      return 'L';

   return 'M';
}


void setup() {
  // Initialisation of the pins
  pinMode(EMITTER_PIN_RIGHT, OUTPUT);
  pinMode(EMITTER_PIN_LEFT, OUTPUT);
  
  pinMode(RECEIVER_PIN_RIGHT, INPUT);
  pinMode(RECEIVER_PIN_LEFT, INPUT);

  // Initiate the random value
  randomSeed(analogRead(3));
}

void loop() {

  // Using the value of needToturn() to make the robot move
  switch(needToTurn())
  {
    // Turn right
    case('R'):
      motors.stop();
      delay(1000);
      
      motors.turn('L',100);
      delay(random(800,1500));
      
      motors.stop();
      delayMicroseconds(10);
      break;

    // Turn left
    case('L'):
      motors.stop();
      delay(1000);
      motors.turn('R',100);
      delay(random(800,1500));
      motors.stop();
      delayMicroseconds(10);
      break;

   // Go forward
    default:
      motors.move(1, 100, -5);
      break;
  }
      
   
}
    
