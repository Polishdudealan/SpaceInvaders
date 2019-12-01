#pragma once

#ifndef LIBRARIES
  #define LIBRARIES
  #include <gamma.h>
  #include <RGBmatrixPanel.h>
  #include <Adafruit_GFX.h>
#endif

enum SpriteType {INVADER, PLAYER, CANNONBALL, POWERUP};

class Sprite { 
	public: 
		//position getters for all sprites
		int getX() const { return x; }
		int getY()const { return y; }
    int getW() const { return width; }
    int getH() const { return height; } 
    
    //checks if the intervals that these objects exist in are overlapping
    //the -1 comes from the inclusion of the origin in the width and height
	  bool isColliding(Sprite& s) { 
	    bool horizontalOverlap = s.getX() <= x + width - 1 && x <= s.getX() + s.getW();
      bool verticalOverlap = s.getY() <= y + height - 1 && y <= s.getY() + s.getH();
      return horizontalOverlap && verticalOverlap;
	  }

	protected:
		//origin is upper left corner
		int x;
		int y;

    //extending right and down from origin 
    int width;
    int height;
    
		SpriteType type;
	};
