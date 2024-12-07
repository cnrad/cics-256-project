#include <Adafruit_NeoMatrix.h>
#include "matrix.h"

#define PIN 5         // Arduino pin 6 to DIN of 8x32 matrix.
#define LED_COUNT 256 // 8x32 = 256 NeoPixel leds
#define BRIGHTNESS 30 // to reduce current for 256 NeoPixels

#define MATRIX_WIDTH 32
#define MATRIX_HEIGHT 8
#define MATRIX_LAYOUT (NEO_MATRIX_BOTTOM + NEO_MATRIX_RIGHT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG)
// MATRIX DECLARATION:
// Parameter 1 = width of NeoPixel matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(MATRIX_WIDTH, MATRIX_HEIGHT, PIN,
                                               MATRIX_LAYOUT,
                                               NEO_GRB + NEO_KHZ800);
void matrixSetup()
{
  matrix.begin();
  matrix.show();                    // Initialize all pixels to 'off'
  matrix.setBrightness(BRIGHTNESS); // overall brightness
}

void matrixLoop()
{
}

void setCursor(int x, int y)
{
  if (x != 32 && y != 8)
  {
    matrix.clear();

    // int index = y * 32 + x; // Calculate the index for the 8x32 matrix
    matrix.drawPixel(x - 1, y, matrix.Color(255, 255, 255));
    matrix.drawPixel(x, y, matrix.Color(255, 255, 255));
    matrix.drawPixel(x, y - 1, matrix.Color(255, 255, 255));
    matrix.drawPixel(x - 1, y - 1, matrix.Color(255, 255, 255));
    matrix.show();
  }
}

// Fill the dots one after the other with a color
