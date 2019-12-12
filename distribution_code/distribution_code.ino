#include "Player.h"
#include "Cannonball.h"
#include "Invader.h"
#include "Gamemode.h"
#include "Game.h"
#include "GamePVP.h"
#include "Game2P.h"
#ifndef CONSTANTS
  #define CONSTANTS
  #include "Constants.h"
#endif
//needed for file i/o
#include <EEPROM.h>
using namespace Constants;

Signal matrix;

// a global variable that represents the game Space Invaders
Gamemode* game;

bool gameRunning = true; 

int highScore1;
int highScore2;
int highScore3;

void printMenu(int pos_x, int pos_y);
void printBox(int x, int y, uint16_t color);

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON1_PIN_NUMBER, INPUT);
  pinMode(BUTTON2_PIN_NUMBER, INPUT);
  pinMode(BUTTON3_PIN_NUMBER, INPUT);
  pinMode(BUTTON4_PIN_NUMBER, INPUT);
  
//  clears data from registers
//  for (int i = 1; i < 7; i++){
//    EEPROM.write(i, 0);
//  }

  //loads data
 char a1 = EEPROM.read(1);
 char a2 = EEPROM.read(2);
 char a3 = EEPROM.read(3);
 char a4 = EEPROM.read(4);
 char a5 = EEPROM.read(5);
 char a6 = EEPROM.read(6);
 
  //reconstructs integer value
  highScore1 = (((a2 << 0) & 0xFF) + (a1 << 8) & 0xFFFF);
  highScore2 = (((a4 << 0) & 0xFF) + (a3 << 8) & 0xFFFF);
  highScore3 = (((a6 << 0) & 0xFF) + (a5 << 8) & 0xFFFF);
  Serial.println(highScore1);
  Serial.println(highScore2);
  Serial.println(highScore3);
  
  //checks for a new player1 highscore, overwrites save data if so
  //shifts bits in order to store integer across 2 memory locations
  char b1 = (game->player1Score >> 8) & 0xFF; //msg
  char b2 = (game->player1Score) & 0xFF;  //lsg
  Serial.print("game->player1Score: ");
  Serial.println(game->player1Score);
  
  if(game->player1Score < 10000 && game->player1Score > highScore3){
    if(game->player1Score >= highScore2){
      if(game->player1Score >= highScore1){
        EEPROM.write(1, b1);
        EEPROM.write(2, b2);

        EEPROM.write(3, a1);
        EEPROM.write(4, a2);

        EEPROM.write(5, a3);
        EEPROM.write(6, a4);
      }
      else{
        EEPROM.write(3, b1);
        EEPROM.write(4, b2);

        EEPROM.write(5, a3);
        EEPROM.write(6, a4);
      }
    }
    else {
      EEPROM.write(5, b1);
      EEPROM.write(6, b2);
    }
  }

  a1 = EEPROM.read(1);
  a2 = EEPROM.read(2);
  a3 = EEPROM.read(3);
  a4 = EEPROM.read(4);
  a5 = EEPROM.read(5);
  a6 = EEPROM.read(6);
 
  //reconstructs integer value
  highScore1 = (((a2 << 0) & 0xFF) + (a1 << 8) & 0xFFFF);
  highScore2 = (((a4 << 0) & 0xFF) + (a3 << 8) & 0xFFFF);
  highScore3 = (((a6 << 0) & 0xFF) + (a5 << 8) & 0xFFFF);
  
  //checks for a new player1 highscore, overwrites save data if so
  if(game->player2Score < 10000) {
        char c1 = (game->player2Score & 0xFF00) >> 8;
    char c2 = game->player2Score & 0x00FF;
    if(game->player2Score > highScore3){
      if(game->player2Score > highScore2){
        if(game->player2Score > highScore1){
          EEPROM.write(1, c1);
          EEPROM.write(2, c2);
  
          EEPROM.write(3, a1);
          EEPROM.write(4, a2);
  
          EEPROM.write(5, a3);
          EEPROM.write(6, a4);
        }
        else{
          EEPROM.write(3, c1);
          EEPROM.write(4, c2);
  
          EEPROM.write(5, a3);
          EEPROM.write(6, a4);
        }
      }
      else {
        EEPROM.write(5, c1);
        EEPROM.write(6, c2);
      }
    }
  }
  game->player1Score = 0;
  game->player2Score = 0;

  a1 = EEPROM.read(1);
  a2 = EEPROM.read(2);
  a3 = EEPROM.read(3);
  a4 = EEPROM.read(4);
  a5 = EEPROM.read(5);
  a6 = EEPROM.read(6);
 
  //reconstructs integer value
  highScore1 = (((a2 << 0) & 0xFF) + (a1 << 8) & 0xFFFF);
  highScore2 = (((a4 << 0) & 0xFF) + (a3 << 8) & 0xFFFF);
  highScore3 = (((a6 << 0) & 0xFF) + (a5 << 8) & 0xFFFF);
  
  
  
  matrix.fillScreen(BLACK.to_333());
  //prints menu
  bool menu = true;
  int pos_x = 3;
  int pos_y = 9;
  
  //menu
//  matrix.setCursor(0, 0);
//  matrix.setTextColor(GREEN.to_333());
//  matrix.print('M');
//  matrix.print('E');
//  matrix.print('N');
//  matrix.print('U');
  //custom font menu
  Font::printCharacter('M', 0, 1, GREEN.to_333(), matrix);
  Font::printCharacter('E', 4, 1, GREEN.to_333(), matrix);
  Font::printCharacter('N', 8, 1, GREEN.to_333(), matrix);
  Font::printCharacter('U', 12, 1, GREEN.to_333(), matrix);

  //highScore
  Font::printCharacter('H', 18, 1, RED.to_333(), matrix);
  Font::printCharacter('I', 18 + 4, 1, RED.to_333(), matrix);
  Font::printCharacter(5, 14 + 4, 7, RED.to_333(), matrix);
  Font::printCharacter('C', 14 + 8, 7, RED.to_333(), matrix);
  Font::printCharacter('R', 14 + 12, 7, RED.to_333(), matrix);

  //converts int score to array of place values
  int high_Score1[4];
  int high_Score2[4];
  int high_Score3[4];
  
  for (int i = 3; i >= 0; i--) {
    high_Score1[i] = highScore1 % 10;
    high_Score2[i] = highScore2 % 10;
    high_Score3[i] = highScore3 % 10;
    highScore1 /= 10;
    highScore2 /= 10;
    highScore3 /= 10;
  }
  //prints out high scores
  for (int i = 0; i < 4; i++) {
    Font::printCharacter(high_Score1[i], 16 + 4 * i, 13, DAMPWHITE.to_333(), matrix);
    Font::printCharacter(high_Score2[i], 16 + 4 * i, 19, DAMPWHITE.to_333(), matrix);
    Font::printCharacter(high_Score3[i], 16 + 4 * i, 25, DAMPWHITE.to_333(), matrix);
  }
  
  //one_player
  Font::printCharacter(1, pos_x -1, pos_y,  AQUA.to_333(), matrix); // changed to 4
  Font::printCharacter('-', pos_x + 3, pos_y,  AQUA.to_333(), matrix); 
  Font::printCharacter('P', pos_x + 7, pos_y,  AQUA.to_333(), matrix);
  
  //two_player
  Font::printCharacter(2, pos_x -1, pos_y + 8,  AQUA.to_333(), matrix); // changed to 4
  Font::printCharacter('-', pos_x + 3, pos_y + 8,  AQUA.to_333(), matrix); 
  Font::printCharacter('P', pos_x + 7, pos_y + 8,  AQUA.to_333(), matrix); 
  
  //pvp
  Font::printCharacter('P', pos_x -1, pos_y + 16,  AQUA.to_333(), matrix); // changed to 4 
  Font::printCharacter('V', pos_x + 3, pos_y + 16,  AQUA.to_333(), matrix);
  Font::printCharacter('P', pos_x + 7, pos_y + 16,  AQUA.to_333(), matrix);
  
  printBox(pos_x - 1, pos_y - 1, GREEN.to_333());
  printBox(pos_x - 1, pos_y - 1 + 8, RED.to_333());
  printBox(pos_x - 1, pos_y - 1 + 16, RED.to_333());
  int button = 1;
  int prevButton = 1;
    while(menu) {

      int left_potentiometer = analogRead(POTENTIOMETER1_PIN_NUMBER);
      bool left_regular = (digitalRead(BUTTON1_PIN_NUMBER) == HIGH);

        //checks where the potentiometer cursor is
    
        if(left_potentiometer < 400){
          button = 1;
        }
        else if(left_potentiometer >= 400 && left_potentiometer <= 600){
          button = 2;

        }
        else if(left_potentiometer > 600) {
          button = 3;
        }
        
        if (button != prevButton){
          switch (button){
            case 1:
               tone(PIEZOPIN, 4000, 10);
               printBox(pos_x - 1, pos_y - 1, RED.to_333());
               printBox(pos_x - 1, pos_y - 1 + 8, RED.to_333());
               printBox(pos_x - 1, pos_y - 1 + 16, RED.to_333());
               printBox(3 - 1, 11 - 3, GREEN.to_333());
               break;
            case 2:
               tone(PIEZOPIN, 4000, 10);
               printBox(pos_x - 1, pos_y - 1, RED.to_333());
               printBox(pos_x - 1, pos_y - 1 + 8, RED.to_333());
               printBox(pos_x - 1, pos_y - 1 + 16, RED.to_333());
               printBox(3 - 1, 11 + 5, GREEN.to_333());
               break;
            case 3:
               tone(PIEZOPIN, 4000, 10);
               printBox(pos_x - 1, pos_y - 1, RED.to_333());
               printBox(pos_x - 1, pos_y - 1 + 8, RED.to_333());
               printBox(pos_x - 1, pos_y - 1 + 16, RED.to_333());
               printBox(3 - 1, 11 + 13, GREEN.to_333());
	       break;
          }
        }
        prevButton = button;
          if (left_regular){
            tone(PIEZOPIN, 1000, 10);
            switch (button){
              case 1:
                game = new Game();
                game->setupGame();
                break;
              case 2:
                game = new Game2P();
                game->setupGame();
                break;
              case 3:
                game = new GamePVP();
                game->setupGame();
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

  //easter egg

  if(left_potentiometer < 100 && right_potentiometer > 900 && left_special && right_special) {
    boardComputationDelay = 10;
  }

  //emergency reset
  if (right_potentiometer < 100 && left_potentiometer > 900 && left_special && right_special && left_regular && right_regular){
    game->setGameOver(true);
    delay(500);
  }
  game->update(left_potentiometer, left_regular, left_special, right_potentiometer, right_regular, right_special);
//  game->update(left_potentiometer, left_special, left_special, right_potentiometer, right_regular, right_special);
  if (game->isGameOver()){
    setup();
  }
  
  delay(boardComputationDelay);
}

void printBox(int x, int y, uint16_t color){
  //top line
  matrix.fillRect(x, y, 11, 1, color); 
  //left side
  matrix.fillRect(x-1, y, 1, 6, color); //subtracted 1 to width to make box bigger
  //bottom line
  matrix.fillRect(x, y + 6, 11, 1, color); 
  //right side
  matrix.fillRect(x + 11, y, 1, 6, color); //added 1 to width to make box bigger
}
