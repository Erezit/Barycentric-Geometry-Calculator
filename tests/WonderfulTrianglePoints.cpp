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
}

TEST(GeometricProblems, HalfWrittenCircle) {
  global::fake_click = true;
  global::is_problem_correct = false;
  Scene scene;
  Point* A = dynamic_cast<Point*>(scene.objects[0]);
  Point* B = dynamic_cast<Point*>(scene.objects[1]);
  Point* C = dynamic_cast<Point*>(scene.objects[2]);
  Point* I = new Incenter(A, B, C);
  Line* AI = new Line(A, I);
  Circle* W = new Circle(A, B, C);
  Line* AD = new PerpendicularLine(AI, A);
  Point* D = new PointIntersectionByLineCircle(W, AD, A);
  Line* BC = new Line(B, C);
  Line* AX = new ParallelLine(BC, A);
  Point* X = new PointIntersectionByLineCircle(W, AX, A);
  Line* IZ = new PerpendicularLine(BC, I);
  Point* Z = new PointByTwoLines(BC, IZ);
  Line* a = new Line(D, I);
  Line* b = new Line(X, Z);
  Point* T = new PointByTwoLines(a, b);
  Line* c = new PerpendicularLine(AI, I);
  Line* AB = new Line(A, B);
  Line* AC = new Line(A, C);
  Point* P1 = new PointByTwoLines(c, AB);
  Point* P2 = new PointByTwoLines(c, AC);
  Circle* w = new Circle(T, P1, P2);
  Line* l = new RadicalAxis(w, W);
  Point* TT = new PointByTwoLines(l, BC);
  Line* IT = new Line(I, T);
  Point* PP = new PointByTwoLines(IT, BC);
  Point* M = new MiddlePoint(PP, T);
  Line* interesting_line = new Line(M, TT);
  scene.selected_shapes.push_back(interesting_line);
  scene.selected_shapes.push_back(IT);
  ProvePendicular::active(scene);
  EXPECT_EQ(global::is_problem_correct, false);
  scene.drawScene();
  MoveBasePoint::active(scene);
  CreateMiddlePoint::active(scene);
   CreateLine::active(scene);
  FindLineIntersection::active(scene);
  RollBack::active(scene);
  ShowBarycentricCoordinate::active(scene);
  DrawIncenter::active(scene);
  drawOrthocenter::active(scene);
   FindDistance::active(scene);
}
