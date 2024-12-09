#include <Adafruit_NeoMatrix.h>
#include "matrix.h"

#define PIN 5         // Arduino pin 6 to DIN of 8x32 matrix.
#define LED_COUNT 256 // 8x32 = 256 NeoPixel leds
#define BRIGHTNESS 30 // to reduce current for 256 NeoPixels

#define BUTTON 26

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

int rgb_cycle = 10;
int rgb_index = 0;

void matrixSetup()
{
  matrix.begin();
  matrix.show();                    // Initialize all pixels to 'off'
  matrix.setBrightness(BRIGHTNESS); // overall brightness

  pinMode(BUTTON, INPUT);
}

void matrixLoop()
{
}

// Will still require matrix.show() after calling this function      
// For below, flip the signs if the matrix is upside down or not. upside down is additive because i said so
void drawCursor(int x, int y, uint16_t color)
{
  matrix.drawPixel(x, y, color);
}

// Arguments x and y are the original 1023x1023 coordinates from the camera
void setCursor(int x, int y)
{
  // Convert the 1023x1023 coordinates to 32x8 coordinates, handle edge cases idk
  x = map(x, 0, 1020, 0, 32);
  y = map(y, 0, 800, 0, 8);

  uint16_t colors[] = { matrix.Color(255, 0, 0), matrix.Color(255, 255, 0), matrix.Color(0, 255, 0), matrix.Color(0, 255, 255), matrix.Color(255, 0, 255), matrix.Color(0, 0, 255) };
    uint16_t color = matrix.Color(180, 180, 180);

    int buttonState = digitalRead(BUTTON);
    if (buttonState == LOW) matrix.clear();

    if (buttonState == HIGH) { // SELECTED (CLICKED)
      color = colors[map(rgb_index, 0, rgb_cycle, 0, 5)];
      rgb_index = (rgb_index + 1) % rgb_cycle;
    } 

    drawCursor(x, y, color);

    matrix.show();
}
