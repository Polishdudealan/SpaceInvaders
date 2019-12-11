#pragma once
#include "Gamemode.h"
#include "Player.h"

class GamePVP : public Gamemode {
  public:
    GamePVP();
  private:
    Player player1;
    Player player2;
};
