#include "gyro/gyro.h"
#include "matrix/matrix.h"
#include "camera/camera.h"

void setup()
{
    gyroSetup();
    // matrixSetup();
    cameraSetup();
}

void loop()
{
    gyroLoop();
    // matrixLoop();
    cameraLoop();
}