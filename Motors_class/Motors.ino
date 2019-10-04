

/* 
 *  This structure will help you use 2 dc motors for moving your robot 
*/


struct Motors {
  //These arguments set the pins for the motor A
  const int 
  PWM_A = 3,
  DIR_A = 12,
  BRAKE_A = 9,
  SNS_A  = A0;

  
  //These arguments set the pins for the motor B
  const int 
  PWM_B   = 11,
  DIR_B   = 13,
  BRAKE_B = 8,
  SNS_B   = A1;


  void init()
  {
    pinMode(BRAKE_A, OUTPUT);  // Brake pin on channel A
    pinMode(DIR_A, OUTPUT);    // Direction pin on channel A
    pinMode(BRAKE_B, OUTPUT);  // Brake pin on channel B
    pinMode(DIR_B, OUTPUT);    // Direction pin on channel B
  }



  /* This method allows you to make the robot go forward 
   * input : int direcction, put 1 or more to go forward,  0 to go backward
   *         int speed, the speed between 0 and 255
  */         
  
  void move(int direction, int speed)
  {
    
    // setting the brakes LOW disable motors brake
    digitalWrite(BRAKE_A, LOW);
    digitalWrite(BRAKE_B, LOW);
    
    // setting direction to HIGH will make the motors spin forward
    digitalWrite(DIR_A, direction);
    digitalWrite(DIR_B, direction);

    
     // setting the speed to its maximum value
     analogWrite(PWM_A, speed);
     analogWrite(PWM_B, speed);       
  }

 
  //This method allows you to stop the robot
  void stop()
  {
    // raising the brake pin the motor will stop faster than the stop by inertia
    digitalWrite(BRAKE_A, HIGH);  // raise the brake for motor A
    digitalWrite(BRAKE_B, HIGH);  // raise the brake for motor B
  }


  /*
   * This method allows you to turn your robot
   * input : int speed, the speed between 0 and 255
   */
  void turn(int speed)
  {
    // setting the brakes LOW disable motors brake
    digitalWrite(BRAKE_A, LOW);
    digitalWrite(BRAKE_B, LOW);
    
    // setting direction to HIGH will make the motors spin forward
    digitalWrite(DIR_A, HIGH);
    digitalWrite(DIR_B, LOW);
    // setting the speed to its "speed" value
    analogWrite(PWM_B, speed);
    analogWrite(PWM_A, speed);
   
  }

     
};
