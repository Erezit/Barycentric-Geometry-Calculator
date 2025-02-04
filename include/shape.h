#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "NameBox.h"
#include "BarycentricCoordinates.h"

class Object {
public:
  virtual void draw() = 0;
};

class Invisibility {
  bool isHidden = false;
  public:
  bool getIsHidden();
  void changeHidden();
};

class OutputSolution {
 public:
  bool isBelongToProof = true;
  virtual void printProof(std::ofstream& out) = 0;
};

struct Equation {
  double A;
  double B;
  double C;
  void simplify() {
    double sum = A + B + C;
    A = A / sum;
    B = B / sum;
    C = C / sum;
  }
};

class RenamebleShape {
  std::string name_;
 public:
  void setName(std::string name);
  std::string getName(); 
};

class Shape : public Object, public Invisibility, public OutputSolution {
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
  virtual std::string getInfoName() = 0;
  virtual ~Shape() = default;
};

class Point : public Shape, public RenamebleShape {   
public:
  Point();                             
  Point(double x_pos, double y_pos);
  double getDistance() final;
  sf::Vector2f getPosition();
  void draw() override = 0;
  double x_coord_;
  double y_coord_;
  sf::CircleShape circle;
  NameBox name;
  std::string getInfoName() final;
};

class BasePoint : public Point {
public:
  void draw() override;
  BasePoint(double x_pos, double y_pos);
  void printProof(std::ofstream& out) override;
};

class FreePoint : public BasePoint {
public:
  void draw() final;
  FreePoint(double x_pos, double y_pos);
  void printProof(std::ofstream& out) override;
};


class MiddlePoint : public Point {
private:
  Point* a_point_ = nullptr;
  Point* b_point_ = nullptr;
public:
  void draw() final;
  void make_actual() final;
  void printProof(std::ofstream& out) override;
  MiddlePoint(Point* a_point, Point* b_point);
};

class Line : public Shape {
protected:
  Point* a_point_ = nullptr;
  Point* b_point_ = nullptr;
  sf::Vertex line[2];
public:
  void make_actual() override;
  double getDistance() override;
  void draw() override;
  Line() = default;
  Line(Point* a_point, Point* b_point);
  virtual std::vector<double> getCoefficients();
  virtual Point* getPointA();
  virtual Point* getPointB();
  std::string getInfoName() override;
  void printProof(std::ofstream& out) override;
};

class PointByTwoLines : public Point {
private:
  Line* a_line_ = nullptr;
  Line* b_line_ = nullptr;
public:
  PointByTwoLines(Line* a_line, Line* b_line);
  void draw() final;
  void make_actual() final;
  void printProof(std::ofstream& out) override;
};

class Incenter : public Point {
  public:
  void draw() final;
  Incenter(Point* a_point, Point* b_point,Point* c_point);
  Point* a_point_ = nullptr;
  Point* b_point_ = nullptr;
  Point* c_point_ = nullptr;
  void make_actual() final;
  void printProof(std::ofstream& out) override;
};

class Orthocenter : public Point {
  public:
  void draw() final;
  Orthocenter(Point* a_point, Point* b_point,Point* c_point);
  Point* a_point_ = nullptr;
  Point* b_point_ = nullptr;
  Point* c_point_ = nullptr;
  void make_actual() final;
  void printProof(std::ofstream& out) override;
};

namespace global {
  extern sf::RenderWindow window;
  extern char next_name;
  extern bool is_problem_correct; 
  extern bool fake_click;
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
  void printProof(std::ofstream& out) override;
};

class Circle : public Shape {
   Point* a_point_ = nullptr;
   Point* b_point_ = nullptr;
   Point* c_point_ = nullptr;
   sf::CircleShape shape;
   public:
   double center_x_;
   double center_y_;
   double radius_;
   public:
   void make_actual() final;
   void draw() final;
   double getDistance() final;
   Circle(Point* a_point, Point* b_point,
          Point* c_point);
   void printProof(std::ofstream& out) override;
   std::string getInfoName() override;
};


class PointIntersectionByLineCircle : public Point {
    Circle* circle_ = nullptr;
    Line* line_ = nullptr;
    Point* point_ = nullptr;
    public:
    void make_actual() final;
    void draw() final;
   PointIntersectionByLineCircle(Circle* circle, Line* line, Point* point);
    void printProof(std::ofstream& out) override;
};

class PerpendicularLine : public Line {
  private:
   Point* base_point_ = nullptr;
   Line* base_line_ = nullptr;
  sf::Vertex line[2];
 public:
  void make_actual() final;
  PerpendicularLine(Line* line, Point* point);
  std::vector<double> getCoefficients() override;
  Point* getPointA() override;
  Point* getPointB() override;
  Point* getBasePoint();
  std::string getInfoName() override;
  void draw() final;
  double getDistance() final;
  void printProof(std::ofstream& out) override;

};

class ParallelLine : public Line {
  private:
    Point* base_point_ = nullptr;
    Line* base_line_ = nullptr;
    sf::Vertex line[2];
  public:
    void make_actual() final;
    ParallelLine(Line* line, Point* point);
     std::vector<double> getCoefficients() override;
     Point* getPointA() override;
    Point* getPointB() override;
    Point* getBasePoint();
    void draw() final;
    std::string getInfoName() override;
    double getDistance() final;
    void printProof(std::ofstream& out) override;

};


struct VectorDiff {
  Point* point_a_;
  Point* point_b_;
  GiNaC::ex A_diff;
  GiNaC::ex B_diff;
  GiNaC::ex C_diff;
  void simplify();
  VectorDiff(Point* point_a, Point* point_b);
  VectorDiff() = default;
  GiNaC::ex A();
  GiNaC::ex B();
  GiNaC::ex C();
  void setCoord(GiNaC::ex A_c, GiNaC::ex B_c, GiNaC::ex C_c);
};

struct RadicalAxis : public Line {
 private:   
  Circle* circle1_ = nullptr;
  Circle* circle2_ = nullptr;
 public:
  std::string getInfoName() override;
  void make_actual() final;
  RadicalAxis(Circle* circle1, Circle* circle2);
  std::vector<double> getCoefficients() override;  
  void draw() final;
  double getDistance() final;
  void printProof(std::ofstream& out) override;

};
