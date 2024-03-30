#include "shape.h"

#include <SFML/Graphics.hpp>
#include <cmath>

namespace global {
sf::RenderWindow window(sf::VideoMode(800, 800),
                        "Barycentric Geometry Calculator");
}

Point::Point(double x_pos, double y_pos) : x_coord_(x_pos), y_coord_(y_pos) {
  circle.setRadius(5.f);
  circle.move(x_pos, y_pos);
}

void BasePoint::draw() { 
    circle.setPosition(x_coord_, y_coord_);
    global::window.draw(circle);
}

MiddlePoint::MiddlePoint(Point* a_point, Point* b_point)
    : a_point_(a_point), b_point_(b_point) {
  circle.setRadius(5.f);
}

void MiddlePoint::make_actual() {
  x_coord_ = (a_point_->x_coord_ + b_point_->x_coord_) / 2;
  y_coord_ = (a_point_->y_coord_ + b_point_->y_coord_) / 2;
  circle.setPosition(x_coord_, y_coord_);
}

void Line::make_actual() {
  line[0] = sf::Vertex(a_point_->getPosition() + sf::Vector2f(5,5));
  line[1] = sf::Vertex(b_point_->getPosition() + sf::Vector2f(5,5));
}

void MiddlePoint::draw() {
  make_actual();
  global::window.draw(circle);
}

Line::Line(Point* a_point, Point* b_point)
    : a_point_(a_point), b_point_(b_point) {
      make_actual();
    }

void Line::draw() 
{
  make_actual();
  global::window.draw(line, 2, sf::Lines);
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

sf::Vector2f Point::getPosition() {
  return global::window.mapPixelToCoords(
          sf::Vector2i(Point::x_coord_, Point::y_coord_));;
}

double Line::getDistance() {
  return 10000;
}
