#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Object {
public:
  virtual void draw() = 0;
};

class Shape : public Object {
public:
  virtual double getDistance() = 0;
};

class Point : public Shape {
public:
  Point() = default;
  Point(double x_pos, double y_pos);

  double getDistance() final;

  void draw() override = 0;

  double x_coord_;
  double y_coord_;
  sf::CircleShape circle;
};

class BasePoint : public Point {
public:
  void draw() final;

  BasePoint(double x_pos, double y_pos) : Point(x_pos, y_pos) {}
};

class MiddlePoint : public Point {
private:
  Point* a_point_ = nullptr;
  Point* b_point_ = nullptr;
public:
  void draw() final;
  void make_actual();

  MiddlePoint(Point* a_point, Point* b_point);
};

class Line : public Shape {
private:
  Point* a_point_ = nullptr;
  Point* b_point_ = nullptr;
public:
  void draw() final;

  Line(Point* a_point, Point* b_point);
};

class Circle;

//class PointByTwoPoints : public Point {
//public:
//  PointByTwoPoints(Point* pnt1, Point* pnt2, double ratio) : parent_shape_first(pnt1), parent_shape_second(pnt2) {
//    circle.setRadius(5.f);
//    circle.move((pnt1->x_coord_ + pnt2->x_coord_) / 2, (pnt1->y_coord_ + pnt2->y_coord_) / ratio);
//  }
//
//  Shape* parent_shape_first;
//  Shape* parent_shape_second;
//};

class PointByTwoLines : public Point {

};

namespace global {
  extern sf::RenderWindow window;
}
