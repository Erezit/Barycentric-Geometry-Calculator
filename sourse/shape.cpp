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
  sf::Vector2 cur_mouse_pos = global::window.mapPixelToCoords(sf::Mouse::getPosition(global::window));
  sf::Vector2 to_global = global::window.mapPixelToCoords(sf::Vector2i(Point::x_coord_, Point::y_coord_));
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
  sf::Vector2f cur_mouse_pos = global::window.mapPixelToCoords(sf::Mouse::getPosition(global::window));
  sf::Vector2f a_to_global = global::window.mapPixelToCoords(sf::Vector2i(a_point_->x_coord_, a_point_->y_coord_));
  sf::Vector2f b_to_global = global::window.mapPixelToCoords(sf::Vector2i(b_point_->x_coord_, b_point_->y_coord_));
  double A = a_to_global.y - b_to_global.y;
  double B = b_to_global.x - a_to_global.x;
  double C = a_to_global.x * b_to_global.y - a_to_global.y * b_to_global.x;
  // std::cout <<"DIST: " <<  std::abs((A * cur_mouse_pos.x + B * cur_mouse_pos.y + C) / sqrt(A * A + B * B)) << std::endl;
  return std::abs((A * cur_mouse_pos.x + B * cur_mouse_pos.y + C) / sqrt(A * A + B * B));
}

std::vector<double> Line::getСoefficients() {
  sf::Vector2f a_to_global = global::window.mapPixelToCoords(sf::Vector2i(a_point_->x_coord_, a_point_->y_coord_));
  sf::Vector2f b_to_global = global::window.mapPixelToCoords(sf::Vector2i(b_point_->x_coord_, b_point_->y_coord_));
  std::vector<double> coefficients;
  coefficients.push_back(a_to_global.y - b_to_global.y);
  coefficients.push_back(b_to_global.x - a_to_global.x);
  coefficients.push_back(a_to_global.x * b_to_global.y - a_to_global.y * b_to_global.x);
  return coefficients;
}

PointByTwoLines::PointByTwoLines(Line* a_line, Line* b_line) : a_line_(a_line), b_line_(b_line) {
  circle.setRadius(5.f);
  make_actual();
}

void PointByTwoLines::draw() {
  make_actual();
  global::window.draw(circle);
}

void PointByTwoLines::make_actual() {
  std::vector<double> coefficients_a = a_line_->getСoefficients();
  std::vector<double> coefficients_b = b_line_->getСoefficients();
  double det = coefficients_a[0] * coefficients_b[1] - coefficients_a[1] * coefficients_b[0];
  double det_a = coefficients_a[2] * coefficients_b[1] - coefficients_a[1] * coefficients_b[2];
  double det_b = coefficients_a[0] * coefficients_b[2] - coefficients_a[2] * coefficients_b[0];
  x_coord_ = -det_a / det;
  y_coord_ = -det_b / det;
  // std::cout << x_coord_ << " " << y_coord_ << std::endl;
  circle.setPosition(x_coord_, y_coord_);
}
