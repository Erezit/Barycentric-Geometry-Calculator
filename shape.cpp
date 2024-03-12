#include "shape.h"
#include <SFML/Graphics.hpp>
#include <cmath>

namespace global {
    sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
}
    
void  Point::draw() {
  global::window.draw(circle);
} 

double Point::getDistance() {
    sf::Vector2 cur_mouse_pos = global::window.mapPixelToCoords(sf::Mouse::getPosition(global::window));
    sf::Vector2 to_global =  global::window.mapPixelToCoords(sf::Vector2i(Point::x_coord_, Point::y_coord_));
   //  std::cout << "cur" << cur_mouse_pos.x << "   " <<  to_global.x  << std::endl;
    double distance = sqrt((cur_mouse_pos.x - to_global.x)*(cur_mouse_pos.x - to_global.x) + (cur_mouse_pos.y - to_global.y) * (cur_mouse_pos.y - to_global.y));
  //  std::cout << distance << std::endl;
    return distance;
}
