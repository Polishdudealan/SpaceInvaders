#pragma once
#include <stdint.h>


class Gamemode {
  public:
    Gamemode() {
      player1Score = 10001;
      player2Score = 10001;  
    }
    virtual void setupGame(){}
    virtual void update(int left_potentiometer_value, bool left_regular_pressed, bool left_special_pressed, int right_potentiometer_value, bool right_regular_pressed, bool right_special_pressed){}
    bool isGameOver() { return gameOver; }
    void setGameOver(bool gameState) { gameOver = gameState; }  
    uint16_t player1Score = 10001;
    uint16_t player2Score = 10001;
  protected:
    bool gameOver = false;
};
