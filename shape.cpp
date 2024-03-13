#include "shape.h"

#include <SFML/Graphics.hpp>
#include <cmath>

namespace global {
sf::RenderWindow window(sf::VideoMode(800, 800),
                        "Barycentric Geometry Calculator");
}

void BasePoint::draw() { global::window.draw(circle); }

void MiddlePoint::make_actual() {
  x_coord_ = (a_point_->x_coord_ + b_point_->x_coord_) / 2;
  y_coord_ = (a_point_->y_coord_ + b_point_->y_coord_) / 2;
  circle.setPosition(x_coord_, y_coord_);
}

void MiddlePoint::draw() {

  make_actual();
  global::window.draw(circle);
}

void Line::draw() {

}

double Point::getDistance() {
  sf::Vector2 cur_mouse_pos =
      global::window.mapPixelToCoords(sf::Mouse::getPosition(global::window));
  sf::Vector2 to_global = global::window.mapPixelToCoords(
      sf::Vector2i(Point::x_coord_, Point::y_coord_));
  //  std::cout << "cur" << cur_mouse_pos.x << "   " <<  to_global.x  <<
  //  std::endl;
  double distance =
      sqrt((cur_mouse_pos.x - to_global.x) * (cur_mouse_pos.x - to_global.x) +
           (cur_mouse_pos.y - to_global.y) * (cur_mouse_pos.y - to_global.y));
  //  std::cout << distance << std::endl;
  return distance;
}
