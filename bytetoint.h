union uIntToByte
{
    int16_t intValue;
    unsigned char byteArray[sizeof(int16_t)];
};
