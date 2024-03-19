#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include "Scene.h"

class Button : public Object {
private:
  sf::RectangleShape rectangle;
public:
  Button() = default;
  Button(int x, int y, std::function<void(Scene&)> func);
  bool Contain(sf::Vector2f vec);
  void draw() final;
  std::function<void(Scene&)> corresponding_function;
};



