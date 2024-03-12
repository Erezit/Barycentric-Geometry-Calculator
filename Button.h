#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include "Scene.h"

class Button : public Object {
private:
  sf::RectangleShape rectangle;
public:
  Button();
  Button(int x, int y,std::function<void(Scene&)> func) {
    rectangle.setSize(sf::Vector2f(20, 20));
    rectangle.setPosition(x, y);
    corresponding_function = func;
  }
  bool Contain(sf::Vector2f vec);
  void draw() final;
  std::function<void(Scene&)> corresponding_function;
};



