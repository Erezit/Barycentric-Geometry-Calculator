#include "Button.h"
#include <SFML/Graphics.hpp>

void Button::draw() {
  global::window.draw(rectangle);
}