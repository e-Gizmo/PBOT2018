/**********************************************
 * e-Gizmo PBOT2018 Controller - LINEBOT.ino
 * 
 * This is for Linesensor sample sketch to
 * follows the black line or white line track.
 * 
 * Reading the 3channel Line sensors:
 * Calibration Instructions:
 * For the new eGizmo PBOT2017 Controller features
 * first thing to do is to calibrate the line
 * sensors. How to calibrate it? Read the ff.
 * 1. After uploading your code for linesensors.
 * Turn OFF the POWER switch.
 * 2. Place the eGizmo PBOT controller to the "black
 * line" then Press and Hold LINE CAL and SYS RST,
 * while pressing and holding the buttons, Turn ON
 * the POWER Switch. LN2 (D12 LED indicator) is ON.
 * 3. First RELEASE the SYS RST followed by LINE CAL.
 * Make sure the 3CH Line sensors are faces on the
 * "black line" and you will see the LN1 and LN3
 * (D11 and D13 LED indicators) are
 * Turn ON and LN1 is blinking. Now Press LINE CAL
 * once for the white color calibration.
 * 4. Next, if the L3 (D13 LED indicator) is blinking.
 * Place the 3CH Line sensors on the "White track". then
 * Press LINE CAL again once for the black color
 * calibration. After that you will see all the LEDS
 * for linesensors are ON.
 * 5. Now your eGizmo PBOT Controller line sensors
 * are calibrated. Then Press the RESET button.
 * You can now trace the line and DONE.
 * 
 * PBOT.LS1_LEFT();
 * PBOT.LS2_CENTER();
 * PBOT.LS3_RIGHT();
 * 
 * Note: 
 * Output reads:
 * White line detected = 0 or LOW;
 * Black line detected = 1 or HIGH;
 * 
 * Codes by
 * e-Gizmo Mechatronix Central
 * http://www.e-gizmo.net
 * June 5,2018
 ************************************************/
#include <Wire.h>
#include "eGizmo_PBOT2018.h"


eGizmo_PBOT2018 PBOT;
int SP1 = 80;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  PBOT.BEGIN();
  PBOT.ALLON();
  PBOT.SPEED(MOTOR_BOTH, SP1);

}
void loop() 
{
  if(PBOT.LS1_LEFT() == LOW && PBOT.LS3_RIGHT() == LOW)
  {
    FORWARD();
  }
  if(PBOT.LS1_LEFT() == LOW && PBOT.LS3_RIGHT() == HIGH)
  {
    TURN_RIGHT();
  }
  if(PBOT.LS1_LEFT() == HIGH && PBOT.LS3_RIGHT() == LOW)
  {
    TURN_LEFT();
  }
  if(PBOT.LS1_LEFT() == LOW && PBOT.LS2_CENTER() == LOW && PBOT.LS3_RIGHT() == LOW)
  {
    REVERSE();
    delay(200);
  }
  //UNCOMMENT THIS FOR STOPPING POINT
 /* if(PBOT.LS1_LEFT() == HIGH && PBOT.LS3_RIGHT() == HIGH)
  {
    STOP();
  }*/
}
void FORWARD(void)
{
  PBOT.DIRECTION(MOTOR_BOTH,MOTOR_FWD);
  PBOT.SPEED(MOTOR_BOTH,SP1);
}
void REVERSE()
{
  PBOT.DIRECTION(MOTOR_BOTH, MOTOR_REV);
  PBOT.SPEED(MOTOR_BOTH,SP1);
}
void TURN_LEFT()
{
  PBOT.DIRECTION(MOTOR_B, MOTOR_FWD);
  PBOT.SPEED(MOTOR_B, SP1);
  PBOT.DIRECTION(MOTOR_A, MOTOR_REV);
  PBOT.SPEED(MOTOR_A, 0);
}
void TURN_RIGHT()
{
  PBOT.DIRECTION(MOTOR_A, MOTOR_FWD);
  PBOT.SPEED(MOTOR_A, SP1);
  PBOT.DIRECTION(MOTOR_B, MOTOR_REV);
  PBOT.SPEED(MOTOR_B, 0);
}
void STOP()
{
  PBOT.SPEED(MOTOR_BOTH,0);
}
