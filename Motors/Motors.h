/**
 * This library is under creative commons license. 
 * It was created by Simon Hurault, Reda Arifi and Quentin Rebuffat
 * This library allows you to control 2 DC motors to move a robot
 */

#ifndef Motors_h
#define Motors_h


class Motors
{
  public:

  /**
   * Constructor
   */
  Motors(); 

  /**
   * The 2 motors go forward
   * @param direction : 1 to go forward, 0 to go backward
   * @param speed : speed of the motor between 0 and 255
   * @param correcotr : value to add at motor A to even out the real life speed
   */
  void move(int direction, int speed, int corrector);


  /**
   * Stop the 2 motors
   */
  void stop();

  /**
   * The motors turn in opposite direction to turn
   * @param direction :  'L' to go left and 'R' to go right
   * @param speed : speed of the motor between 0 and 255
   */
  void turn(char direction, int speed);

  private:
  int PWM_A, DIR_A, BRAKE_A, SNS_A; // Motors A pins
  int PWM_B, DIR_B, BRAKE_B, SNS_B; // Motors B pins
};
#endif