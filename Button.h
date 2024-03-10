#pragma once

#include "shape.h"
#include <SFML/Graphics.hpp>

class Button : public Object {
private:
  sf::RectangleShape rectangle;
public:
  Button();
  Button(int x, int y) {
    rectangle.setSize(sf::Vector2f(20, 20));
    rectangle.setPosition(x, y);
  }
  void draw() final;
};


//class ButtonManager {
//    public:
//    void ToolMovePointSelected(Scene cur_scene){
//
//    }
//};

