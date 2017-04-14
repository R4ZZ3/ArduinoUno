//Serial Relay - Arduino will patch a 
//serial link between the computer and the GPRS Shield
//at 19200 bps 8-N-1
//Computer is connected to Hardware UART
//GPRS Shield is connected to the Software UART 

#include <SoftwareSerial.h>

SoftwareSerial GPRS(7, 8);

unsigned char buffer[64];  // buffer array for data receive over serial port
int count=0;               // counter for buffer array 

void setup()
{
  GPRS.begin(19200);
  Serial.begin(19200);
}

void loop()
{
  if (GPRS.available())
  {
    while(GPRS.available())
    {
      buffer[count++]=GPRS.read();
      if(count == 64)break;
    }
    Serial.write(buffer,count);
    clearBufferArray();
    count = 0;
  }
  if (Serial.available())
    GPRS.write(Serial.read());
}

void clearBufferArray()
{
  for (int i=0; i<count;i++)
  {
    buffer[i]=NULL;
  }
}
