#pragma once

class Gamemode {
  public:
    virtual void setupGame(){}
    virtual void update(int left_potentiometer_value, bool left_regular_pressed, bool left_special_pressed, int right_potentiometer_value, bool right_regular_pressed, bool right_special_pressed){}
    bool isGameOver() { return gameOver; }   
  protected:
    bool gameOver = false;
};
