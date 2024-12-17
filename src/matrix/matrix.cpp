#include <Adafruit_Protomatter.h>
#include "src/Cursor/Cursor.h"
#include <string>

#define LED_COUNT 512 // 16x32 = 256 NeoPixel leds
#define BRIGHTNESS 30 // to reduce current for 256 NeoPixels

#define MATRIX_WIDTH 32
#define MATRIX_HEIGHT 16
#define MATRIX_LAYOUT (NEO_MATRIX_BOTTOM + NEO_MATRIX_RIGHT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG)

#define A A16
#define B A17
#define C A5
#define NC A4

#define OE 23
#define LAT 19
#define CLK 18
#define G1 2  // 2/LED
#define G2 13 //
#define R1 4
#define R2 12
#define B5 15
#define B2 5
uint8_t rgbPins[] = {R1, G1, B5, R2, G2, B2};
uint8_t addrPins[] = {A, B, C, NC};

Adafruit_Protomatter matrix = Adafruit_Protomatter(MATRIX_WIDTH, 4, 1, rgbPins, 3, addrPins, CLK, LAT, OE, false);

void matrixSetup()
{
  // Initialize matrix...
  Serial.println("Starting...");

  ProtomatterStatus status = matrix.begin();

  if (status != PROTOMATTER_OK)
  {
    Serial.print("PROTOMATTER NOT OK: ");
    Serial.println((int)status);
  };
}

// Will still require matrix.show() after calling this function
// For below, flip the signs if the matrix is upside down or not. upside down is additive because i said so
void drawCursor(int x, int y, uint16_t color)
{
  matrix.drawPixel(x, y, color);
  matrix.drawPixel(x + 1, y, color);
  matrix.drawPixel(x, y + 1, color);
}
void drawTarget(int x, int y, uint16_t color)
{
  matrix.drawPixel(x, y, color);
  matrix.drawPixel(x + 1, y, color);
  matrix.drawPixel(x, y + 1, color);
  matrix.drawPixel(x -1, y, color);
  matrix.drawPixel(x , y-1, color);
}
// Arguments x and y are the original 1023x1023 coordinates from the camera
void setCursor(int x, int y)
{
  // Convert the 1023x1023 coordinates to 32x16 coordinates, handle edge cases idk
  x = map(x, 0, 1020, 0, 32);
  y = map(y, 0, 800, 0, 16);

  uint16_t color = matrix.color565(180, 180, 180);

  if (buttonPressed())
  { // SELECTED (CLICKED)
    color = matrix.color565(255, 255, 255);
  }

  drawCursor(x, y, color);
}

void clearCursor(int x, int y)
{
  // Convert the 1023x1023 coordinates to 32x8 coordinates, handle edge cases idk
  x = map(x, 0, 1020, 0, 32);
  y = map(y, 0, 800, 0, 16);
  matrix.drawPixel(x, y, matrix.color565(0, 0, 0));
}

void drawRect(int x, int y, int w, int h, uint16_t color)
{
  matrix.drawRect(x, y, w, h, color);
}

void fillRect(int x, int y, int w, int h, uint16_t color)
{
  matrix.fillRect(x, y, w, h, color);
}

const uint8_t font[37][6] = {
    {0b11110, 0b10001, 0b11111, 0b10001, 0b10001, 0b10001}, // A
    {0b11110, 0b10001, 0b11110, 0b10001, 0b10001, 0b11110}, // B
    {0b11111, 0b10000, 0b10000, 0b10000, 0b10000, 0b11111}, // C
    {0b11110, 0b10001, 0b10001, 0b10001, 0b10001, 0b11110}, // D
    {0b11111, 0b10000, 0b11110, 0b10000, 0b10000, 0b11111}, // E
    {0b11111, 0b10000, 0b11110, 0b10000, 0b10000, 0b10000}, // F
    {0b11111, 0b10000, 0b10111, 0b10001, 0b10001, 0b11111}, // G
    {0b10001, 0b10001, 0b11111, 0b10001, 0b10001, 0b10001}, // H
    {0b11111, 0b00100, 0b00100, 0b00100, 0b00100, 0b11111}, // I
    {0b11111, 0b00001, 0b00001, 0b00001, 0b10001, 0b11111}, // J
    {0b10001, 0b10010, 0b11100, 0b10010, 0b10001, 0b10001}, // K
    {0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b11111}, // L
    {0b10001, 0b11011, 0b10101, 0b10001, 0b10001, 0b10001}, // M
    {0b10001, 0b11001, 0b10101, 0b10011, 0b10001, 0b10001}, // N
    {0b11111, 0b10001, 0b10001, 0b10001, 0b10001, 0b11111}, // O
    {0b11111, 0b10001, 0b11111, 0b10000, 0b10000, 0b10000}, // P
    {0b11111, 0b10001, 0b10001, 0b10011, 0b10010, 0b11101}, // Q
    {0b11111, 0b10001, 0b11111, 0b10010, 0b10001, 0b10001}, // R
    {0b11111, 0b10000, 0b11111, 0b00001, 0b00001, 0b11111}, // S
    {0b11111, 0b00100, 0b00100, 0b00100, 0b00100, 0b00100}, // T
    {0b10001, 0b10001, 0b10001, 0b10001, 0b10001, 0b11111}, // U
    {0b10001, 0b10001, 0b10001, 0b01010, 0b01010, 0b00100}, // V
    {0b10001, 0b10001, 0b10101, 0b10101, 0b11011, 0b10001}, // W
    {0b10001, 0b01010, 0b00100, 0b00100, 0b01010, 0b10001}, // X
    {0b10001, 0b10001, 0b01010, 0b00100, 0b00100, 0b00100}, // Y
    {0b11111, 0b00010, 0b00100, 0b01000, 0b10000, 0b11111}, // Z
    {0b11111, 0b10001, 0b10001, 0b10001, 0b10001, 0b11111}, // 0
    {0b00100, 0b01100, 0b00100, 0b00100, 0b00100, 0b01110}, // 1
    {0b11111, 0b00001, 0b11111, 0b10000, 0b10000, 0b11111}, // 2
    {0b11111, 0b00001, 0b11111, 0b00001, 0b00001, 0b11111}, // 3
    {0b10001, 0b10001, 0b11111, 0b00001, 0b00001, 0b00001}, // 4
    {0b11111, 0b10000, 0b11111, 0b00001, 0b00001, 0b11111}, // 5
    {0b11111, 0b10000, 0b11111, 0b10001, 0b10001, 0b11111}, // 6
    {0b11111, 0b00001, 0b00010, 0b00100, 0b01000, 0b01000}, // 7
    {0b11111, 0b10001, 0b11111, 0b10001, 0b10001, 0b11111}, // 8
    {0b11111, 0b10001, 0b11111, 0b00001, 0b00001, 0b11111}, // 9
    {0b00000, 0b00100, 0b00000, 0b00100, 0b00000, 0b00000}  // :
};

void drawChar(int x, int y, char letter, uint16_t color)
{
  // Convert letter to uppercase and get the index
  letter = toupper(letter);
  int index;
  if (letter >= 'A' && letter <= 'Z')
    index = letter - 'A';
  else if (letter >= '0' && letter <= '9')
    index = letter - '0' + 26;
  else if (letter == ':')
    index = 36;
  else
    return; // Unsupported character

  // Draw the character
  for (int i = 0; i < 6; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      if (font[index][i] & (1 << (4 - j)))
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
    drawChar(x + i * 6, y, text[i], color);
  }
}

void scrollText(String text, uint16_t color, int y)
{
  unsigned long time = millis();
  int textLength = text.length();
  int textWidth = textLength * 4;
  int x = 32;
  while (x > -textWidth)
  {
    if (millis() - time > 100)
    {
      drawString(x + 1, y, text, matrix.color565(0, 0, 0));
      drawString(x, y, text, color);
      matrix.show();
      x--;
      time = millis();
    }
  }
}

uint16_t color(int _r, int _g, int _b)
{

  int r = map(_r, 0, 255, 0, 32);
  int g = map(_g, 0, 255, 0, 64);
  int b = map(_b, 0, 255, 0, 32);

  return matrix.color565(r, g, b);
}

void showMatrix()
{
  matrix.show();
}

void clearMatrix()
{
  matrix.fillRect(0, 0, 32, 16, color(0, 0, 0));
}