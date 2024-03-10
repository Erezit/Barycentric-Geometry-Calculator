#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"

class Button : public Object {
private:
  sf::RectangleShape rectangle;
public:
  Button();
  Button(int x, int y) {
    rectangle.setSize(sf::Vector2f(20, 20));
    rectangle.setOrigin(x, y);
  }
  void draw() final;
};


//class ButtonManager {
//    public:
//    void ToolMovePointSelected(Scene cur_scene){
//
//    }
//};

