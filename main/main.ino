#include <Motors.h>
// Define Trig and Echo pin:

#define EMITTER_PIN_RIGHT 2
#define RECEIVER_PIN_RIGHT 4

#define EMITTER_PIN_LEFT 7
#define RECEIVER_PIN_LEFT 10

#define DISTANCE_MAX 17


Motors motors = Motors(); //Creation of a Motors object to control the 2

/*
 * This function allows you the get the distance between the captor and an obstacle
 * Output : the distance between captor and obstacle(int)
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
  return distance >= 2? distance : 0; // the captor isn't precise for a distance less than 2cm
}

char needToTurn()
{
   if(get_distance(EMITTER_PIN_RIGHT , RECEIVER_PIN_RIGHT) <= DISTANCE_MAX)
     return 'R';
    
   if(get_distance(EMITTER_PIN_LEFT , RECEIVER_PIN_LEFT) <= DISTANCE_MAX)
      return 'L';

   return 'M';
}


void setup() {
  //pinMode(EMITTER_PIN_MID, OUTPUT);
  pinMode(EMITTER_PIN_RIGHT, OUTPUT);
  pinMode(EMITTER_PIN_LEFT, OUTPUT);
  
  //pinMode(RECEIVER_PIN_MID, INPUT);
  pinMode(RECEIVER_PIN_RIGHT, INPUT);
  pinMode(RECEIVER_PIN_LEFT, INPUT);
  
  randomSeed(analogRead(3));
}

void loop() {
  switch(needToTurn())
  {
    case('R'):
      motors.stop();
      delay(1000);
      motors.turn('L',110);
      delay(random(800,1500));
      break;

    case('L'):
      motors.stop();
      delay(1000);
      motors.turn('R',110);
      delay(random(800,1500));
      break;
   
    default:
      motors.move(1, 110);
      break;
      
  }  
}
    
