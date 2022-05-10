unsigned char write_parameters(String s1, String s2)
{
  if (s1 == "P" && s2 == "KP")
  {
    // Position and Kp
    return writePositionKp;
  }
  else if (s1 == "P" && s2 == "KI")
  {
    // Position and Ki
    return writePositionKi;
  }
  else if (s1 == "S" && s2 == "KP")
  {
    // Speed and Kp
    return writeSpeedKp;
  }
  else if (s1 == "S" && s2 == "KI")
  {
    // Speed and Ki
    return writeSpeedKi;
  }
  else if (s1 == "C" && s2 == "KP")
  {
    // Current and Kp
    return writeCurrentKp;
  }
  else if (s1 == "C" && s2 == "KI")
  {
    // Current and Ki
    return writeCurrentKi;
  }
  else if (s1 == "T") {
    // Torque
    return setTorque;
  }
}
