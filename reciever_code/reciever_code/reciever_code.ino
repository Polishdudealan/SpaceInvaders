#define LIBRARIES
#include <gamma.h>
#include <RGBmatrixPanel.h>
#include <Adafruit_GFX.h>

// define the wiring of the LED screen
const uint8_t CLK  = 8;
const uint8_t LAT = A3;
const uint8_t OE = 9;
const uint8_t A = A0;
const uint8_t B = A1;
const uint8_t C = A2;
RGBmatrixPanel matrix{A, B, C, CLK, LAT, OE, false};

const int BUFFER_SIZE = 7;
char storage[BUFFER_SIZE];

const char DRAWPIXEL = 0;
const char DRAWRECT = 1;
const char FILLSCREEN = 2;
const char SETCURSOR = 3;
const char PRINTCHAR = 4;
const char SETTEXTCOLOR = 5;
const char NONE = 6;

void setup() {
  Serial.begin(38400);
  matrix.begin();
  matrix.setTextSize(1);
  for (int i = 0; i < BUFFER_SIZE; i++) {
    storage[i] = 0;
  }
}

void serialEvent() {
    Serial.readBytes(storage, BUFFER_SIZE);
    //Serial.println(storage);
    //Serial.println("redsomthing");
    //Serial.println(command);
    uint16_t color = ((0x0000 | storage[5]) << 8) | storage[6];
    if (storage[0] > 6 || storage[0] < 0 || storage[1] > 20 || storage[1] < -20 || storage[2] > 20 || storage[2] < -20 ||
        storage[3] > 40 || storage[3] < 0 || storage[4] > 40 || storage[4] < 0) {
          return;
    }
    Serial.println(color);
    switch (storage[0]) {
    case DRAWPIXEL:
      matrix.drawPixel(storage[1], storage[2], color);
      break;
    case DRAWRECT:
      matrix.drawRect(storage[1], storage[2], storage[3], storage[4], color);
      break;
    case FILLSCREEN:
      matrix.fillScreen(color);
      break;
    case SETCURSOR:
      matrix.setCursor(storage[1], storage[2]);
      break;
    case PRINTCHAR:
      matrix.print(storage[6]);
      break;
    case SETTEXTCOLOR:
      matrix.setTextColor(color);
      break;
    default:
    ;
  }
}

void loop() {
 
}
