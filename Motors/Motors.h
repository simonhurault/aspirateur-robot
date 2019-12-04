/*
* This library is under creative commons license. 
* It was created by Simon Hurault, Reda Arifi and Quentin Rebuffat
* This library allows you to control 2 DC motors to move a robot
*/

#ifndef Motors_h
#define Motors_h


class Motors
{
  public:
  Motors(); 
  void move(int direction, int speed);
  void stop();
  void turn(int speed);

  private:
  int PWM_A, DIR_A, BRAKE_A, SNS_A;
  int PWM_B, DIR_B, BRAKE_B, SNS_B;
};
#endif