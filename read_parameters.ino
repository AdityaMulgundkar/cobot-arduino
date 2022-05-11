unsigned char read_parameters(String s1, String s2)
{
  // Sample packet
  // RC1,KP,0.001
  // ST1,KP,0.001 WORKING
  // SC1,Kp,0.25
  // SC1,Ki,0.25
  // ST,
  if (s1 == "P" && s2 == "KP")
  {
    // Position and Kp
    return readPositionKp;
  }
  else if (s1 == "P" && s2 == "KI")
  {
    // Position and Ki
    return readPositionKi;
  }
  else if (s1 == "S" && s2 == "KP")
  {
    // Speed and Kp
    return readSpeedKp;
  }
  else if (s1 == "S" && s2 == "KI")
  {
    // Speed and Ki
    return readSpeedKi;
  }
  else if (s1 == "C" && s2 == "KP")
  {
    // Current and Kp
    return readCurrentKp;
  }
  else if (s1 == "C" && s2 == "KI")
  {
    // Current and Ki
    return readCurrentKi;
  }
}
