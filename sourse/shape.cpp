#include "shape.h"

#include <SFML/Graphics.hpp>
#include <cmath>

namespace global {
  sf::RenderWindow window(sf::VideoMode(1400, 900),
                          "Barycentric Geometry Calculator", sf::Style::Close | sf::Style::Titlebar);
  char next_name = 'A';
}
GiNaC::symbol a("a");
GiNaC::symbol b("b");
GiNaC::symbol c("c");

void Shape::setCoordinates(GiNaC::ex poly1, GiNaC::ex poly2, GiNaC::ex poly3) {
  barycentric_coordinates.setCoordinates(poly1, poly2, poly3);
}

void Shape::choosenActive() {
  color = sf::Color{0, 0, 255, 255};
}

void Shape::choosenFinal() {
  color = sf::Color{255, 255, 255, 255};
}

sf::Color Shape::getColor() {
  return color;
}

BarycentricCoordinates Shape::getCoordinates() {
  return barycentric_coordinates;
}

Point::Point(double x_pos, double y_pos) : x_coord_(x_pos), y_coord_(y_pos) {
  circle.setRadius(5.f);
  circle.move(x_pos, y_pos);
  name.setName(global::next_name);
  global::next_name = global::next_name + 1;
}

BasePoint::BasePoint(double x_pos, double y_pos) : Point(x_pos, y_pos) {
    choosenFinal();
}

void BasePoint::draw() { 
    circle.setFillColor(getColor());
    circle.setPosition(x_coord_, y_coord_);
    global::window.draw(circle);
    name.setPosition(x_coord_, y_coord_);
    global::window.draw(name.getName());
}

MiddlePoint::MiddlePoint(Point* a_point, Point* b_point)
    : a_point_(a_point), b_point_(b_point) {
  circle.setRadius(5.f);
  name.setName(global::next_name);
  global::next_name = global::next_name + 1;
  BarycentricCoordinates barycentric_coordinates_a = a_point_ -> getCoordinates();
  BarycentricCoordinates barycentric_coordinates_b = b_point_ -> getCoordinates();
  GiNaC::ex sum_a = barycentric_coordinates_a.getACoordinate() + barycentric_coordinates_a.getBCoordinate() + barycentric_coordinates_a.getCCoordinate();
  GiNaC::ex sum_b = barycentric_coordinates_b.getACoordinate() + barycentric_coordinates_b.getBCoordinate() + barycentric_coordinates_b.getCCoordinate();
  barycentric_coordinates.setCoordinates((barycentric_coordinates_a.getACoordinate() / sum_a + barycentric_coordinates_b.getACoordinate() / sum_b).normal(),
          (barycentric_coordinates_a.getBCoordinate() / sum_a + barycentric_coordinates_b.getBCoordinate() / sum_b).normal(),
          (barycentric_coordinates_a.getCCoordinate() / sum_a + barycentric_coordinates_b.getCCoordinate() / sum_b).normal());
  barycentric_coordinates.simplify();
  choosenFinal();
}

void MiddlePoint::make_actual() {
  x_coord_ = (a_point_->x_coord_ + b_point_->x_coord_) / 2;
  y_coord_ = (a_point_->y_coord_ + b_point_->y_coord_) / 2;
  circle.setPosition(x_coord_, y_coord_);
  name.setPosition(x_coord_, y_coord_);
}

void Line::make_actual() {
  sf::Color tmp_color = getColor();
  line[0] = sf::Vertex(a_point_->getPosition() + sf::Vector2f(5,5), tmp_color);
  line[1] = sf::Vertex(b_point_->getPosition() + sf::Vector2f(5,5), tmp_color);
}

void Line::draw() {
  make_actual();
  global::window.draw(line, 2, sf::Lines);
}


void MiddlePoint::draw() {
  make_actual();
  circle.setFillColor(getColor());
  global::window.draw(circle);
  global::window.draw(name.getName());
}

Line::Line(Point* a_point, Point* b_point)
    : a_point_(a_point), b_point_(b_point) {
      make_actual();
      BarycentricCoordinates barycentric_coordinates_a = a_point_ -> getCoordinates();
      BarycentricCoordinates barycentric_coordinates_b = b_point_ -> getCoordinates();
      GiNaC::ex new_coordinate_a = barycentric_coordinates_a.getBCoordinate() * barycentric_coordinates_b.getCCoordinate() - barycentric_coordinates_a.getCCoordinate() * barycentric_coordinates_b.getBCoordinate();
      GiNaC::ex new_coordinate_b = barycentric_coordinates_a.getCCoordinate() * barycentric_coordinates_b.getACoordinate() - barycentric_coordinates_a.getACoordinate() * barycentric_coordinates_b.getCCoordinate();
      GiNaC::ex new_coordinate_c = barycentric_coordinates_a.getACoordinate() * barycentric_coordinates_b.getBCoordinate() - barycentric_coordinates_a.getBCoordinate() * barycentric_coordinates_b.getACoordinate();
      barycentric_coordinates.setCoordinates(new_coordinate_a.normal(), new_coordinate_b.normal(), new_coordinate_c.normal());
      barycentric_coordinates.simplify();
      choosenFinal();
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
  return std::abs((A * cur_mouse_pos.x + B * cur_mouse_pos.y + C) / sqrt(A * A + B * B));
}

Point* Line::getPointA() {
  return a_point_;
}

Point* Line::getPointB() {
  return b_point_;
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


template <typename T>
std::vector<T> FindCoordinate(const T& A1,const T& B1,const T& C1,const T& A2,const T& B2,const T& C2) {
  return std::vector<T>{-B1 * C2 + B2 * C1,-A2 * C1 + A1 * C2, -A1 * B2 + B1 * A2};
}

PointByTwoLines::PointByTwoLines(Line* a_line, Line* b_line) : a_line_(a_line), b_line_(b_line) {
  circle.setRadius(5.f);
  make_actual();
  name.setName(global::next_name);
  global::next_name = global::next_name + 1;
  BarycentricCoordinates barycentric_coordinates_a = a_line_ -> getCoordinates();
  BarycentricCoordinates barycentric_coordinates_b = b_line_ -> getCoordinates();
  std::vector<GiNaC::ex> new__coordinates = FindCoordinate<GiNaC::ex>(barycentric_coordinates_a.getACoordinate(), barycentric_coordinates_a.getBCoordinate(),barycentric_coordinates_a.getCCoordinate(),barycentric_coordinates_b.getACoordinate(), barycentric_coordinates_b.getBCoordinate(), barycentric_coordinates_b.getCCoordinate()); 
  barycentric_coordinates.setCoordinates(new__coordinates[0].normal(), new__coordinates[1].normal(), new__coordinates[2].normal());
  barycentric_coordinates.simplify();
  choosenFinal();
}

void PointByTwoLines::draw() {
  make_actual();
  circle.setFillColor(getColor());
  global::window.draw(circle);
  global::window.draw(name.getName());
}

void PointByTwoLines::make_actual() {
  std::vector<double> coefficients_a = a_line_->getСoefficients();
  std::vector<double> coefficients_b = b_line_->getСoefficients();
  double det = coefficients_a[0] * coefficients_b[1] - coefficients_a[1] * coefficients_b[0];
  double det_a = coefficients_a[2] * coefficients_b[1] - coefficients_a[1] * coefficients_b[2];
  double det_b = coefficients_a[0] * coefficients_b[2] - coefficients_a[2] * coefficients_b[0];
  x_coord_ = -det_a / det;
  y_coord_ = -det_b / det;
  circle.setPosition(x_coord_, y_coord_);
  name.setPosition(x_coord_, y_coord_);
}


Incenter::Incenter(Point* a_point, Point* b_point,Point* c_point) : a_point_(a_point), b_point_(b_point), c_point_(c_point) {
  circle.setRadius(5.f);
  make_actual();
  barycentric_coordinates.setCoordinates(a, b, c);
  name.setName(global::next_name);
  global::next_name = global::next_name + 1;
  choosenFinal();
}

void Incenter::make_actual() {
  sf::Vector2f a_position = a_point_ -> getPosition();
  sf::Vector2f b_position = b_point_ -> getPosition();
  sf::Vector2f c_position = c_point_ -> getPosition();
  double c_size =  sqrt((a_position - b_position).x * (a_position - b_position).x + (a_position - b_position).y * (a_position - b_position).y);
  double b_size =  sqrt((a_position - c_position).x * (a_position - c_position).x + (a_position - c_position).y * (a_position - c_position).y);
  double a_size =  sqrt((c_position - b_position).x * (c_position - b_position).x + (c_position - b_position).y * (c_position - b_position).y);
  double sum = a_size + b_size  + c_size;
  x_coord_ = (a_position.x * a_size + b_position.x * b_size + c_position.x * c_size) / sum;
  y_coord_ = (a_position.y * a_size + b_position.y * b_size + c_position.y * c_size) / sum;
  circle.setPosition(x_coord_, y_coord_);
  name.setPosition(x_coord_, y_coord_);
}

void Incenter::draw() {
  make_actual();
  global::window.draw(circle);
  circle.setFillColor(getColor());
  global::window.draw(name.getName());
}

Orthocenter::Orthocenter(Point* a_point, Point* b_point,Point* c_point) : a_point_(a_point), b_point_(b_point), c_point_(c_point) {
  circle.setRadius(5.f);
  make_actual();
  barycentric_coordinates.setCoordinates(1 / (b * b + c * c - a * a), 1 / (c * c - b * b + a * a), 1 / (b * b - c * c + a * a));
  name.setName(global::next_name);
  global::next_name = global::next_name + 1;
  choosenFinal();
}

void Orthocenter::draw() {
  make_actual();
  global::window.draw(circle);
  circle.setFillColor(getColor());
  global::window.draw(name.getName());
}

void Orthocenter::make_actual() {
  sf::Vector2f a_position = a_point_ -> getPosition();
  sf::Vector2f b_position = b_point_ -> getPosition();
  sf::Vector2f c_position = c_point_ -> getPosition();
  double c_size =  sqrt((a_position - b_position).x * (a_position - b_position).x + (a_position - b_position).y * (a_position - b_position).y);
  double b_size =  sqrt((a_position - c_position).x * (a_position - c_position).x + (a_position - c_position).y * (a_position - c_position).y);
  double a_size =  sqrt((c_position - b_position).x * (c_position - b_position).x + (c_position - b_position).y * (c_position - b_position).y);
  double a_weight = (a_size * a_size - b_size * b_size + c_size * c_size) * (a_size * a_size + b_size * b_size - c_size * c_size);
  double b_weight = (a_size * a_size + b_size * b_size - c_size * c_size) * (-a_size * a_size + b_size * b_size + c_size * c_size);
  double c_weight = (-a_size * a_size + b_size * b_size + c_size * c_size) * (a_size * a_size - b_size * b_size + c_size * c_size);
  double sum = a_weight + b_weight  + c_weight;
  x_coord_ = (a_position.x * a_weight + b_position.x * b_weight + c_position.x * c_weight) / sum;
  y_coord_ = (a_position.y * a_weight + b_position.y * b_weight + c_position.y * c_weight) / sum;
  circle.setPosition(x_coord_, y_coord_);
  name.setPosition(x_coord_, y_coord_);
}

