#include "shape.h"
#include <SFML/Graphics.hpp>

namespace global {
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
}

class Shape {
  public:
  virtual void draw() = 0;
};

class Point: public Shape {
    public:

   
    double x_coord_;
    double y_coord_;

};

class Line: public Shape {
   private:

};


class PointByTwoPoints:public Point {
    PointByTwoPoints(const Point* pnt1, const Point* pnt2, double ratio) {
         circle.setRadius(10.f);
         circle.move((pnt1->x_coord_ + pnt2->x_coord_)/2, (pnt1->y_coord_ + pnt2->y_coord_)/2);
    }

    void draw() override {
      global::window.draw(circle);
    }

    private:
    Shape* parent_shape_first;
    Shape* parent_shape_second;
    sf::CircleShape circle;
};

class PointByTwoLines:public Point {
    private:
    Shape* parent_shape_first;
    Shape* parent_shape_second;
};
