#pragma once

#include <stdint.h>

class Color {
  public: 
    int red;
    int green;
    int blue;
    Color();
    Color(int r, int g, int b);
    uint16_t to_333() const;
};
