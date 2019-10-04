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