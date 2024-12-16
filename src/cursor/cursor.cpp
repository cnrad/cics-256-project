// Wii Remote IR sensor  test sample code  by kako http://www.kako.com
// modified output for Wii-BlobTrack program by RobotFreak http://www.letsmakerobots.com/user/1433
// modified for https://dfrobot.com by Lumi, Jan. 2014

#include <Wire.h>
#include <Arduino.h>
#include "Cursor.h"
#include "../Matrix/Matrix.h"

#define BUTTON 26

int IRsensorAddress = 0xB0;
int slaveAddress;
byte data_buf[16];
int i;

int Ix[4];
int Iy[4];
int s;

void Write_2bytes(byte d1, byte d2)
{
  Wire.beginTransmission(slaveAddress);
  Wire.write(d1);
  Wire.write(d2);
  Wire.endTransmission();
}

void cameraSetup()
{
  // Init button
  pinMode(BUTTON, INPUT);

  slaveAddress = IRsensorAddress >> 1; // This results in 0x21 as the address to pass to TWI
  Serial.begin(115200);
  Wire.begin();
  // IR sensor initialize
  Write_2bytes(0x30, 0x01);
  delay(10);
  Write_2bytes(0x30, 0x08);
  delay(10);
  Write_2bytes(0x06, 0x90);
  delay(10);
  Write_2bytes(0x08, 0xC0);
  delay(10);
  Write_2bytes(0x1A, 0x40);
  delay(10);
  Write_2bytes(0x33, 0x33);
  delay(10);
  delay(100);
}

int lastObservedX = 0;
int lastObservedY = 0;

void cameraLoop()
{
  // IR sensor read
  Wire.beginTransmission(slaveAddress);
  Wire.write(0x36);
  Wire.endTransmission();

  Wire.requestFrom(slaveAddress, 16); // Request the 2 byte heading (MSB comes first)
  for (int i = 0; i < 16; i++)
  {
    data_buf[i] = 0;
  }

  int i = 0;
  while (Wire.available() && i < 16)
  {
    data_buf[i] = Wire.read();
    i++;
  }

  Ix[0] = data_buf[1];
  Iy[0] = data_buf[2];
  s = data_buf[3];
  Ix[0] += (s & 0x30) << 4;
  Iy[0] += (s & 0xC0) << 2;

  Ix[1] = data_buf[4];
  Iy[1] = data_buf[5];
  s = data_buf[6];
  Ix[1] += (s & 0x30) << 4;
  Iy[1] += (s & 0xC0) << 2;

  Ix[2] = data_buf[7];
  Iy[2] = data_buf[8];
  s = data_buf[9];
  Ix[2] += (s & 0x30) << 4;
  Iy[2] += (s & 0xC0) << 2;

  Ix[3] = data_buf[10];
  Iy[3] = data_buf[11];
  s = data_buf[12];
  Ix[3] += (s & 0x30) << 4;
  Iy[3] += (s & 0xC0) << 2;

  // Don't remove this for now, this is used for the processing sketch of the 2d camera
  // for (i = 0; i < 4; i++)
  // {
  //   if (Ix[i] < 1000)
  //     Serial.print("");
  //   if (Ix[i] < 100)
  //     Serial.print("");
  //   if (Ix[i] < 10)
  //     Serial.print("");
  //   Serial.print(int(Ix[i]));
  //   Serial.print(",");
  //   if (Iy[i] < 1000)
  //     Serial.print("");
  //   if (Iy[i] < 100)
  //     Serial.print("");
  //   if (Iy[i] < 10)
  //     Serial.print("");
  //   Serial.print(int(Iy[i]));
  //   if (i < 3)
  //     Serial.print(",");
  // }

  if (Ix[0] != lastObservedX || Iy[0] != lastObservedY)
  {
    clearCursor(lastObservedX, lastObservedY);
  }

  // Lets assume one IR source is present
  if (Ix[0] != 1023 && Iy[0] != 1023)
  {
    setCursor(1023 - Ix[0], Iy[0]);
    lastObservedX = 1023 - Ix[0];
    lastObservedY = Iy[0];
  }
  else
  {
    // If there's no data, just set the cursor to the last point it was observed at
    setCursor(lastObservedX, lastObservedY);
  }

  Serial.println("");
}

// Returns normalized 32x8 coords
int *getCursorCoords()
{
  static int cursorCoords[2];

  int x = map(lastObservedX, 0, 1020, 0, 32);
  int y = map(lastObservedY, 0, 800, 0, 16);

  cursorCoords[0] = x;
  cursorCoords[1] = y;

  return cursorCoords;
}

boolean buttonPressed()
{
  return digitalRead(BUTTON) == HIGH;
}