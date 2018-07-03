/*
  eGizmo_PBOT2018.h - eGizmo_PBOT2017 library for Wiring - description
  Copyright (c) 2018 e-Gizmo Mechatronix Central
  Codes by Sir Henry
  Rewritten for eGizmo_PBOT2018 library by Roma.  All right reserved.
*/
#ifndef eGizmo_PBOT2018_h 
#define eGizmo_PBOT2018_h

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <inttypes.h>
#include "Stream.h"
#include <string.h>
#include <stdbool.h>

#include <Wire.h>

#define bool int
#define true 1
#define false 0

// partype
#define P_NONE 0
#define P_BYTE 1
#define P_INT 2

// Command defines
#define TWI_MSPEEDA  0x10
#define TWI_MSPEEDB 0x11
#define TWI_MFWDA 0x12
#define TWI_MREVA 0x13
#define TWI_MFWDB 0x14
#define TWI_MREVB 0x15
#define TWI_MOFF  0x16  // Motor OFF
#define TWI_MON   0x17

#define TWI_SERVO1  0x20
#define TWI_SERVO2  0x21
#define TWI_SERVO3  0x22
#define TWI_SERVO4  0x23

#define MIN_PULSE_WIDTH       544     // the shortest pulse sent to a servo  
#define MAX_PULSE_WIDTH      2400     // the longest pulse sent to a servo 

#define TWI_READLINE  0x50
#define TWI_READCOL   0x51

#define MOTOR_A  1
#define MOTOR_B  2
#define MOTOR_BOTH  3
#define MOTOR_FWD true
#define MOTOR_REV false


class eGizmo_PBOT2018
{
  public:
    eGizmo_PBOT2018();
    void BEGIN();
    void BEGIN(uint8_t);

    void ALLON();
    void ALLOFF();
    void SPEED(uint8_t,uint8_t);
    void DIRECTION(uint8_t, bool);
    void SERVO(uint8_t,uint16_t);

    boolean COL1_RIGHT();
    boolean COL2_CENTER();
    boolean COL3_LEFT();

    boolean LS1_LEFT();
    boolean LS2_CENTER();
    boolean LS3_RIGHT();


    void twi_send(uint8_t,uint8_t,uint16_t,int8_t);
    void twi_send(int, int, int);

    byte twi_read(int, byte);


  private:
    byte device;
    int8_t min;                       // minimum is this value times 4 added to MIN_PULSE_WIDTH    
    int8_t max;                       // maximum is this value times 4 added to MAX_PULSE_WIDTH   
    
};
#endif

