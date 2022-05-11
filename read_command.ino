void read_command()
{
  // Sample packet
  // SC1,KP,0.001
  // RC1,KP,0.001
  // SC1,Kp,0.25
  // SC1,Ki,0.25

  canMsg.can_dlc = 0x08;

  memset(command_arg_char, 0, sizeof(command_arg_char));
  Serial.readBytes(command_arg_char, 12);

  console.log("Command Data: ", command_arg_char);
  String cmd_str = String(command_arg_char);
  cmd_str.toUpperCase();

  String cmd_motor_str = "";
  String cmd_str_1 = "";
  String cmd_str_2 = "";
  String cmd_str_3 = "";

  cmd_motor_str = cmd_str.substring(2, 3);
  int cmd_motor = cmd_motor_str.toInt();
  cmd_str_1 = cmd_str.substring(1, 2);
  cmd_str_2 = cmd_str.substring(4, 6);
  cmd_str_3 = cmd_str.substring(7, 12);

  // Set CAN ID for selected Motor
  cmd_motor == 3 ? canMsg.can_id = M3_CAN : (cmd_motor == 2 ? canMsg.can_id = M2_CAN : canMsg.can_id = M1_CAN);
  console.log("CAN ID (DEC): ", canMsg.can_id);

  console.log("Motor choice: ", cmd_motor);
  console.log("Value:        ", cmd_str_1);
  console.log("Param:        ", cmd_str_2);

  if(cmd_str.charAt(0) == '0')
  {
    // DISABLE
    console.log("Mode:         Disable Motor");
    canMsg.data[0] = 0x81;
    for (int i = 1; i < 8; i++)
    {
      canMsg.data[i] = 0x00;
    }
  }
  else if (cmd_str.charAt(0) == '1')
  {
    // ENABLE
    console.log("Mode:         Enable Motor");
    canMsg.data[0] = 0x88;
    for (int i = 1; i < 8; i++)
    {
      canMsg.data[i] = 0x00;
    }
  }
  else if (cmd_str.charAt(0) == '2')
  {
    // STOP
    console.log("Mode:         Stop Motor");
    canMsg.data[0] = 0x80;
    for (int i = 1; i < 8; i++)
    {
      canMsg.data[i] = 0x00;
    }
  }
  else if (cmd_str.charAt(0) == '3')
  {
    // RESET
    console.log("Mode:         Reset Motor");
    canMsg.data[0] = 0x76;
    for (int i = 1; i < 8; i++)
    {
      canMsg.data[i] = 0x00;
    }
  }
  else if (cmd_str.charAt(0) == '4')
  {
    // RESET
    console.log("Mode:         Motor 1 Status");
    canMsg.data[0] = 0x9A;
    for (int i = 1; i < 8; i++)
    {
      canMsg.data[i] = 0x00;
    }
  }
  else if (cmd_str.charAt(0) == 'R')
  {
    // READ
    console.log("Mode:         Read");
    canMsg.data[0] = read_parameters(cmd_str_1, cmd_str_2);
    for (int i = 1; i < 8; i++)
    {
      canMsg.data[i] = 0x00;
    }
  }
  else if (cmd_str.charAt(0) == 'S')
  {
    // SET / WRITE
    console.log("Mode:         Write");
    canMsg.data[0] = write_parameters(cmd_str_1, cmd_str_2);
    if(cmd_str.charAt(1) != 'T')
    {
      console.log("Float");
      // Float - Kp, Ki
      uFloatToByte V;
      V.floatValue = cmd_str_3.toFloat();
      
      canMsg.data[1] = 0x00;
      canMsg.data[2] = 0x00;
      canMsg.data[3] = 0x00;
      canMsg.data[4] = V.byteArray[0];
      canMsg.data[5] = V.byteArray[1];
      canMsg.data[6] = V.byteArray[2];
      canMsg.data[7] = V.byteArray[3];
    }
    else 
    {
      console.log("Torque");
      // Int - Torque
      // ST,2000
      uIntToByte V;
      cmd_str_3 = cmd_str.substring(3, 7);
      console.log("Setting Torque:", cmd_str_3);
      V.intValue = cmd_str_3.toInt();
      uint8_t someInt = cmd_str_3.toInt();
      
      canMsg.data[1] = 0x00;
      canMsg.data[2] = 0x00;
      canMsg.data[3] = 0x00;
      canMsg.data[4] = V.byteArray[0];
      canMsg.data[5] = V.byteArray[1];
      canMsg.data[6] = 0x00;
      canMsg.data[7] = 0x00;
    }
  }
  readyFlag = true;
  delay(100);
}
