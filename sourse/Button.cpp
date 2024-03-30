#include "Button.h"

#include <SFML/Graphics.hpp>

Button::Button(int x, int y, std::function<void(Scene&)> func, sf::Texture& sTest) {
  rectangle.setSize(sf::Vector2f(60, 80));
  rectangle.setPosition(x, y);
  corresponding_function = func;
  rectangle.setTexture(&sTest);
}

void Button::draw() { global::window.draw(rectangle); }

bool Button::Contain(sf::Vector2f button_click) {
  // std::cout << "Try Contain" << std::endl;
  sf::RectangleShape tmp;
  tmp.setSize(sf::Vector2f(1, 1));
  tmp.setPosition(button_click);
  bool ans = rectangle.getGlobalBounds().intersects(tmp.getGlobalBounds());
  // std::cout << ans << std::endl;
  return ans;
}
