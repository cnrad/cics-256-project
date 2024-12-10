#include "gyro/gyro.h"
#include "matrix/matrix.h"
#include "cursor/cursor.h"
#include "game/GameObject/GameObject.h"
void setup()
{
    matrixSetup();
    cameraSetup();
}

int gameIndex = 0; // 0 for menu

void loop()
{
    cameraLoop();
    // GameManager gameManager;
    // gameManager.run();

    // games[gameIndex].update()

    // This runs every time and determines the game speed!!!
    showMatrix();
    delay(10);
}

// #include <Wire.h>
// #include <Arduino.h>

// void setup()
// {
//     Wire.begin();

//     Serial.begin(115200);
//     while (!Serial)
//         ; // Leonardo: wait for serial monitor
//     Serial.println("\nI2C Scanner");
// }

// void loop()
// {
//     byte error, address;
//     int nDevices;

//     Serial.println("Scanning...");

//     nDevices = 0;
//     for (address = 1; address < 127; address++)
//     {
//         // The i2c_scanner uses the return value of
//         // the Write.endTransmisstion to see if
//         // a device did acknowledge to the address.
//         Wire.beginTransmission(address);
//         error = Wire.endTransmission();

//         if (error == 0)
//         {
//             Serial.print("I2C device found at address 0x");
//             if (address < 16)
//                 Serial.print("0");
//             Serial.print(address, HEX);
//             Serial.println("  !");

//             nDevices++;
//         }
//         else if (error == 4)
//         {
//             Serial.print("Unknown error at address 0x");
//             if (address < 16)
//                 Serial.print("0");
//             Serial.println(address, HEX);
//         }
//     }
//     if (nDevices == 0)
//         Serial.println("No I2C devices found\n");
//     else
//         Serial.println("done\n");

//     delay(5000); // wait 5 seconds for next scan
// }