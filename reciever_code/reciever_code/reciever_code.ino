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


char storage;

void setup() {
  Serial.begin(14400);
  matrix.begin();

}
void serialEvent() {
    storage = Serial.read();
    Serial.println("redsomthing");
}
void loop() {
  if(storage == 'r') {
    matrix.fillScreen(matrix.Color333(1, 0, 0));
  } 
  else if(storage == 'g'){
    matrix.fillScreen(matrix.Color333(0, 1, 0));
  }
  else{
    matrix.fillScreen(matrix.Color333(0, 0, 1));
  }

  delay(20);
}
