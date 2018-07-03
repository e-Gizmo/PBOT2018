/*
  eGizmo_PBOT2018.cpp - eGizmo_PBOT2018 library for Wiring - implementation
  Copyright (c) 2018 e-Gizmo Mechatronix Central
  Codes by Sir Henry
  Rewritten for eGizmo_PBOT2018 library by Roma.  All right reserved.
*/

#include "eGizmo_PBOT2018.h"
#include "Wire.h"

#define SERVO_MIN() (MIN_PULSE_WIDTH - this->min * 4)
#define SERVO_MAX() (MAX_PULSE_WIDTH - this->max * 4)


eGizmo_PBOT2018::eGizmo_PBOT2018(){

}

// Public Methods ////////s//////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries
void eGizmo_PBOT2018::BEGIN()
{

  Wire.begin();
  eGizmo_PBOT2018::ALLON();
}

/* Motor Controls */

// Switch ON the motor driver
void  eGizmo_PBOT2018::ALLON() {
  twi_send(25, TWI_MON, 0, P_NONE);
}

// switch off the motor driver (all motors)
void  eGizmo_PBOT2018::ALLOFF() {
  twi_send(25, TWI_MOFF, 0, P_NONE);
}

// set motor speed
//  whichmotor = MOTOR_A, MOTOR_B, or MOTOR_BOTH
// speed = 0 to 255
// 0 = full stop
// Tip: To ensure motor run at low speed settings, start with a high speed for a fraction of a second
// and then set to the desired low speed

void eGizmo_PBOT2018::SPEED(uint8_t  whichmotor, uint8_t speed) {
  //if(speed>155) speed=155;  // limit speed to 155
  //if(speed>0) speed += 100; // minimum speed=100, 0=stop
  speed = ~speed;
  if (whichmotor == MOTOR_A) {
    twi_send(25, TWI_MSPEEDA, speed, P_BYTE);
  }
  if (whichmotor == MOTOR_B) {
    twi_send(25, TWI_MSPEEDB, speed, P_BYTE);
  }
  if (whichmotor == MOTOR_BOTH) {
    twi_send(25, TWI_MSPEEDB, speed, P_BYTE);
    twi_send(25, TWI_MSPEEDA, speed, P_BYTE);
  }

}

// set motor direction
//  whichmotor = MOTOR_A, MOTOR_B, or MOTOR_BOTH
// dir = MOTOR_FWD or MOTOR_REV
 
void eGizmo_PBOT2018::DIRECTION(uint8_t whichmotor, bool dir) {
  if (whichmotor == MOTOR_A) {
    if (dir) twi_send(25, TWI_MFWDA, 0, P_NONE);
    else twi_send(25, TWI_MREVA, 0, P_NONE);
  }
  if (whichmotor == MOTOR_B) {
    if (dir) twi_send(25, TWI_MFWDB, 0, P_NONE);
    else twi_send(25, TWI_MREVB, 0, P_NONE);
  }
  if (whichmotor == MOTOR_BOTH) {
    if (dir) {
      twi_send(25, TWI_MFWDA, 0, P_NONE);
      twi_send(25, TWI_MFWDB, 0, P_NONE);
    }
    else {
      twi_send(25, TWI_MREVA, 0, P_NONE);
      twi_send(25, TWI_MREVB, 0, P_NONE);
    }
  }
}
/*
    Servo Control
    whichservo - 1 to 4 ,ignore other values
    pulsewidth - 500 to 2499 (us)
                - value less than 500 stops the servo PWM generator
                - the pulsewidth converted to degrees from 0 to 180.
*/
void  eGizmo_PBOT2018::SERVO(uint8_t  whichservo, uint16_t pulsewidth) {
  if ((whichservo > 0) & (whichservo < 5)) {
    if(pulsewidth < MIN_PULSE_WIDTH)
    {
    if(pulsewidth < 0) pulsewidth = 0;
    if(pulsewidth > 180) pulsewidth =180;
    pulsewidth = map(pulsewidth,0,180,SERVO_MIN(), SERVO_MAX());
  }
  twi_send(25, whichservo + 0x1F, pulsewidth, P_INT);

}
}
/*
  Sensors
*/

// Read collision sensors
// input and output: sensor varaiable name (type struct csense)
//

boolean eGizmo_PBOT2018::COL1_RIGHT() {
   if(twi_read(25, TWI_READCOL) & 0x01)
    return true;
  else
    return false;
}
boolean eGizmo_PBOT2018::COL2_CENTER() {
   if(twi_read(25, TWI_READCOL) & 0x02)
    return true;
  else
    return false;
}
boolean eGizmo_PBOT2018::COL3_LEFT() {
   if(twi_read(25, TWI_READCOL) & 0x04)
    return true;
  else
    return false;
}

// Read line sensors
// input and output: sensor varaiable name (type struct lsense)
//

boolean eGizmo_PBOT2018::LS1_LEFT() {
   if(twi_read(25, TWI_READLINE) & 0x01)
    return true;
  else
    return false;
}
boolean eGizmo_PBOT2018::LS2_CENTER() {
   if(twi_read(25, TWI_READLINE) & 0x02)
    return true;
  else
    return false;
}

boolean eGizmo_PBOT2018::LS3_RIGHT() {
   if(twi_read(25, TWI_READLINE) & 0x04)
    return true;
  else
    return false;
}

/* TWI driver for the MBOT Controller
    MBOT device id device = 25
    command : Command type (see command defines)
    parameter : command parameter as may be required
    parameter type  partype : P_NONE - no parameter
                              P_BYTE - byte type parameter
                              P_INT  - integer type parameter
*/

// Send command and parameter to MBOT controller
void eGizmo_PBOT2018::twi_send(uint8_t device, uint8_t command, uint16_t parameter, int8_t partype) {
  Wire.beginTransmission(device);
  Wire.write(uint8_t(command));
  // 16 bit (integer) transfer, send data in two byte wide parts
  if (partype == P_INT) {
    Wire.write(highByte(parameter));  // high byte
    Wire.write(lowByte(parameter));   // low byte
  }
  if (partype == P_BYTE) {
    Wire.write((parameter));
  }
  Wire.endTransmission();             // close transfer
}

// Read command
byte eGizmo_PBOT2018::twi_read(int device, byte command) {
  // send command
  Wire.beginTransmission(device);
  Wire.write(uint8_t(command));
  Wire.endTransmission();
  delayMicroseconds(1);
  // read MBOT response
  Wire.requestFrom(device, 1);
  Wire.read();
}
