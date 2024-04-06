#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "NameBox.h"
#include "BarycentricCoordinates.h"

class Object {
public:
  virtual void draw() = 0;
};

class Shape : public Object {
private:
sf::Color color;
public:
  virtual double getDistance() = 0;
  BarycentricCoordinates barycentric_coordinates;
  void setCoordinates(GiNaC::ex poly1, GiNaC::ex poly2, GiNaC::ex poly3);
  BarycentricCoordinates getCoordinates();
  virtual void choosenActive();
  virtual void choosenFinal();
  sf::Color getColor();
  virtual void make_actual();
};

class Point : public Shape {
public:
  Point() = default;
  Point(double x_pos, double y_pos);

  double getDistance() final;
  sf::Vector2f getPosition();
  void draw() override = 0;
  double x_coord_;
  double y_coord_;
  sf::CircleShape circle;
  NameBox name;
};

class BasePoint : public Point {
public:
  void draw() final;
  BasePoint(double x_pos, double y_pos);
};

class MiddlePoint : public Point {
private:
  Point* a_point_ = nullptr;
  Point* b_point_ = nullptr;
public:
  void draw() final;
  void make_actual() final;

  MiddlePoint(Point* a_point, Point* b_point);
};

class Line : public Shape {
private:
  Point* a_point_ = nullptr;
  Point* b_point_ = nullptr;
  sf::Vertex line[2];
public:
  void make_actual() final;
  double getDistance() final;
  void draw() final;
  Line(Point* a_point, Point* b_point);
  std::vector<double> getСoefficients();
  Point* getPointA();
  Point* getPointB();
};





class PointByTwoLines : public Point {
private:
  Line* a_line_ = nullptr;
  Line* b_line_ = nullptr;
public:
  PointByTwoLines(Line* a_line, Line* b_line);
  void draw() final;
  void make_actual() final;
};

class Incenter : public Point {
  public:
  void draw() final;
  Incenter(Point* a_point, Point* b_point,Point* c_point);
  Point* a_point_ = nullptr;
  Point* b_point_ = nullptr;
  Point* c_point_ = nullptr;
  void make_actual() final;
};

class Orthocenter : public Point {
  public:
  void draw() final;
  Orthocenter(Point* a_point, Point* b_point,Point* c_point);
  Point* a_point_ = nullptr;
  Point* b_point_ = nullptr;
  Point* c_point_ = nullptr;
  void make_actual() final;
};

namespace global {
  extern sf::RenderWindow window;
  extern char next_name;
}

class IsogonalPoint : public Point {
  Point* a_point_ = nullptr;
  Point* b_point_ = nullptr;
  Point* c_point_ = nullptr;
  Point* origin_point_= nullptr;
  public:
  void make_actual() final;
  void draw() final;
  IsogonalPoint(Point* a_point, Point* b_point,Point* c_point, Point* origin_point);
};

class Circle : public Shape {
   Point* a_point_ = nullptr;
   Point* b_point_ = nullptr;
   Point* c_point_ = nullptr;
   sf::CircleShape shape;
   double center_x_;
   double center_y_;
   double radius_;
   public:
   void make_actual() final;
   void draw() final;
   Circle(Point* a_point, Point* b_point,Point* c_point);
};
