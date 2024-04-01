#include "NameBox.h"

  void NameBox::setName(char sbl) {
    font.loadFromFile("Textures/LTSuperior-Medium.ttf");
    name.setFont(font);
    name.setColor(sf::Color::Red);
    name.setString(sbl);
    name.setCharacterSize(20);
    name.setStyle(sf::Text::Bold);
  }

  void NameBox::setPosition(double num1, double num2) {
    x_coord_ = num1 - 5;
    y_coord_ = num2 - 5;
  }
  
  sf::Text NameBox::getName() {
    name.setPosition(x_coord_ + delta.x, y_coord_ + delta.y);
    return name;
  }

  void NameBox::setDelta(sf::Vector2f new_delta) {
    delta = new_delta;
  }
