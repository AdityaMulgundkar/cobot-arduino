/*
  Command | Output
  --------------------------------

  TO-DOs:
  1. Wrap Final Serial output

*/

#include <SPI.h>     //Library for using SPI Communication
#include <mcp2515.h> //Library for using CAN Communication
#include "console.h"

#define SERIAL_BAUD_RATE 115200
#define SERIAL_TIMEOUT 300

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
  canMsg.can_id = 0x141;
  canMsg.can_dlc = 0x08;

  unsigned char charset[8] = {0x9A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  for(int i = 0; i<8; i++) {
    canMsg.data[i] = charset[i];
  }

  Serial.print("Send(1): ");

  mcp2515.sendMessage(&canMsg);
  printserial(canMsg.can_id, canMsg.data);
  Serial.print("\n");
  int len = 10;
  while ((mcp2515.readMessage(&canMsg) != MCP2515::ERROR_OK))
  {
    delay(1);
    len--;
    if ((len <= 0))
    {
      break;
    }
  }

  if (len > 0)
  {
    Serial.print("Recv   : ");
    printserial(canMsg.can_id, canMsg.data);
    Serial.print("\n");
  }
  else
  {
    Serial.print("Recv   : NO ANSWER");
    Serial.print("\n");
  }

  Serial.print("\n");

    delay(100);
  Serial.print("\n");
}