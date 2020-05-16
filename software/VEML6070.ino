/*
  Example sketch for VEML6070-Breakout (Digital UV Light Sensor).
  Rset=270k on breakout, UVA sensitivity: 5.625 uW/cm²/step

  Board           I2C/TWI Pins
                  SDA, SCL
  ----------------------------
  Uno, Ethernet    A4, A5
  Mega             20, 21
  Leonardo          2,  3
  Due              20, 21

  Integration Times and UVA Sensitivity:
    Rset=240k -> 1T=100.0ms ->   5.000 uW/cm²/step
    Rset=270k -> 1T=112.5ms ->   5.625 uW/cm²/step
    Rset=300k -> 1T=125.0ms ->   6.250 uW/cm²/step
    Rset=600k -> 1T=250.0ms ->  12.500 uW/cm²/step

  Example source code free to use.
  Further information: https://learn.watterott.com/license/
*/

#include <Wire.h>

#define I2C_ADDR 0x38 //0x38 and 0x39

//Integration Time
#define IT_1_2 0x0 //1/2T
#define IT_1   0x1 //1T
#define IT_2   0x2 //2T
#define IT_4   0x3 //4T

void setup()
{
  Serial.begin(9600);
  while(!Serial); //wait for serial port to connect (needed for Leonardo only)

  Wire.begin();

  Wire.beginTransmission(I2C_ADDR);
  Wire.write((IT_1<<2) | 0x02);
  Wire.endTransmission();
  delay(500);
}

void loop()
{
  byte msb=0, lsb=0;
  uint16_t uv;

  Wire.requestFrom(I2C_ADDR+1, 1); //MSB
  delay(1);
  if(Wire.available())
    msb = Wire.read();

  Wire.requestFrom(I2C_ADDR+0, 1); //LSB
  delay(1);
  if(Wire.available())
    lsb = Wire.read();

  uv = (msb<<8) | lsb;
  Serial.println(uv, DEC); //output in steps (16bit)

  delay(1000);
}
