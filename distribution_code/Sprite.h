#pragma once
#include "Signal.h"
#ifndef CONSTANTS
  #define CONSTANTS
  #include "Constants.h"
#endif

class Sprite { 
	public: 
    Sprite(int x, int y, int w, int h): 
      x(x), y(y), width(w), height(h),
      oldX(x), oldY(y), redrawFlag(true) {}
    
	  //needs to be implemented in each child class, will likely use draw_with_rgb  
    //but that might have more arguments such as color and cannot be virutal  
    virtual void draw(Signal&)   = 0; 
    
    //position getters for all sprites
		int getX() const { return x; }
		int getY()const { return y; }
    int getW() const { return width; }
    int getH() const { return height; } 
    
    //checks if the intervals that these objects exist in are overlapping
    //the -1 comes from the inclusion of the origin in the width and height
	  bool isColliding(Sprite& s) { 
	    bool horizontalOverlap = s.getX() <= x + width - 1 && x <= s.getX() + s.getW() - 1;
      bool verticalOverlap = s.getY() <= y + height - 1 && y <= s.getY() + s.getH() - 1;
      return horizontalOverlap && verticalOverlap;
	  }

    //sets redrawFlag so that when redraw is called the sprite is correctly updated
    void upd(){
      redrawFlag = true;
    }
    
    //will erase old image and draw new image with new positions and values
    void redraw(Signal& matrix) {
      if (redrawFlag) {
        eraseOld(matrix);
        oldX = x;
        oldY = y;
        draw(matrix);
        redrawFlag = false;
      }
    }

    // erases sprite previous position
    void eraseOld(Signal& matrix) {
		  matrix.fillRect(oldX, oldY, width, height, Constants::BLACK.to_333());
	  }

    //erases sprite current position
    void erase(Signal& matrix) {
      matrix.fillRect(x, y, width, height, Constants::BLACK.to_333());
    }
	  
    
	protected:
		//origin is upper left corner
		int x;
		int y;

    //extending right and down from origin 
    int width;
    int height;

    //this flag is used to determine whether a redraw is necessary for the sprite
    bool redrawFlag;

    //these varibales are used to determine where the current image is on the screen
    int oldX;
    int oldY;
};
