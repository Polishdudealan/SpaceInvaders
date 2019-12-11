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

const int BUFFER_SIZE = 8;
char storage[BUFFER_SIZE];

const char DRAWPIXEL = 0;
const char FILLRECT = 1;
const char FILLSCREEN = 2;
const char SETCURSOR = 3;
const char PRINTCHAR = 4;
const char SETTEXTCOLOR = 5;
const char NONE = 6;

void setup() {
  Serial.begin(115200);
  matrix.begin();
  matrix.setTextSize(1 );
  for (int i = 0; i < BUFFER_SIZE; i++) {
    storage[i] = 0;
  }
}

void serialEvent() {
    Serial.readBytes(storage, BUFFER_SIZE);
    //Serial.println("redsomthing");
    //Serial.println(command);
    uint16_t color = ((0x00FF & storage[5]) << 8) | (0x00FF & storage[6]);
        
    //Serial.println(color);
    switch (storage[0]) {
    case DRAWPIXEL:
      matrix.drawPixel(storage[1], storage[2], color);
      break;
    case FILLRECT:
      matrix.fillRect(storage[1], storage[2], storage[3], storage[4], color);
      break;
    case FILLSCREEN:
      matrix.fillScreen(color);
      break;
    case SETCURSOR:
      matrix.setCursor(storage[1], storage[2]);
      break;
    case PRINTCHAR:
      matrix.print(storage[7]);
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
