#pragma once
#include "Gamemode.h"
#include "Sprite.h"
#include "Color.h"
#include "Signal.h"

#ifndef CONSTANTS
  #define CONSTANTS
  #include "Constants.h"
#endif

const int NUM_B = 7;
const int BALL_DELAY = 5;

class pvBall : public Sprite {
  public:
    pvBall(bool side = false): side(side), Sprite(-10, -10, 2, 1) {}
    
    void move(){
      x += side ? -1 : 1;
    }

    void set(bool arg_side){
      side = arg_side;
    }
  
    void deactivate() {
      active = false;
    }

    void draw(Signal& matrix) {
      if (active) {
        matrix.fillRect(x,y,width,height, side ? RED.to_333() : BLUE.to_333());  
      } else {
        erase(matrix);
      }
    }

    void fire(int arg_x, int arg_y) {
      x = arg_x;
      y = arg_y;
      active = true;
    }

    bool isActive() {
      return active;
    }

    bool getSide() {
      return side;
    }
    
  private:
    bool active = false;
    bool side; //false = player1, true = player2
}; 

class pvPlayer : public Sprite {
  public:
    pvPlayer(bool side): side(side), Sprite(side ? 30 : 0, 15, 2, 3), color(side ? RED.to_333() : BLUE.to_333()) {
      for (int i = 0; i < NUM_B; i++) {
        balls[i].set(side);
      }
    }

    pvBall balls[NUM_B];

    void reload() {ballCycle = ballCycle == BALL_DELAY ? BALL_DELAY : ballCycle+1;}
    
    void setY(int arg_y) {
      y = arg_y;
    }
  
    void fire() {
      if (ballCycle == BALL_DELAY) {
        for (int i = 0; i < NUM_B; i++) {
          if (!balls[i].isActive()){
            balls[i].fire(x+1,y+1);
            ballCycle = 0;
            for(int i = 0; i < 1000; i += 100){
              tone(PIEZOPIN, 4000 + i, 10);
            }
            return;
          }
        }  
      }
    }

    void draw(Signal& matrix){
      if (side) {
        matrix.drawPixel(x+1, y, color);
        matrix.drawPixel(x+1, y+1, color);
        matrix.drawPixel(x+1, y+2, color);
        matrix.drawPixel(x, y+1, GREEN.to_333()); 
      } else {
        matrix.drawPixel(x, y, color);
        matrix.drawPixel(x, y+1, color);
        matrix.drawPixel(x, y+2, color);
        matrix.drawPixel(x+1, y+1, GREEN.to_333());       
      }
    }
    
  private:
    bool side;
    int ballCycle = BALL_DELAY;
    uint16_t color; 
};

class GamePVP : public Gamemode {
  public:
    GamePVP(){}

    // sets up game
    void setupGame() {
      matrix.setTextColor(RED.to_333());
      matrix.fillScreen(BLACK.to_333());
      matrix.setCursor(13,8);
      matrix.print('3');
      tone(PIEZOPIN, 500, 500);
      delay(1000);
      matrix.fillScreen(BLACK.to_333());
      matrix.setCursor(13,8);
      matrix.print('2');
      tone(PIEZOPIN, 500, 500);
      delay(1000);
      matrix.fillScreen(BLACK.to_333());
      matrix.setCursor(13,8);
      matrix.print('1');
      tone(PIEZOPIN, 500, 500);
      delay(1000);
      matrix.fillScreen(BLACK.to_333());
      matrix.setCursor(2,8);
      matrix.setTextColor(GREEN.to_333());
      matrix.print('F');
      matrix.print('I');
      matrix.print('G');
      matrix.print('H');
      matrix.print('T');
      tone(PIEZOPIN, 1000, 500);
      delay(500);
      matrix.fillScreen(BLACK.to_333());
    }
      
    // runs game
    void update(int left_potentiometer_value, bool left_regular_pressed, bool left_special_pressed, int right_potentiometer_value, bool right_regular_pressed, bool right_special_pressed) {
      player1.erase(matrix);
      player2.erase(matrix);
      for (int i = 0; i < NUM_B; i++) {
        player1.balls[i].erase(matrix);
        player2.balls[i].erase(matrix);
      }
      left_potentiometer_value = 1024-left_potentiometer_value;
      
      player1.reload();
      player2.reload();

      if (left_regular_pressed) {
        player1.fire();
      }
      if (right_regular_pressed) {
        player2.fire();
      }

      int newY1 = (47 - left_potentiometer_value / 16) >= -1 ? ((47 - left_potentiometer_value / 16) < 31 ? (47 - left_potentiometer_value / 16) : 30 ): -1;
      player1.setY(newY1);
      int newY2 = (47 - right_potentiometer_value / 16) >= -1 ? ((47 - right_potentiometer_value / 16) < 31 ? (47 - right_potentiometer_value / 16) : 30 ): -1;
      player2.setY(newY2);

      for (int i = 0; i < NUM_B; i++) {
        player1.balls[i].move();
        if (player1.balls[i].getX() > 31) {
          player1.balls[i].deactivate();
        } 
        player2.balls[i].move();
        if (player2.balls[i].getX() < 0) {
          player2.balls[i].deactivate();
        }
      }
      
      bool changed = false;
      for (int i = 0; i < NUM_B; i++) {
        if (player1.isColliding(player2.balls[i]) && player2.balls[i].isActive()){
          p2++;
          player2.balls[i].deactivate();
          changed = true;
        }
        if (player2.isColliding(player1.balls[i]) && player1.balls[i].isActive()){
          p1++;
          player2.balls[i].deactivate();
          changed = true;
        }
      }
      if (changed) {
        for (int i = 0; i < NUM_B; i++) {
          player1.balls[i].deactivate();
          player2.balls[i].deactivate();          
        }
        matrix.fillScreen(BLACK.to_333());
        printScore();
        delay(1000);
        matrix.fillScreen(BLACK.to_333());
        if (p1 == 7 || p2 == 7){
          game_over();
        }
        return;
      }

      player1.draw(matrix);
      player2.draw(matrix);
      for (int i = 0; i < NUM_B; i++){
        player1.balls[i].draw(matrix);
        player2.balls[i].draw(matrix);
      }
    }
  
  private:
    Signal matrix;
    int p1 = 0;
    int p2 = 0;
    pvPlayer player1 {false};
    pvPlayer player2 {true};

    void printScore(){
      matrix.setTextColor(BLUE.to_333());
      matrix.setCursor(8, 8);
      matrix.print(p1 + '0');
      matrix.setTextColor(DAMPWHITE.to_333());
      matrix.setCursor(14, 8);
      matrix.print('-');
      matrix.setTextColor(RED.to_333());
      matrix.setCursor(20, 8);
      matrix.print(p2 + '0');
    }

    void game_over() {
      matrix.setCursor(8, 0);
      matrix.setTextColor(p1 == 7 ? BLUE.to_333() : RED.to_333());
      matrix.print('P');
      matrix.print('-');
      matrix.print(p1 == 7 ? '1' : '2');
      
      matrix.setCursor(5, 8);
      matrix.print('W');
      matrix.print('I');
      matrix.print('N');
      matrix.print('S');
      delay(5000);
      gameOver = true;
    }
};
