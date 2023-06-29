#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "Motor.h"

#define MOTOR_LEFT 0
#define MOTOR_RIGHT 1
// TODO
#define _PERIOD 50
#define _EXEC_TIME 3000
#define _SAMPLES_TO_SKIP 4

int const length = (_EXEC_TIME / _PERIOD) - (_SAMPLES_TO_SKIP - 1); // Comprimento do array (20)

struct Data
{
    int pwmLeft;
    int pwmRight;
    int ticksLeft;
    int ticksRight;
    float ratio;
};

class Movement
{
public:
    Movement(Motor *motors, float track);

    void begin();

    void line(float speed, float length, bool isFront = true);
    void front(float speed, float length);
    void back(float speed, float length);

    virtual void curve(float speed, float radius, float angle, bool isLeft = true) = 0;
    virtual void left(float speed, float radius, float angle) = 0;
    virtual void right(float speed, float radius, float angle) = 0;

    void stop();
    void slow();
    void block();

    void reset();

    float getTrack();
    Motor *getMotors();

protected:
    Motor *_motors;
    int _numMotors;
    int _MIN_PWM = 2048; 
    int _MAX_PWM = 4095; 
    float _MIN_SPEED = 50.0;
    float _MAX_SPEED = 100.0;
    
private:
    virtual void _directionCalibration();
    float _track;       // Distance between wheels (cm)
};
#endif
