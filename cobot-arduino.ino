/*
  Command | Output
  --------------------------------

  TO-DOs:
  1. Wrap Final Serial output
  
  Rishabhs TODOs:
  1. Torque feedback
  2. Position feedback
  3. Velocity feedback
  4. Home position - get and set
  5. ROS Serial
  6. Tele-op


  Sample packet:
  RC1,KP // Read Current KP for Motor 1
  SC1,KP,0.1 // Read Current KP for Motor 1
  SC1,Kp,1RC1,KP,0.001
  SC1,Ki,0
  ST
*/

#include <SPI.h>     //Library for using SPI Communication
#include <mcp2515.h> //Library for using CAN Communication
#include "console.h"
#include "bytetofloat.h"
#include "bytetoint.h"

#define SERIAL_BAUD_RATE 115200
#define SERIAL_TIMEOUT 300

// COMMAND DEFINITIONS
unsigned char stopMotor = 0x81;

unsigned char readMotor1Status = 0x9A;
unsigned char readMotor2Status = 0x9C;
unsigned char readMotor3Status = 0x9D;

unsigned char readPositionKp = 0x30;
unsigned char readPositionKi = 0x31;

unsigned char readSpeedKp = 0x32;
unsigned char readSpeedKi = 0x33;

unsigned char readCurrentKp = 0x34;
unsigned char readCurrentKi = 0x35;

unsigned char writePositionKp = 0x36;
unsigned char writePositionKi = 0x37;

unsigned char writeSpeedKp = 0x38;
unsigned char writeSpeedKi = 0x39;

unsigned char writeCurrentKp = 0x3A;
unsigned char writeCurrentKi = 0x3B;

unsigned char setTorque = 0xA2;

// CAN IDs FOR MOTORS
#define M1_CAN 0x141
#define M2_CAN 0x142
#define M3_CAN 0x143

// ERROR CODES
#define ERROR_200 200 // Success
#define ERROR_1 1     //
#define ERROR_11 11   // Out of memory range
#define ERROR_15 15   // write memory addr is greater than read

console console;

// TO-DO: Clean up bytes in dynamic memory

struct can_frame canMsg;

MCP2515 mcp2515(10);

int incomingByte = 1;
char command_arg_char[12];
uint8_t command_arg_byte[45];
bool readyFlag = false;

void setup()
{
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.setTimeout(SERIAL_TIMEOUT);
  mcp2515.reset();
  mcp2515.setBitrate(CAN_1000KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();
  console.log("Setup done.");
}

void printserial(unsigned long ID, unsigned char buf[8])
{
  Serial.print(ID, HEX);
  Serial.print(": ");
  for (int i = 0; i < 8; i++)
  {
    Serial.print(buf[i], HEX);
    Serial.print("  ");
  }
}

void loop()
{
  if (Serial.available() > 0)
  {
    read_command();
  }

  if (readyFlag)
  {
    readyFlag = false;
    process_command();
  }
}
