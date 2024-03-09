#include <iostream>
#include <SFML/Graphics.hpp>



class Shape {
  public:
  virtual void draw() = 0;
  virtual double getDistance() =0;
};

class Point:public Shape {
   public:
   Point(double x_pos, double y_pos):x_coord_(x_pos),y_coord_(y_pos) {
     circle.setRadius(5.f);
     circle.move(x_pos, y_pos);
   }
   Point() {}
   double getDistance() final;
   void draw() final;    
   double  x_coord_;
   double  y_coord_;
   sf::CircleShape circle;
};

class BasePoint:public Point {
   public:
   BasePoint(double x_pos, double y_pos):Point(x_pos, y_pos) {}
};

class Line;

class Circal;

class PointByTwoPoints:public Point {
    public:
  PointByTwoPoints(Point* pnt1, Point* pnt2, double ratio):parent_shape_first(pnt1),parent_shape_second(pnt2)  {
    circle.setRadius(5.f);
    circle.move((pnt1->x_coord_ + pnt2->x_coord_)/2, (pnt1->y_coord_ + pnt2->y_coord_)/ratio);
  }  
   Shape* parent_shape_first;
   Shape* parent_shape_second;
};

class PointByTwoLines:public Point {

};

namespace global {
    extern sf::RenderWindow window;
}
