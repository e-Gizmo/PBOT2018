/**********************************************
  e-Gizmo PBOT Controller - AVOID COLLISION.ino

  This is for collsion sample sketch to avoid
  crashing on the wall or any objects that blocking
  way of the PBOT.

  Reading the 3channel Collision sensors:

  PBOT.COL1_RIGHT();
  PBOT.COL2_CENTER();
  PBOT.COL3_LEFT();

  Output reads:
       No object detection = 0 or LOW;
       Object detected     = 1 or HIGH;

  Codes by
  e-Gizmo Mechatronix Central
  http://www.e-gizmo.net
  June 5,2018
************************************************/

#include "eGizmo_PBOT2018.h"
#include <Wire.h>


eGizmo_PBOT2018 PBOT;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  PBOT.BEGIN();
  PBOT.ALLON();
  PBOT.SPEED(MOTOR_BOTH, 120);
}

void loop() {
  if(PBOT.COL2_CENTER()){ //center object detection
   change_direction(); 
  }
  delay(200);
}

//Sample Function for changing directions
void  change_direction(void) {
  boolean cw = HIGH;
  PBOT.DIRECTION(MOTOR_BOTH, MOTOR_REV);

  delay(500);
  if (cw) {
    cw = false;
    PBOT.DIRECTION(MOTOR_A, MOTOR_FWD);

  } else {
    cw = true;
    PBOT.DIRECTION(MOTOR_B, MOTOR_FWD);
  }
  delay(500);
  PBOT.DIRECTION(MOTOR_BOTH, MOTOR_FWD);
}
