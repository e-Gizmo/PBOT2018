/**********************************************
  e-Gizmo PBOT2018 Controller - MOTOR_TEST.ino

  This is for motor sample sketch to controls
  and move forward, reverse, turning right,
  turning left, and stop the motors.

  Set motor speed:
  PBOT.SPEED(whichmotor, speed);
  Note: Forward Speed = 0 Full Stop;255 High, limit 250

  Where: 
        whichmotor = MOTOR_A or MOTOR_B, MOTOR_BOTH
        speed = 0 to 255

  Set motor direction:
  PBOT.DIRECTION(whichmotor, dir);
  Where: 
        whichmotor = MOTOR_A or MOTOR_B, MOTOR_BOTH
        dir = MOTOR_FWD, MOTOR_REV;


  Codes by
  e-Gizmo Mechatronix Central
  http://www.e-gizmo.com
  June 5,2018
************************************************/

#include "eGizmo_PBOT2018.h"
#include <Wire.h>


eGizmo_PBOT2018 PBOT;
int SPEED = 120; //Set Speeds to 120 PWM

void setup() {
  Wire.begin();
  PBOT.BEGIN();
  PBOT.ALLON(); //Turn on all motors
  // Need for intial start of motors
  PBOT.SPEED(MOTOR_BOTH, 120); 
}

void loop() {

  //Move Forward
  PBOT.DIRECTION(MOTOR_BOTH, MOTOR_FWD);
  PBOT.SPEED(MOTOR_BOTH, 120);
  delay(2000);

  //Reverse
  PBOT.DIRECTION(MOTOR_BOTH, MOTOR_REV);
  PBOT.SPEED(MOTOR_BOTH, 120);
  delay(2000);
  
  //Turn Right
  PBOT.DIRECTION(MOTOR_A, MOTOR_FWD);
  PBOT.SPEED(MOTOR_A, 120);
  PBOT.SPEED(MOTOR_B, 0);
  delay(2000);
  
  //Turn Left
  PBOT.DIRECTION(MOTOR_B, MOTOR_FWD);
  PBOT.SPEED(MOTOR_B, 120);
  PBOT.SPEED(MOTOR_A, 0);
  delay(2000);
  
  //Stop
  PBOT.SPEED(MOTOR_BOTH, 0);
  delay(2000);

  //Extreme Right
  PBOT.DIRECTION(MOTOR_A, MOTOR_FWD);
  PBOT.DIRECTION(MOTOR_B, MOTOR_REV);
  PBOT.SPEED(MOTOR_BOTH, 120);
  delay(2000);

  //Extreme Left
  PBOT.DIRECTION(MOTOR_A,MOTOR_REV);
  PBOT.DIRECTION(MOTOR_B,MOTOR_FWD);
  delay(2000);
}


