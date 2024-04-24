#include "shape.h"

#include <SFML/Graphics.hpp>
#include <cmath>


  void RenamebleShape::setName(std::string name) {
    name_ = name;
  }

  std::string RenamebleShape::getName() {
    return name_;
  }


namespace global {
  sf::RenderWindow window(sf::VideoMode(1400, 900),
                        "Barycentric Geometry Calculator",
                        sf::Style::Close | sf::Style::Titlebar, sf::ContextSettings(0,0,8));
  char next_name = 'A';
  bool isActiveMode = false;
  bool is_problem_correct = false; // for testing
  bool fake_click = false;
}  // namespace global
GiNaC::symbol a("a");
GiNaC::symbol b("b");
GiNaC::symbol c("c");


void Invisibility::changeHidden() {
  isHidden = !isHidden;  
}

bool Invisibility::getIsHidden() {
   return isHidden;
}

void Shape::setCoordinates(GiNaC::ex poly1, GiNaC::ex poly2, GiNaC::ex poly3) {
  barycentric_coordinates.setCoordinates(poly1, poly2, poly3);
}

void Shape::choosenActive() { color = sf::Color{255, 36, 0, 255}; }

void Shape::choosenFinal() { color = sf::Color{65, 105, 255, 255}; }

void Shape::make_actual() {}

sf::Color Shape::getColor() { return color; }

BarycentricCoordinates Shape::getCoordinates() {
  return barycentric_coordinates;
}

Point::Point() {
  circle.setRadius(5.f);
  circle.setOrigin(sf::Vector2f(5,5));
  name.setName(global::next_name);
  global::next_name = global::next_name + 1;
  choosenFinal();
}

Point::Point(double x_pos, double y_pos) : Point() {
  x_coord_ = x_pos;
  y_coord_ = y_pos;
  circle.move(x_pos, y_pos);
}

BasePoint::BasePoint(double x_pos, double y_pos) : Point(x_pos, y_pos) {}

void BasePoint::draw() {
  circle.setFillColor(getColor());
  circle.setPosition(x_coord_, y_coord_);
  global::window.draw(circle);
  name.setPosition(x_coord_, y_coord_);
  if(!getIsHidden()) {
    global::window.draw(name.getName());
  }
}

MiddlePoint::MiddlePoint(Point* a_point, Point* b_point)
    : Point(), a_point_(a_point), b_point_(b_point) {
  BarycentricCoordinates barycentric_coordinates_a = a_point_->getCoordinates();
  BarycentricCoordinates barycentric_coordinates_b = b_point_->getCoordinates();
  GiNaC::ex sum_a = barycentric_coordinates_a.getACoordinate() +
                    barycentric_coordinates_a.getBCoordinate() +
                    barycentric_coordinates_a.getCCoordinate();
  GiNaC::ex sum_b = barycentric_coordinates_b.getACoordinate() +
                    barycentric_coordinates_b.getBCoordinate() +
                    barycentric_coordinates_b.getCCoordinate();
  barycentric_coordinates.setCoordinates(
      (barycentric_coordinates_a.getACoordinate() / sum_a +
       barycentric_coordinates_b.getACoordinate() / sum_b)
          .normal(),
      (barycentric_coordinates_a.getBCoordinate() / sum_a +
       barycentric_coordinates_b.getBCoordinate() / sum_b)
          .normal(),
      (barycentric_coordinates_a.getCCoordinate() / sum_a +
       barycentric_coordinates_b.getCCoordinate() / sum_b)
          .normal());
  barycentric_coordinates.simplify();
}

void MiddlePoint::make_actual() {
  x_coord_ = (a_point_->x_coord_ + b_point_->x_coord_) / 2;
  y_coord_ = (a_point_->y_coord_ + b_point_->y_coord_) / 2;
  circle.setPosition(x_coord_, y_coord_);
  name.setPosition(x_coord_, y_coord_);
}

void Line::make_actual() {
  sf::Color tmp_color = getColor();
  line[0] = sf::Vertex(a_point_->getPosition(), tmp_color);
  line[1] = sf::Vertex(b_point_->getPosition(), tmp_color);
}

void Line::draw() {
  make_actual();
  global::window.draw(line, 2, sf::Lines);
}

void MiddlePoint::draw() {
  make_actual();
  circle.setFillColor(getColor());
  global::window.draw(circle);
  if(!getIsHidden()) {
    global::window.draw(name.getName());
  }
}

Line::Line(Point* a_point, Point* b_point)
    : a_point_(a_point), b_point_(b_point) {
  make_actual();
  BarycentricCoordinates barycentric_coordinates_a = a_point_->getCoordinates();
  BarycentricCoordinates barycentric_coordinates_b = b_point_->getCoordinates();
  GiNaC::ex new_coordinate_a = barycentric_coordinates_a.getBCoordinate() *
                                   barycentric_coordinates_b.getCCoordinate() -
                               barycentric_coordinates_a.getCCoordinate() *
                                   barycentric_coordinates_b.getBCoordinate();
  GiNaC::ex new_coordinate_b = barycentric_coordinates_a.getCCoordinate() *
                                   barycentric_coordinates_b.getACoordinate() -
                               barycentric_coordinates_a.getACoordinate() *
                                   barycentric_coordinates_b.getCCoordinate();
  GiNaC::ex new_coordinate_c = barycentric_coordinates_a.getACoordinate() *
                                   barycentric_coordinates_b.getBCoordinate() -
                               barycentric_coordinates_a.getBCoordinate() *
                                   barycentric_coordinates_b.getACoordinate();
  barycentric_coordinates.setCoordinates(new_coordinate_a.normal(),
                                         new_coordinate_b.normal(),
                                         new_coordinate_c.normal());
  barycentric_coordinates.simplify();
  choosenFinal();
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
      sf::Vector2i(Point::x_coord_, Point::y_coord_));
  ;
}

double Line::getDistance() {
  sf::Vector2f cur_mouse_pos =
      global::window.mapPixelToCoords(sf::Mouse::getPosition(global::window));
  sf::Vector2f a_to_global = global::window.mapPixelToCoords(
      sf::Vector2i(a_point_->x_coord_, a_point_->y_coord_));
  sf::Vector2f b_to_global = global::window.mapPixelToCoords(
      sf::Vector2i(b_point_->x_coord_, b_point_->y_coord_));
  double A = a_to_global.y - b_to_global.y;
  double B = b_to_global.x - a_to_global.x;
  double C = a_to_global.x * b_to_global.y - a_to_global.y * b_to_global.x;
  return std::abs((A * cur_mouse_pos.x + B * cur_mouse_pos.y + C) /
                  sqrt(A * A + B * B));
}

Point* Line::getPointA() { return a_point_; }

Point* Line::getPointB() { return b_point_; }

std::vector<double> Line::getCoefficients() {
  sf::Vector2f a_to_global = global::window.mapPixelToCoords(
      sf::Vector2i(a_point_->x_coord_, a_point_->y_coord_));
  sf::Vector2f b_to_global = global::window.mapPixelToCoords(
      sf::Vector2i(b_point_->x_coord_, b_point_->y_coord_));
  std::vector<double> coefficients;
  coefficients.push_back(a_to_global.y - b_to_global.y);
  coefficients.push_back(b_to_global.x - a_to_global.x);
  coefficients.push_back(a_to_global.x * b_to_global.y -
                         a_to_global.y * b_to_global.x);
  return coefficients;
}

template <typename T>
std::vector<T> FindCoordinate(const T& A1, const T& B1, const T& C1,
                              const T& A2, const T& B2, const T& C2) {
  return std::vector<T>{-B1 * C2 + B2 * C1, -A2 * C1 + A1 * C2,
                        -A1 * B2 + B1 * A2};
}

PointByTwoLines::PointByTwoLines(Line* a_line, Line* b_line)
    : Point(), a_line_(a_line), b_line_(b_line) {
  make_actual();
  BarycentricCoordinates barycentric_coordinates_a = a_line_->getCoordinates();
  BarycentricCoordinates barycentric_coordinates_b = b_line_->getCoordinates();
  std::vector<GiNaC::ex> new__coordinates =
      FindCoordinate<GiNaC::ex>(barycentric_coordinates_a.getACoordinate(),
                                barycentric_coordinates_a.getBCoordinate(),
                                barycentric_coordinates_a.getCCoordinate(),
                                barycentric_coordinates_b.getACoordinate(),
                                barycentric_coordinates_b.getBCoordinate(),
                                barycentric_coordinates_b.getCCoordinate());
  barycentric_coordinates.setCoordinates(new__coordinates[0].normal(),
                                         new__coordinates[1].normal(),
                                         new__coordinates[2].normal());
  barycentric_coordinates.simplify();
}

void PointByTwoLines::draw() {
  make_actual();
  circle.setFillColor(getColor());
  global::window.draw(circle);
  if(!getIsHidden()) {  
    global::window.draw(name.getName());
  }
}

void PointByTwoLines::make_actual() {
  std::vector<double> coefficients_a = a_line_->getCoefficients();
  std::vector<double> coefficients_b = b_line_->getCoefficients();
  double det = coefficients_a[0] * coefficients_b[1] -
               coefficients_a[1] * coefficients_b[0];
  double det_a = coefficients_a[2] * coefficients_b[1] -
                 coefficients_a[1] * coefficients_b[2];
  double det_b = coefficients_a[0] * coefficients_b[2] -
                 coefficients_a[2] * coefficients_b[0];
  x_coord_ = -det_a / det;
  y_coord_ = -det_b / det;
  circle.setPosition(x_coord_, y_coord_);
  name.setPosition(x_coord_, y_coord_);
}

Incenter::Incenter(Point* a_point, Point* b_point, Point* c_point)
    : Point(), a_point_(a_point), b_point_(b_point), c_point_(c_point) {
  make_actual();
  barycentric_coordinates.setCoordinates(a, b, c);
  choosenFinal();
}

void Incenter::make_actual() {
  sf::Vector2f a_position = a_point_->getPosition();
  sf::Vector2f b_position = b_point_->getPosition();
  sf::Vector2f c_position = c_point_->getPosition();
  double c_size =
      sqrt((a_position - b_position).x * (a_position - b_position).x +
           (a_position - b_position).y * (a_position - b_position).y);
  double b_size =
      sqrt((a_position - c_position).x * (a_position - c_position).x +
           (a_position - c_position).y * (a_position - c_position).y);
  double a_size =
      sqrt((c_position - b_position).x * (c_position - b_position).x +
           (c_position - b_position).y * (c_position - b_position).y);
  double sum = a_size + b_size + c_size;
  x_coord_ =
      (a_position.x * a_size + b_position.x * b_size + c_position.x * c_size) /
      sum;
  y_coord_ =
      (a_position.y * a_size + b_position.y * b_size + c_position.y * c_size) /
      sum;
  circle.setPosition(x_coord_, y_coord_);
  name.setPosition(x_coord_, y_coord_);
}

void Incenter::draw() {
  make_actual();
  global::window.draw(circle);
  circle.setFillColor(getColor());
  if(!getIsHidden()) {
    global::window.draw(name.getName());
  }
}

Orthocenter::Orthocenter(Point* a_point, Point* b_point, Point* c_point)
    :Point(), a_point_(a_point), b_point_(b_point), c_point_(c_point) {
  make_actual();
  barycentric_coordinates.setCoordinates(1 / (b * b + c * c - a * a),
                                         1 / (c * c - b * b + a * a),
                                         1 / (b * b - c * c + a * a));
}

void Orthocenter::draw() {
  make_actual();
  global::window.draw(circle);
  circle.setFillColor(getColor());
  if(!getIsHidden()) {
    global::window.draw(name.getName());
  }
}

void Orthocenter::make_actual() {
  sf::Vector2f a_position = a_point_->getPosition();
  sf::Vector2f b_position = b_point_->getPosition();
  sf::Vector2f c_position = c_point_->getPosition();
  double Dxa = 2*(b_position.x - c_position.x);
  double Dxb = 2*(c_position.x - a_position.x);
  double Dxc = 2*(a_position.x - b_position.x);
  double Dya = 2*(b_position.y - c_position.y);
  double Dyb = 2*(c_position.y - a_position.y);
  double Dyc = 2*(a_position.y - b_position.y);
  double Sa = a_position.x * a_position.x + a_position.y * a_position.y;
  double Sb = b_position.x * b_position.x + b_position.y * b_position.y;
  double Sc = c_position.x * c_position.x + c_position.y * c_position.y;
  std::vector<double> det = FindCoordinate<double>(Dxc, Dyc, Sa - Sb, Dxa, Dya, Sb - Sc);

  double x_coord_tmp = -det[0] / det[2];
  double y_coord_tmp = -det[1] / det[2];

  x_coord_ = a_position.x + b_position.x + c_position.x - 2  * x_coord_tmp;
  y_coord_ = a_position.y + b_position.y + c_position.y - 2  * y_coord_tmp;

  circle.setPosition(x_coord_, y_coord_);
  name.setPosition(x_coord_, y_coord_);
}

IsogonalPoint::IsogonalPoint(Point* a_point, Point* b_point, Point* c_point,
                             Point* origin_point)
    :Point(), a_point_(a_point),
      b_point_(b_point),
      c_point_(c_point),
      origin_point_(origin_point) {
  make_actual();
  BarycentricCoordinates barycentric_coordinates_origin =
      origin_point->getCoordinates();
  barycentric_coordinates.setCoordinates(
      a * a / barycentric_coordinates_origin.getACoordinate(),
      b * b / barycentric_coordinates_origin.getBCoordinate(),
      c * c / barycentric_coordinates_origin.getCCoordinate());
  barycentric_coordinates.simplify();
}

std::vector<double> FindreFlectionLine(std::vector<double> line1,
                                       std::vector<double> line2) {
  double alpha = -2 * (line1[0] * line2[0] + line1[1] * line2[1]);
  double betta = (line1[0] * line1[0] + line1[1] * line1[1]);
  return std::vector<double>{alpha * line1[0] + betta * line2[0],
                             alpha * line1[1] + betta * line2[1],
                             alpha * line1[2] + betta * line2[2]};
}

void IsogonalPoint::make_actual() {
  sf::Vector2f a_position = a_point_->getPosition();
  sf::Vector2f b_position = b_point_->getPosition();
  sf::Vector2f c_position = c_point_->getPosition();
  sf::Vector2f position = origin_point_->getPosition();

  std::vector<double> line_ab = FindCoordinate<double>(
      a_position.x, a_position.y, 1, b_position.x, b_position.y, 1);
  std::vector<double> line_ac = FindCoordinate<double>(
      a_position.x, a_position.y, 1, c_position.x, c_position.y, 1);
  double normal_ab = sqrt(line_ab[0] * line_ab[0] + line_ab[1] * line_ab[1]);
  double normal_ac = sqrt(line_ac[0] * line_ac[0] + line_ac[1] * line_ac[1]);
  std::vector<double> bisector_a =
      std::vector{line_ab[0] / normal_ab - line_ac[0] / normal_ac,
                  line_ab[1] / normal_ab - line_ac[1] / normal_ac,
                  line_ab[2] / normal_ab - line_ac[2] / normal_ac};
  std::vector<double> line_ax = FindCoordinate<double>(
      a_position.x, a_position.y, 1, position.x, position.y, 1);
  std::vector<double> reflection_ax = FindreFlectionLine(bisector_a, line_ax);

  std::vector<double> line_ba = line_ab;
  std::vector<double> line_bc = FindCoordinate<double>(
      c_position.x, c_position.y, 1, b_position.x, b_position.y, 1);
  double normal_ba = normal_ab;
  double normal_bc = sqrt(line_bc[0] * line_bc[0] + line_bc[1] * line_bc[1]);
  std::vector<double> bisector_b =
      std::vector{line_ba[0] / normal_ba - line_bc[0] / normal_bc,
                  line_ba[1] / normal_ba - line_bc[1] / normal_bc,
                  line_ba[2] / normal_ba - line_bc[2] / normal_bc};
  std::vector<double> line_bx = FindCoordinate<double>(
      b_position.x, b_position.y, 1, position.x, position.y, 1);
  std::vector<double> reflection_bx = FindreFlectionLine(bisector_b, line_bx);

  std::vector<double> isogonal_x = FindCoordinate<double>(
      reflection_ax[0], reflection_ax[1], reflection_ax[2], reflection_bx[0],
      reflection_bx[1], reflection_bx[2]);

  x_coord_ = isogonal_x[0] / isogonal_x[2];
  y_coord_ = isogonal_x[1] / isogonal_x[2];

  circle.setPosition(x_coord_, y_coord_);
  name.setPosition(x_coord_, y_coord_);
}

void IsogonalPoint::draw() {
  make_actual();
  global::window.draw(circle);
  circle.setFillColor(getColor());
  if(!getIsHidden()) {
    global::window.draw(name.getName());
  }
}

template <typename T>
T FindСoefficientInCircle(const T& A, const T& B, const T& C) {
  return (a * a * B * C + b * b * A * C + c * c * A * B) / (A + B + C);
}

template <typename T>
T FindDet(const T& A1, const T& B1, const T& C1, const T& A2, const T& B2,
          const T& C2, const T& A3, const T& B3, const T& C3) {
  return A1 * B2 * C3 + A3 * C2 * B1 + C1 * A2 * B3 - C1 * B2 * A3 -
         B1 * A2 * C3 - A1 * C2 * B3;
}

Circle::Circle(Point* a_point, Point* b_point, Point* c_point)
    : a_point_(a_point), b_point_(b_point), c_point_(c_point) {
  make_actual();
  shape.setFillColor(sf::Color(0, 0, 0, 0));
  shape.setOutlineThickness(2);
  shape.setOutlineColor(sf::Color(255, 255, 255, 255));
  shape.setPointCount(100);
  BarycentricCoordinates a_coordinates = a_point_->getCoordinates();
  BarycentricCoordinates b_coordinates = b_point_->getCoordinates();
  BarycentricCoordinates c_coordinates = c_point_->getCoordinates();
  GiNaC::ex coefficient1 = FindСoefficientInCircle<GiNaC::ex>(
      a_coordinates.getACoordinate(), a_coordinates.getBCoordinate(),
      a_coordinates.getCCoordinate());
  GiNaC::ex coefficient2 = FindСoefficientInCircle<GiNaC::ex>(
      b_coordinates.getACoordinate(), b_coordinates.getBCoordinate(),
      b_coordinates.getCCoordinate());
  GiNaC::ex coefficient3 = FindСoefficientInCircle<GiNaC::ex>(
      c_coordinates.getACoordinate(), c_coordinates.getBCoordinate(),
      c_coordinates.getCCoordinate());
  GiNaC::ex det =
      FindDet(a_coordinates.getACoordinate(), a_coordinates.getBCoordinate(),
              a_coordinates.getCCoordinate(), b_coordinates.getACoordinate(),
              b_coordinates.getBCoordinate(), b_coordinates.getCCoordinate(),
              c_coordinates.getACoordinate(), c_coordinates.getBCoordinate(),
              c_coordinates.getCCoordinate());
  GiNaC::ex det_a =
      FindDet(coefficient1, a_coordinates.getBCoordinate(),
              a_coordinates.getCCoordinate(), coefficient2,
              b_coordinates.getBCoordinate(), b_coordinates.getCCoordinate(),
              coefficient3, c_coordinates.getBCoordinate(),
              c_coordinates.getCCoordinate());
  GiNaC::ex det_b =
      FindDet(a_coordinates.getACoordinate(), coefficient1,
              a_coordinates.getCCoordinate(), b_coordinates.getACoordinate(),
              coefficient2, b_coordinates.getCCoordinate(),
              c_coordinates.getACoordinate(), coefficient3,
              c_coordinates.getCCoordinate());
  GiNaC::ex det_c =
      FindDet(a_coordinates.getACoordinate(), a_coordinates.getBCoordinate(),
              coefficient1, b_coordinates.getACoordinate(),
              b_coordinates.getBCoordinate(), coefficient2,
              c_coordinates.getACoordinate(), c_coordinates.getBCoordinate(),
              coefficient3);

  barycentric_coordinates.setCoordinates(det_a / det, det_b / det, det_c / det);

  //barycentric_coordinates.simplify();
 // a_coordinates.print();
 // b_coordinates.print();
 // c_coordinates.print();
 // std::cout << coefficient1 << " " << coefficient2 << " " << coefficient3
   //         << std::endl;
  //std::cout << barycentric_coordinates.getACoordinate() << "  "
    //        << barycentric_coordinates.getBCoordinate() << "  "
      //      << barycentric_coordinates.getCCoordinate() << std::endl;
 // std::cout << center_x_ << " " << center_y_ << std::endl;
  choosenFinal();
}

void Circle::make_actual() {
  sf::Vector2f a_position = a_point_->getPosition();
  sf::Vector2f b_position = b_point_->getPosition();
  sf::Vector2f c_position = c_point_->getPosition();
  a_position = a_position;
  b_position = b_position;
  c_position = c_position;

  double z1 = a_position.x * a_position.x + a_position.y * a_position.y;
  double z2 = b_position.x * b_position.x + b_position.y * b_position.y;
  double z3 = c_position.x * c_position.x + c_position.y * c_position.y;

  double x12 = a_position.x - b_position.x;
  double x23 = b_position.x - c_position.x;
  double x31 = c_position.x - a_position.x;

  double y12 = a_position.y - b_position.y;
  double y23 = b_position.y - c_position.y;
  double y31 = c_position.y - a_position.y;

  double z_x = y31 * (z1 - z2) - y12 * (z3 - z1);
  double z_y = x12 * (z3 - z1) - x31 * (z1 - z2);
  double z = x12 * y31 - y12 * x31;

  center_x_ = z_x / 2 / z;
  center_y_ = z_y / 2 / z;

  double radius_a =
      sqrt((a_position.x - center_x_) * (a_position.x - center_x_) +
           (a_position.y - center_y_) * (a_position.y - center_y_));

  double radius_b =
      sqrt((b_position.x - center_x_) * (b_position.x - center_x_) +
           (b_position.y - center_y_) * (b_position.y - center_y_));

  double radius_c =
      sqrt((c_position.x - center_x_) * (c_position.x - center_x_) +
           (c_position.y - center_y_) * (c_position.y - center_y_));
  shape.setOutlineColor(getColor());
  radius_ = (radius_a + radius_b + radius_c) / 3;
  shape.setPosition(center_x_ - radius_, center_y_ - radius_);
  shape.setRadius(radius_);
}

void Circle::draw() {
  make_actual();
  global::window.draw(shape);
}

double Circle::getDistance() {  
  sf::Vector2f cur_mouse_pos = global::window.mapPixelToCoords(sf::Mouse::getPosition(global::window));
  sf::Vector2f center_pos = global::window.mapPixelToCoords(sf::Vector2i(center_x_, center_y_));
  double dist = sqrt((center_pos.x - cur_mouse_pos.x) * (center_pos.x - cur_mouse_pos.x) + (center_pos.y - cur_mouse_pos.y) * (center_pos.y - cur_mouse_pos.y));
  return fabs(dist - radius_);
}

PointIntersectionByLineCircle::PointIntersectionByLineCircle(Circle* base_circle, Line* line, Point* point) :Point(), circle_(base_circle), line_(line), point_(point) {

  BarycentricCoordinates circle_coordinate = circle_ -> getCoordinates();
  BarycentricCoordinates line_coordinate = line_ -> getCoordinates();
  BarycentricCoordinates point_coordinate = point_ -> getCoordinates();
  GiNaC::ex Da = line_coordinate.getBCoordinate() -line_coordinate.getCCoordinate();
  GiNaC::ex Db = line_coordinate.getCCoordinate() -line_coordinate.getACoordinate();
  GiNaC::ex Dc = line_coordinate.getACoordinate() -line_coordinate.getBCoordinate();
  GiNaC::ex X0 = point_coordinate.getACoordinate();
  GiNaC::ex Y0 = point_coordinate.getBCoordinate();
  GiNaC::ex Z0 = point_coordinate.getCCoordinate();
  GiNaC::ex det = a * a * Db * Dc + b * b * Dc * Da + c * c * Da * Db;
  GiNaC::ex det_a = -a * a * (Db * Z0 + Dc * Y0);
  GiNaC::ex det_b = -b * b * (Dc * X0 + Da * Z0);
  GiNaC::ex det_c = -c * c * (Da * Y0 + Db * X0);
  GiNaC::ex det_more = (X0 + Y0 + Z0) * (circle_coordinate.getACoordinate() * Da + circle_coordinate.getBCoordinate() * Db + circle_coordinate.getCCoordinate() * Dc);
  GiNaC::ex delta = (det_more + det_a + det_b + det_c) / det;
  barycentric_coordinates.setCoordinates(X0  + delta * Da, Y0  + delta * Db, Z0  + delta * Dc);
  barycentric_coordinates.simplify();
  make_actual();
  barycentric_coordinates.simplify();
}

void PointIntersectionByLineCircle::make_actual() {
  std::vector<double> line_coordinate = line_ -> getCoefficients();
  sf::Vector2f position = point_ -> getPosition();
  double sum = line_coordinate[0] * line_coordinate[0] + line_coordinate[1] * line_coordinate[1];
  double tmp = 2 * circle_ -> center_x_* line_coordinate[1] * line_coordinate[1] - 2 * line_coordinate[0] * line_coordinate[1] * circle_ -> center_y_ - 2 * line_coordinate[0]  * line_coordinate[2];
  x_coord_ = tmp / sum - position.x; 
  y_coord_ = (-line_coordinate[2] - line_coordinate[0] * x_coord_) / line_coordinate[1];
  x_coord_ = x_coord_;
  y_coord_ = y_coord_;
  circle.setPosition(x_coord_, y_coord_);
  name.setPosition(x_coord_, y_coord_);
}

void PointIntersectionByLineCircle::draw() {
  make_actual();
  circle.setFillColor(getColor());
  global::window.draw(circle);
  circle.setFillColor(getColor());
  if(!getIsHidden()) {
    global::window.draw(name.getName());
  }
}


PerpendicularLine::PerpendicularLine(Line* line, Point* point) : base_point_(point), base_line_(line) {
  a_point_ = line -> getPointA(); 
  b_point_ = line -> getPointB();
  make_actual();
  BarycentricCoordinates tmp_bar =  base_line_ -> getCoordinates();
  BarycentricCoordinates tmp_bar_point =  base_point_ -> getCoordinates();

  GiNaC::ex X0 = (b * b + c * c - a * a) * (tmp_bar.getCCoordinate() - tmp_bar.getBCoordinate());
  GiNaC::ex Y0 = (-b * b + c * c + a * a) * (tmp_bar.getACoordinate() - tmp_bar.getCCoordinate());
  GiNaC::ex Z0 = (b * b - c * c + a * a) * (tmp_bar.getBCoordinate() - tmp_bar.getACoordinate());
  GiNaC::ex X1 = Y0 - Z0;
  GiNaC::ex Y1 = Z0 - X0;
  GiNaC::ex Z1 = X0 - Y0;
  std::vector<GiNaC::ex> new_pos = FindCoordinate<GiNaC::ex>(X1, Y1, Z1, tmp_bar_point.getACoordinate(), tmp_bar_point.getBCoordinate(), tmp_bar_point.getCCoordinate());

  barycentric_coordinates.setCoordinates(new_pos[0], new_pos[1], new_pos[2]);

  barycentric_coordinates.simplify();
  choosenFinal();
}


void  PerpendicularLine::make_actual() {
  sf::Color tmp_color = getColor();
  std::vector<double> line_coordinate = getCoefficients();
  line[0] = sf::Vertex(sf::Vector2f(0, -line_coordinate[2] / line_coordinate[1]), tmp_color);
  line[1] = sf::Vertex(sf::Vector2f(1400, (-line_coordinate[2] -line_coordinate[0] * 1400) / line_coordinate[1]), tmp_color);
}


Point* PerpendicularLine::getPointA() {
  return a_point_;
}

Point* PerpendicularLine::getPointB() { 
  return b_point_;
}

Point* PerpendicularLine::getBasePoint() { 
  return base_point_;
}


std::vector<double> PerpendicularLine::getCoefficients() {
  sf::Vector2f base_position = base_point_->getPosition();
  std::vector<double> line_coord = base_line_ ->  getCoefficients();
  std::vector<double> new_position = {-line_coord[1], line_coord[0], line_coord[1] * base_position.x - line_coord[0] * base_position.y};
  return new_position;
}

void PerpendicularLine::draw() {
   make_actual();
   global::window.draw(line, 2, sf::Lines);
}
 
double PerpendicularLine::getDistance() {
   sf::Vector2f cur_mouse_pos = global::window.mapPixelToCoords(sf::Mouse::getPosition(global::window));
   std::vector<double> cofficients = getCoefficients();
   double dist =  fabs(cofficients[0] * cur_mouse_pos.x + cofficients[1] * cur_mouse_pos.y + cofficients[2]) / sqrt(cofficients[0] * cofficients[0]+ cofficients[1] * cofficients[1]);
   return dist;
}

  void VectorDiff::simplify() {
    BarycentricCoordinates tmp;
    tmp.setCoordinates(A_diff, B_diff, C_diff);
    tmp.simplify();
    A_diff = tmp.getACoordinate();
    B_diff = tmp.getBCoordinate();
    C_diff = tmp.getCCoordinate();
  }

  VectorDiff::VectorDiff(Point* point_a, Point* point_b)
      : point_a_(point_a), point_b_(point_b) {
    BarycentricCoordinates point_a_coordinate = point_a_->getCoordinates();
    BarycentricCoordinates point_b_coordinate = point_b_->getCoordinates();
    GiNaC::ex sum_a = point_a_coordinate.getACoordinate() +
                      point_a_coordinate.getBCoordinate() +
                      point_a_coordinate.getCCoordinate();
    GiNaC::ex sum_b = point_b_coordinate.getACoordinate() +
                      point_b_coordinate.getBCoordinate() +
                      point_b_coordinate.getCCoordinate();
    A_diff = (point_a_coordinate.getACoordinate() / sum_a -
              point_b_coordinate.getACoordinate() / sum_b)
                 .normal();
    B_diff = (point_a_coordinate.getBCoordinate() / sum_a -
              point_b_coordinate.getBCoordinate() / sum_b)
                 .normal();
    C_diff = (point_a_coordinate.getCCoordinate() / sum_a -
              point_b_coordinate.getCCoordinate() / sum_b)
                 .normal();
  }
  GiNaC::ex VectorDiff::A() { return A_diff; }
  GiNaC::ex VectorDiff::B() { return B_diff; }
  GiNaC::ex VectorDiff::C() { return C_diff; }
  void VectorDiff::setCoord(GiNaC::ex A_c, GiNaC::ex B_c, GiNaC::ex C_c) {
    A_diff = A_c;
    B_diff = B_c;
    C_diff = C_c;
  }

  ParallelLine::ParallelLine(Line* line, Point* point) : base_point_(point), base_line_(line) {
    make_actual();
    a_point_ = line -> getPointA();
    b_point_ = line -> getPointB();
    BarycentricCoordinates tmp_bar =  base_line_ -> getCoordinates();
    BarycentricCoordinates tmp_bar_point =  base_point_ -> getCoordinates();
    GiNaC::ex X0 = tmp_bar.getBCoordinate() - tmp_bar.getCCoordinate();
    GiNaC::ex Y0 = tmp_bar.getCCoordinate() - tmp_bar.getACoordinate();
    GiNaC::ex Z0 = tmp_bar.getACoordinate() - tmp_bar.getBCoordinate();
    std::vector<GiNaC::ex> new_pos = FindCoordinate<GiNaC::ex>(X0, Y0, Z0, tmp_bar_point.getACoordinate(), tmp_bar_point.getBCoordinate(), tmp_bar_point.getCCoordinate());
    barycentric_coordinates.setCoordinates(new_pos[0], new_pos[1], new_pos[2]); 
    barycentric_coordinates.simplify();
    choosenFinal();
  }

  std::vector<double>  ParallelLine::getCoefficients() {
    std::vector<double> line_coordinate = base_line_ -> getCoefficients();
    sf::Vector2f a_position = base_point_ ->getPosition();
    line_coordinate[2] = -(line_coordinate[0] * a_position.x + line_coordinate[1] * a_position.y);
    return line_coordinate;
  }
  void  ParallelLine::make_actual() {
   sf::Color tmp_color = getColor();
    std::vector<double> line_coordinate = getCoefficients();
    line[0] = sf::Vertex(sf::Vector2f(0, -line_coordinate[2] / line_coordinate[1]), tmp_color);
    line[1] = sf::Vertex(sf::Vector2f(1400, (-line_coordinate[2] -line_coordinate[0] * 1400) / line_coordinate[1]), tmp_color);
  }
  
  double ParallelLine::getDistance() {
    sf::Vector2f cur_mouse_pos = global::window.mapPixelToCoords(sf::Mouse::getPosition(global::window));
    std::vector<double> cofficients = getCoefficients();
    double dist =  fabs(cofficients[0] * cur_mouse_pos.x + cofficients[1] * cur_mouse_pos.y + cofficients[2]) / sqrt(cofficients[0] * cofficients[0]+ cofficients[1] * cofficients[1]);
    return dist;

  }
  void ParallelLine::draw() {
    make_actual();
    global::window.draw(line, 2, sf::Lines);
  }

  Point* ParallelLine::getPointA() {
    return a_point_;
  }

  Point* ParallelLine::getPointB() {
    return b_point_;
  }


RadicalAxis::RadicalAxis(Circle* circle1, Circle* circle2): circle1_(circle1), circle2_(circle2) {
  make_actual();
  BarycentricCoordinates barycentric_coordinates_circle_1 = circle1_ -> getCoordinates();
  BarycentricCoordinates barycentric_coordinates_circle_2 = circle2_ -> getCoordinates();
  barycentric_coordinates.setCoordinates(barycentric_coordinates_circle_1.getACoordinate() - barycentric_coordinates_circle_2.getACoordinate(), barycentric_coordinates_circle_1.getBCoordinate() - barycentric_coordinates_circle_2.getBCoordinate(), barycentric_coordinates_circle_1.getCCoordinate() - barycentric_coordinates_circle_2.getCCoordinate());
   barycentric_coordinates.simplify();
   choosenFinal();
}

std::vector<double>  RadicalAxis::getCoefficients() {
 double X1 = circle1_ -> center_x_;
 double Y1 = circle1_ -> center_y_;
 double X2 = circle2_ -> center_x_;
 double Y2 = circle2_ -> center_y_;
 double A = 2 * X1 - 2 * X2;
 double B = 2 * Y1 - 2 * Y2;
 double C = X2 * X2 + Y2 * Y2 - X1 * X1 - Y1 * Y1 - circle2_ -> radius_ *  circle2_ -> radius_ + circle1_ -> radius_ *  circle1_ -> radius_;
 return std::vector<double>{A,B,C};
}

 void  RadicalAxis::make_actual() {
  sf::Color tmp_color = getColor();
  std::vector<double> line_coordinate = getCoefficients();
  line[0] = sf::Vertex(sf::Vector2f(0, -line_coordinate[2] / line_coordinate[1]), tmp_color);
  line[1] = sf::Vertex(sf::Vector2f(1400, (-line_coordinate[2] -line_coordinate[0] * 1400) / line_coordinate[1]), tmp_color);
}


void RadicalAxis::draw() {
  make_actual();
  global::window.draw(line, 2, sf::Lines);
}


double RadicalAxis::getDistance() {
  sf::Vector2f cur_mouse_pos = global::window.mapPixelToCoords(sf::Mouse::getPosition(global::window));
  std::vector<double> cofficients = getCoefficients();
  double dist =  fabs(cofficients[0] * cur_mouse_pos.x + cofficients[1] * cur_mouse_pos.y + cofficients[2]) / sqrt(cofficients[0] * cofficients[0]+ cofficients[1] * cofficients[1]);
  return dist;
}

