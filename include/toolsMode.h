#pragma once
#include <SFML/Graphics.hpp>

#include "Scene.h"

struct MoveBasePoint {
  MoveBasePoint() = default;
  static void active(Scene& cur_scene);
  static bool is_moving;
  static Shape* last_object;
};

struct CreateMiddlePoint {
  CreateMiddlePoint() = default;
  static void active(Scene& cur_scene);
};

struct NoMode {
  static void active(Scene&) {}
};

struct CreateLine {
   CreateLine() = default;
   static void active(Scene& cur_scene);
};

struct FindLineIntersection {
  FindLineIntersection() = default;
  static void active(Scene& cur_scene);
};

struct RollBack {
  RollBack() = default;
  static void active(Scene& cur_scene);
  static bool flag;
};

struct MoveName {
  MoveName() = default;
  static void active(Scene& cur_scene);
  static bool is_moving;
  static Shape* last_object;
};

struct ShowBarycentricCoordinate {
  ShowBarycentricCoordinate() = default;
  static void active(Scene& cur_scene);
};

struct ProveIntersect {
  ProveIntersect() = default;
  static void active(Scene& cur_scene);
  //static int counter;
};

struct ProveCollinearity {
  ProveCollinearity() = default;
  static void active(Scene& cur_scene);
};

struct DrawIncenter {
  DrawIncenter() = default;
  static void active(Scene& cur_scene);
  static bool single;
};

struct drawOrthocenter {
  drawOrthocenter() = default;
  static void active(Scene& cur_scene);
  static bool single;
};

struct ProvePendicular {
  ProvePendicular() = default;
  static void active(Scene& cur_scene);
};

struct FindDistance {
  FindDistance() = default;
  static void active(Scene& cur_scene);
};
