#include <Adafruit_NeoMatrix.h>
#include "matrix.h"
#include "src/cursor/cursor.h"
#include <string>
using namespace std;

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

int rgb_cycle = 10;
int rgb_index = 0;

void matrixSetup()
{
  matrix.begin();
  matrix.show();                    // Initialize all pixels to 'off'
  matrix.setBrightness(BRIGHTNESS); // overall brightness
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

  uint16_t colors[] = {matrix.Color(255, 0, 0), matrix.Color(255, 255, 0), matrix.Color(0, 255, 0), matrix.Color(0, 255, 255), matrix.Color(255, 0, 255), matrix.Color(0, 0, 255)};
  uint16_t color = matrix.Color(180, 180, 180);

  if (buttonPressed())
  { // SELECTED (CLICKED)
    color = colors[map(rgb_index, 0, rgb_cycle, 0, 5)];
    rgb_index = (rgb_index + 1) % rgb_cycle;
  }

  drawCursor(x, y, color);
}

void clearCursor(int x, int y)
{
  // Convert the 1023x1023 coordinates to 32x8 coordinates, handle edge cases idk
  x = map(x, 0, 1020, 0, 32);
  y = map(y, 0, 800, 0, 8);
  matrix.drawPixel(x, y, matrix.Color(0, 0, 0));
}

void drawRect(int x, int y, int w, int h, uint16_t color)
{
  matrix.drawRect(x, y, w, h, color);
}

void fillRect(int x, int y, int w, int h, uint16_t color)
{
  matrix.fillRect(x, y, w, h, color);
}

const uint8_t font[26][4] = {
    {0b111, 0b101, 0b111, 0b101}, // A
    {0b110, 0b101, 0b110, 0b101}, // B
    {0b111, 0b100, 0b100, 0b111}, // C
    {0b110, 0b101, 0b101, 0b110}, // D
    {0b111, 0b100, 0b110, 0b111}, // E
    {0b111, 0b100, 0b110, 0b100}, // F
    {0b111, 0b100, 0b101, 0b111}, // G
    {0b101, 0b101, 0b111, 0b101}, // H
    {0b111, 0b010, 0b010, 0b111}, // I
    {0b111, 0b001, 0b001, 0b110}, // J
    {0b101, 0b110, 0b110, 0b101}, // K
    {0b100, 0b100, 0b100, 0b111}, // L
    {0b101, 0b111, 0b101, 0b101}, // M
    {0b101, 0b111, 0b111, 0b101}, // N
    {0b111, 0b101, 0b101, 0b111}, // O
    {0b111, 0b101, 0b111, 0b100}, // P
    {0b111, 0b101, 0b111, 0b011}, // Q
    {0b111, 0b101, 0b111, 0b101}, // R
    {0b111, 0b100, 0b111, 0b011}, // S
    {0b111, 0b010, 0b010, 0b010}, // T
    {0b101, 0b101, 0b101, 0b111}, // U
    {0b101, 0b101, 0b101, 0b010}, // V
    {0b101, 0b101, 0b111, 0b101}, // W
    {0b101, 0b010, 0b010, 0b101}, // X
    {0b101, 0b101, 0b111, 0b010}, // Y
    {0b111, 0b010, 0b010, 0b111}  // Z
};

void drawChar(int x, int y, char letter, uint16_t color)
{
  // Define a simple 3x4 font for letters A-Z

  // Convert letter to uppercase and get the index
  letter = toupper(letter);
  if (letter < 'A' || letter > 'Z')
    return; // Only support A-Z
  int index = letter - 'A';

  // Draw the character
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if (font[index][i] & (1 << (2 - j)))
      {
        matrix.drawPixel(x + j, y + i, color);
      }
    }
  }
}

void drawString(int x, int y, String text, uint16_t color)
{
  for (int i = 0; i < text.length(); i++)
  {
    drawChar(x + i * 4, y, text[i], color);
  }
}

void scrollText(String text, uint16_t color)
{
  unsigned long time = millis();
  int textLength = text.length();
  int textWidth = textLength * 4;
  int x = 32;
  while (x > -textWidth)
  {
    if (millis() - time > 100)
    {
      drawString(x + 1, 0, text, matrix.Color(0, 0, 0));
      drawString(x, 0, text, color);
      matrix.show();
      x--;
      time = millis();
    }
  }
}

uint16_t color(int r, int g, int b)
{
  return matrix.Color(r, g, b);
}

void showMatrix()
{
  matrix.show();
}