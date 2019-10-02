// Define Trig and Echo pin:
#define EMITTER_PIN 2
#define RECEIVER_PIN 4
#include <P:\aspirateur-robot\Motors\Motors.ino>

Motors motors;


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
  return distance >= 2? distance : 0;
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
