#include "gyro/gyro.h"
#include "matrix/matrix.h"

void setup()
{
    gyroSetup();
    matrixSetup();
}

void loop()
{
    gyroLoop();
    matrixLoop();
}