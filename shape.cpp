#include "shape.h"
#include <SFML/Graphics.hpp>

namespace global {
    sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
}
    
void  Point::draw() {
  global::window.draw(circle);
} 

