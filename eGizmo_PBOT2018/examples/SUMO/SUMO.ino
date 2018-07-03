/**********************************************
 * e-Gizmo PBOT2018 Controller - SUMO.ino
 * 
 * This is for collsion sample sketch to avoid
 * lines and stays in a ring with 3 channel collsion
 * sensors to bump the targets if detected.
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
int BUMP_SPEED_LEFT = 110;
int BUMP_SPEED_CENTER = 130;
int BUMP_SPEED_RIGHT = 110;
int ROTATE_SPEED = 90;
int SAFE_SPEED = 80;
int LINE_SENSE= 0;
int GET_BACK = 0;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  PBOT.BEGIN(); //PBOT begin and turn on all motors
  PBOT.SPEED(MOTOR_BOTH,200); // Start motors in 200 PWM speeds
}
void loop()
{
  //Attacking the opponent if the sensors detects it
  if(PBOT.COL2_CENTER() == HIGH)
  {
    BUMP_THE_OPPONENTS_ON_CENTER();
  }
  if(PBOT.COL3_LEFT() == HIGH)
  {
    BUMP_THE_OPPONENTS_ON_LEFT();
  }
  if(PBOT.COL1_RIGHT() == HIGH)
  {
    BUMP_THE_OPPONENTS_ON_RIGHT();
  }  
  if(PBOT.COL1_RIGHT() == HIGH && PBOT.COL3_LEFT() == HIGH){
    BUMP_THE_OPPONENTS_ON_CENTER();
  }

  //Avoiding the outside black line
  if(PBOT.LS1_LEFT() == HIGH && PBOT.LS3_RIGHT() == LOW)
  {
    TURN_RIGHT(); 
    delay(100);
  }
  if(PBOT.LS1_LEFT() == LOW && PBOT.LS3_RIGHT() == HIGH)
  {
    TURN_LEFT(); 
    delay(100);
  }
  if(PBOT.LS1_LEFT() == HIGH && PBOT.LS2_CENTER() == HIGH && PBOT.LS3_RIGHT() == HIGH){
    REVERSE();
    delay(200);
    ROTATE();
    delay(900);
  }
 // If all sensors detects nothing
  if(PBOT.COL3_LEFT() == LOW && PBOT.COL2_CENTER() == LOW && PBOT.COL1_RIGHT() == LOW)
  {
    SAFE_DRIVE();
  }
  if(PBOT.LS2_CENTER() == LOW) LINE_SENSE = 1;
  if (LINE_SENSE == 2){
    ROTATE();
    delay(900);
    GET_BACK = 0;
  }
  else
  {
    GET_BACK = 0;
    SAFE_DRIVE();

  }

}

void SAFE_DRIVE()
{
  PBOT.DIRECTION(MOTOR_BOTH,MOTOR_FWD);
  PBOT.SPEED(MOTOR_BOTH,SAFE_SPEED);
}
void ROTATE()
{
  PBOT.DIRECTION(MOTOR_A,MOTOR_REV);
  PBOT.DIRECTION(MOTOR_B,MOTOR_FWD);
  PBOT.SPEED(MOTOR_BOTH,SAFE_SPEED);
}
void REVERSE()
{
  PBOT.DIRECTION(MOTOR_BOTH, MOTOR_REV);
  PBOT.SPEED(MOTOR_BOTH,100);
}
void STOP()
{
  PBOT.SPEED(MOTOR_BOTH,0);
}
void BUMP_THE_OPPONENTS_ON_LEFT()
{
  PBOT.DIRECTION(MOTOR_A,MOTOR_REV);
  PBOT.DIRECTION(MOTOR_B,MOTOR_FWD);
  PBOT.SPEED(MOTOR_BOTH,BUMP_SPEED_LEFT);
}
void BUMP_THE_OPPONENTS_ON_CENTER()
{
  PBOT.DIRECTION(MOTOR_BOTH,MOTOR_FWD);
  PBOT.SPEED(MOTOR_BOTH, BUMP_SPEED_CENTER);
}
void BUMP_THE_OPPONENTS_ON_RIGHT()
{
  PBOT.DIRECTION(MOTOR_A,MOTOR_FWD);
  PBOT.DIRECTION(MOTOR_B,MOTOR_REV);
  PBOT.SPEED(MOTOR_BOTH,BUMP_SPEED_RIGHT);
}

void TURN_LEFT()
{
  PBOT.DIRECTION(MOTOR_B, MOTOR_FWD);
  PBOT.SPEED(MOTOR_B, SAFE_SPEED);
  PBOT.DIRECTION(MOTOR_A, MOTOR_REV);
  PBOT.SPEED(MOTOR_A, 0);
}
void TURN_RIGHT()
{
  PBOT.DIRECTION(MOTOR_A, MOTOR_FWD);
  PBOT.SPEED(MOTOR_A, SAFE_SPEED);
  PBOT.DIRECTION(MOTOR_B, MOTOR_REV);
  PBOT.SPEED(MOTOR_B, 0);
}

