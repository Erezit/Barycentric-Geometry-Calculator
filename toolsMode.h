#pragma once
#include <SFML/Graphics.hpp>

#include "Scene.h"

struct MovePoint {
  MovePoint() {}
  static void active(Scene& cur_scene);
  static bool is_moving;
  static Shape* last_object;
};

struct NoMode {
  static void active(Scene&) {}
};
