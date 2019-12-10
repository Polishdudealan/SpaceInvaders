#include "Player.h"
#include "Cannonball.h"
#include "Invader.h"
#include "Game.h"
#ifndef CONSTANTS
  #define CONSTANTS
  #include "Constants.h"
#endif

using namespace Constants;

Signal matrix;

// a global variable that represents the game Space Invaders
Game game;

bool gameRunning = true; 


void printMenu(int pos_x, int pos_y);
void printBox(int x, int y, uint16_t color);

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON1_PIN_NUMBER, INPUT);
  pinMode(BUTTON2_PIN_NUMBER, INPUT);
  pinMode(BUTTON3_PIN_NUMBER, INPUT);
  pinMode(BUTTON4_PIN_NUMBER, INPUT);

  matrix.fillScreen(BLACK.to_333());
  //prints menu
  bool menu = true;
  int pos_x = 11;
  int pos_y = 10;
  
  //menu
  matrix.setCursor(5, 0);
  matrix.setTextColor(GREEN.to_333());
  matrix.print('M');
  matrix.print('E');
  matrix.print('N');
  matrix.print('U');
  
  //one_player
  Font::printCharacter(1, pos_x + 0, pos_y,  AQUA.to_333(), matrix);
  Font::printCharacter('-', pos_x + 3, pos_y,  AQUA.to_333(), matrix); 
  Font::printCharacter('P', pos_x + 6, pos_y,  AQUA.to_333(), matrix);
  
  //two_player
  Font::printCharacter(2, pos_x + 0, pos_y + 8,  AQUA.to_333(), matrix);
  Font::printCharacter('-', pos_x + 3, pos_y + 8,  AQUA.to_333(), matrix); 
  Font::printCharacter('P', pos_x + 6, pos_y + 8,  AQUA.to_333(), matrix);
  
  //pvp
  Font::printCharacter('P', pos_x + 0, pos_y + 16,  AQUA.to_333(), matrix);
  Font::printCharacter('V', pos_x + 3, pos_y + 16,  AQUA.to_333(), matrix);
  Font::printCharacter('P', pos_x + 6, pos_y + 16,  AQUA.to_333(), matrix);
  int button = 1;
  int prevButton = 1;
    while(menu) {

      int left_potentiometer = analogRead(POTENTIOMETER1_PIN_NUMBER);
      bool left_regular = (digitalRead(BUTTON1_PIN_NUMBER) == HIGH);

        //checks where the potentiometer cursor is
    
        if(left_potentiometer < 340){
          button = 1;
        }
        else if(left_potentiometer >= 340 && left_potentiometer <= 680){
          button = 2;

        }
        else if(left_potentiometer > 680) {
          button = 3;
        }
        
        if (button != prevButton){
          switch (button){
            case 1:
                printBox(pos_x - 1, pos_y - 1, RED.to_333());
                printBox(pos_x - 1, pos_y - 1 + 8, RED.to_333());
                printBox(pos_x - 1, pos_y - 1 + 16, RED.to_333());
                printBox(11 - 1, 11 - 2, GREEN.to_333());
                break;
              case 2:
                printBox(pos_x - 1, pos_y - 1, RED.to_333());
                printBox(pos_x - 1, pos_y - 1 + 8, RED.to_333());
                printBox(pos_x - 1, pos_y - 1 + 16, RED.to_333());
                printBox(11 - 1, 11 + 6, GREEN.to_333());
                break;
              case 3:
                printBox(pos_x - 1, pos_y - 1, RED.to_333());
                printBox(pos_x - 1, pos_y - 1 + 8, RED.to_333());
                printBox(pos_x - 1, pos_y - 1 + 16, RED.to_333());
                printBox(11 - 1, 11 + 14, GREEN.to_333());
                break;
          }
        }
        prevButton = button;
          if (left_regular){
            switch (button){
              case 1:
                game.setupGame();
                break;
              case 2:
                game.setupGame();
                break;
              case 3:
                game.setupGame();
                break;
            }
            menu = false;
          }
      delay(50);
    } //while loop 
} //setup()

  void loop() {
  int left_potentiometer = analogRead(POTENTIOMETER1_PIN_NUMBER);
  bool left_regular = (digitalRead(BUTTON1_PIN_NUMBER) == HIGH);
  bool left_special = (digitalRead(BUTTON2_PIN_NUMBER) == HIGH);
  int right_potentiometer = analogRead(POTENTIOMETER2_PIN_NUMBER);
  bool right_special = (digitalRead(BUTTON3_PIN_NUMBER) == HIGH);
  bool right_regular = (digitalRead(BUTTON4_PIN_NUMBER) == HIGH);

  //todo implement game select

  if(left_potentiometer < 100 && right_potentiometer > 900 && left_special && right_special) {
    boardComputationDelay = 5;
  }
  game.update(left_potentiometer, left_regular);
  
  delay(boardComputationDelay);
}

void printBox(int x, int y, uint16_t color){
  //top line
  matrix.fillRect(x, y, 11, 1, color);
  //left side
  matrix.fillRect(x, y, 1, 6, color);
  //bottom line
  matrix.fillRect(x, y + 6, 11, 1, color);
  //right side
  matrix.fillRect(x + 10, y, 1, 6, color); 

}
