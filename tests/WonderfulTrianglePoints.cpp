#include <gtest/gtest.h>
#include "shape.h"
#include "toolsMode.h"
#include "Scene.h"

TEST(WonderfulTrianglePoints, Barycenter) {
  global::fake_click = true;
  global::is_problem_correct = false;
  Scene scene;  
  Point* A = dynamic_cast<Point*>(scene.objects[0]);
  Point* B = dynamic_cast<Point*>(scene.objects[1]);
  Point* C = dynamic_cast<Point*>(scene.objects[2]);
  Point* middla_point_ab = new MiddlePoint(A, B);
  Point* middla_point_bc = new MiddlePoint(B, C);
  Point* middla_point_ca = new MiddlePoint(C, A);
  Line* mediana_a = new Line(middla_point_bc, A);
  Line* mediana_b = new Line(middla_point_ca, B);
  Line* mediana_c = new Line(middla_point_ab, C);
  scene.selected_shapes.push_back(mediana_a);
  scene.selected_shapes.push_back(mediana_b);
  scene.selected_shapes.push_back(mediana_c);
  ProveIntersect::active(scene);
  EXPECT_EQ(global::is_problem_correct, true);
  delete middla_point_ab;
  delete middla_point_bc;
  delete middla_point_ca;
  delete mediana_a;
  delete mediana_b;
  delete mediana_c;
}

TEST(WonderfulTrianglePoints, Orthocenter) {
  global::fake_click = true;
   global::is_problem_correct = false;
  Scene scene;
  Point* A = dynamic_cast<Point*>(scene.objects[0]);
  Point* B = dynamic_cast<Point*>(scene.objects[1]);
  Point* C = dynamic_cast<Point*>(scene.objects[2]);
  
  Line* BC = new Line(B, C);
  Line* AC = new Line(A, C);
  Line* AB = new Line(A, B);

  Line* perpendicular_a = new PerpendicularLine(BC, A);
  Line* perpendicular_b = new PerpendicularLine(AC, B);
  Line* perpendicular_c = new PerpendicularLine(AB, C);
  
  scene.selected_shapes.push_back(perpendicular_a);
  scene.selected_shapes.push_back(perpendicular_b);
  scene.selected_shapes.push_back(perpendicular_c);
  ProveIntersect::active(scene);
  EXPECT_EQ(global::is_problem_correct, true);
}

TEST(GeometricProblems, Classicc) {
  global::fake_click = true;
  global::is_problem_correct = false;
  Scene scene;
  Point* A = dynamic_cast<Point*>(scene.objects[0]);
  Point* B = dynamic_cast<Point*>(scene.objects[1]);
  Point* C = dynamic_cast<Point*>(scene.objects[2]);
  Line* AB = new Line(A, B);
  Line* AC = new Line(A, C);
  Point* H = new Orthocenter(A, B, C);
  Point* O = new IsogonalPoint(A, B, C, H);
  Point* middle_ab = new MiddlePoint(A, B);
  Point* middle_ac = new MiddlePoint(A, C);
  Line* middle_perpendicular_ab = new Line(middle_ab, O);
  Line* middle_perpendicular_ac = new Line(middle_ac, O);
  Point* X = new PointByTwoLines(middle_perpendicular_ab, AC);
  Point* Y = new PointByTwoLines(middle_perpendicular_ac, AB);
  Line* BX = new Line(B, X);
  Line* CY = new Line(C, Y);
  Point* Z = new PointByTwoLines(BX, CY);
  scene.selected_shapes.push_back(H);
  scene.selected_shapes.push_back(O);
  scene.selected_shapes.push_back(Z);
  ProveCollinearity::active(scene);
  EXPECT_EQ(global::is_problem_correct, true);
  EXPECT_EQ(1,1);
}

