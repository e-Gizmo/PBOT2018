/**********************************************
 * e-Gizmo PBOT2018 Controller - MAZE.ino
 * 
 * This enables pbot to avoid obstacles and may
 * also solve mazes.
 * 
 * Reading the 3channel Collision sensors:
 * PBOT.COL1_RIGHT();
 * PBOT.COL2_CENTER();
 * PBOT.COL3_LEFT();
 * Output reads:
 * No object detection = 0 or LOW;
 * Object detected     = 1 or HIGH;
 * 
 * Codes by
 * e-Gizmo Mechatronix Central
 * http://www.e-gizmo.net
 * June 5,2018
 ************************************************/
#include <Wire.h>
#include "eGizmo_PBOT2018.h"


eGizmo_PBOT2018 PBOT;

int SPEED;
int NORMAL_SPEED = 90;
int ROTATE_SPEED = 90;
int TURN_SPEED_HIGH = 80;
int TURN_SPEED_LOW = 120;
int PAUSE = 200;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  PBOT.BEGIN(); //PBOT begin and turn on all motors
  PBOT.SPEED(MOTOR_BOTH,200); // Start motors in 200 PWM speeds
}
void loop()
{
  if(PBOT.COL3_LEFT() == 0 && PBOT.COL2_CENTER() == 0 && PBOT.COL1_RIGHT() == 0)
  {
    FORWARD();
  }
  if(PBOT.COL3_LEFT() == 1 && PBOT.COL2_CENTER() == 1 && PBOT.COL1_RIGHT() == 1)
  {
    REVERSE();
    delay(PAUSE);
    ROTATE();
    delay(PAUSE);
  }
  if(PBOT.COL3_LEFT() == 1 && PBOT.COL2_CENTER() == 1)
  {
    TURN_RIGHT();
    delay(500);
    FORWARD();
    delay(PAUSE);
  }
  if(PBOT.COL2_CENTER() == 1  && PBOT.COL1_RIGHT() == 1)
  {
    TURN_LEFT();
    delay(500);
    FORWARD();
    delay(PAUSE);
  }
}

void FORWARD()
{
  PBOT.DIRECTION(MOTOR_BOTH,MOTOR_FWD);
  PBOT.SPEED(MOTOR_BOTH,NORMAL_SPEED);
}
void ROTATE()
{
  PBOT.DIRECTION(MOTOR_A,MOTOR_REV);
  PBOT.DIRECTION(MOTOR_B,MOTOR_FWD);
  PBOT.SPEED(MOTOR_BOTH,ROTATE_SPEED);
}
void REVERSE()
{
  PBOT.DIRECTION(MOTOR_BOTH, MOTOR_REV);
  PBOT.SPEED(MOTOR_BOTH,NORMAL_SPEED);
}
void STOP()
{
  PBOT.SPEED(MOTOR_BOTH,0);
}
void TURN_LEFT()
{
  PBOT.DIRECTION(MOTOR_B, MOTOR_FWD);
  PBOT.SPEED(MOTOR_B, TURN_SPEED_HIGH);
  PBOT.DIRECTION(MOTOR_A, MOTOR_REV);
  PBOT.SPEED(MOTOR_A, TURN_SPEED_LOW);
}
void TURN_RIGHT()
{
  PBOT.DIRECTION(MOTOR_A, MOTOR_FWD);
  PBOT.SPEED(MOTOR_A, TURN_SPEED_HIGH);
  PBOT.DIRECTION(MOTOR_B, MOTOR_REV);
  PBOT.SPEED(MOTOR_B, TURN_SPEED_LOW);
}

