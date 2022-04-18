void process_command()
{
  console.log("Send: ");
  mcp2515.sendMessage(&canMsg);
  console.log(canMsg.can_id, canMsg.data);

  uFloatToByte V;

  int len = 10;
  while ((mcp2515.readMessage(&canMsg) != MCP2515::ERROR_OK))
  {
    delay(100);
    len--;
    if ((len <= 0))
    {
      break;
    }
    readyFlag = false;
  }
  if (len > 0)
  {
    console.log("Recv: ");
    console.log(canMsg.can_id, canMsg.data);

    console.log("canMsg.data float: ");
    V.byteArray[0] = canMsg.data[7];
    V.byteArray[1] = canMsg.data[6];
    V.byteArray[2] = canMsg.data[5];
    V.byteArray[3] = canMsg.data[4];
    console.log(V.floatValue);
  }
  else
  {
    console.log("Recv   : NO ANSWER");
  }
}
