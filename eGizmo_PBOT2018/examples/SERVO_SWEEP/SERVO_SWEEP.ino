/**********************************************
 * e-Gizmo PBOT2018 Controller - SERVO_SWEEP.ino
 * 
 * This is for SERVO sample sketch
 * to sweeps the shaft back and forth
 * across 180 degrees.
 * 
 * SERVO Control
 * ex. PBOT.SERVO(whichSERVO,pulsewidth);
 * where:
 * whichservo = 1 to 4 ,ignore other values
 * pulsewidth = 0 to 180 (degrees)
 * - value less than 500 stops the SERVO PWM generator
 * - the pulsewidth converted to degrees from 0 to 180 (default)
 * 
 * Codes by
 * e-Gizmo Mechatronix Central
 * http://www.e-gizmo.com
 * June 5,2018
 ************************************************/

#include "eGizmo_PBOT2018.h"
#include <Wire.h>

eGizmo_PBOT2018 PBOT; // Create PBOT object to control a SERVO
int POS = 0; //servo start position

void setup() {
  Wire.begin();
  PBOT.BEGIN();
}
void loop() {

  for(POS = 10; POS < 170; POS += 1)  // goes from 00 degrees to 170 degrees 
  {                                   // in steps of 1 degree 
    PBOT.SERVO(1, POS);               // tell servo to go to position in variable 'pos' 
    PBOT.SERVO(2, POS);
    PBOT.SERVO(3, POS); 
    PBOT.SERVO(4, POS); 
    delay(15);          
    // waits 15ms for the servo to reach the position 
  } 
  for(POS = 170; POS>=10; POS-=1)     // goes from 170 degrees to 10 degrees 
  {                                
    PBOT.SERVO(1, POS);               // tell servo to go to position in variable 'pos' 
    PBOT.SERVO(2, POS);
    PBOT.SERVO(3, POS); 
    PBOT.SERVO(4, POS); 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 

}


