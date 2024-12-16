#include <Adafruit_Protomatter.h>
#include "src/cursor/cursor.h"
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

  matrix.show(); // Initialize all pixels to 'off'
}

// Will still require matrix.show() after calling this function
// For below, flip the signs if the matrix is upside down or not. upside down is additive because i said so
void drawCursor(int x, int y, uint16_t color)
{
  matrix.drawPixel(x, y, color);
  matrix.drawPixel(x, y, color);
  matrix.drawPixel(x, y, color);
  matrix.drawPixel(x, y, color);
  matrix.drawPixel(x, y, color);
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

const uint8_t font[26][6] = {
    {0b111111, 0b100001, 0b100001, 0b111111, 0b100001, 0b100001}, // A
    {0b111110, 0b100001, 0b111110, 0b100001, 0b100001, 0b111110}, // B
    {0b111111, 0b100000, 0b100000, 0b100000, 0b100000, 0b111111}, // C
    {0b111110, 0b100001, 0b100001, 0b100001, 0b100001, 0b111110}, // D
    {0b111111, 0b100000, 0b111111, 0b100000, 0b100000, 0b111111}, // E
    {0b111111, 0b100000, 0b111111, 0b100000, 0b100000, 0b100000}, // F
    {0b111111, 0b100000, 0b100111, 0b100001, 0b100001, 0b111111}, // G
    {0b100001, 0b100001, 0b111111, 0b100001, 0b100001, 0b100001}, // H
    {0b111111, 0b001000, 0b001000, 0b001000, 0b001000, 0b111111}, // I
    {0b111111, 0b000001, 0b000001, 0b000001, 0b100001, 0b111111}, // J
    {0b100001, 0b100010, 0b111100, 0b100010, 0b100001, 0b100001}, // K
    {0b100000, 0b100000, 0b100000, 0b100000, 0b100000, 0b111111}, // L
    {0b100001, 0b110011, 0b101101, 0b100001, 0b100001, 0b100001}, // M
    {0b100001, 0b110001, 0b101001, 0b100101, 0b100011, 0b100001}, // N
    {0b111111, 0b100001, 0b100001, 0b100001, 0b100001, 0b111111}, // O
    {0b111111, 0b100001, 0b111111, 0b100000, 0b100000, 0b100000}, // P
    {0b111111, 0b100001, 0b100001, 0b100101, 0b100011, 0b111111}, // Q
    {0b111111, 0b100001, 0b111111, 0b100010, 0b100001, 0b100001}, // R
    {0b111111, 0b100000, 0b111111, 0b000001, 0b000001, 0b111111}, // S
    {0b111111, 0b001000, 0b001000, 0b001000, 0b001000, 0b001000}, // T
    {0b100001, 0b100001, 0b100001, 0b100001, 0b100001, 0b111111}, // U
    {0b100001, 0b100001, 0b100001, 0b100001, 0b010010, 0b001100}, // V
    {0b100001, 0b100001, 0b100001, 0b101101, 0b110011, 0b100001}, // W
    {0b100001, 0b010010, 0b001100, 0b001100, 0b010010, 0b100001}, // X
    {0b100001, 0b100001, 0b010010, 0b001100, 0b001000, 0b001000}, // Y
    {0b111111, 0b000010, 0b000100, 0b001000, 0b010000, 0b111111}  // Z
};

void drawChar(int x, int y, char letter, uint16_t color)
{
  // Convert letter to uppercase and get the index
  letter = toupper(letter);
  if (letter < 'A' || letter > 'Z')
    return; // Only support A-Z
  int index = letter - 'A';

  // Draw the character
  for (int i = 0; i < 6; i++)
  {
    for (int j = 0; j < 6; j++)
    {
      if (font[index][i] & (1 << (5 - j)))
      {
        matrix.drawPixel(x + j, y + i, color);
      }
    }
  }
}

void drawString(int x, int y, std::string text, uint16_t color)
{
  for (int i = 0; i < text.length(); i++)
  {
    drawChar(x + i * 4, y, text[i], color);
  }
}

void scrollText(std::string text, uint16_t color, int y)
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