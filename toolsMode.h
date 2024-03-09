#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"

struct MovePoint {
  MovePoint() {}
  void operator()(Scene& cur_scene) {
    sf::Event& cur_event = cur_scene.event;
    if (cur_event.type == sf::Event::MouseButtonReleased) {
      is_moving = false;
    }
    if (cur_event.type == sf::Event::MouseButtonPressed) {
      is_moving = true;
    }

    if (is_moving) {
     Shape* movable_object = cur_scene.selectObject();
     // Shape* movable_object = cur_scene.objects[0];
      if (Point* movable_point = dynamic_cast<Point *>(movable_object)) {
        movable_point->circle.setPosition(global::window.mapPixelToCoords(
            sf::Mouse::getPosition(global::window)));
        movable_point->x_coord_ = global::window.mapPixelToCoords(sf::Mouse::getPosition(global::window)).x;
        movable_point->y_coord_ = global::window.mapPixelToCoords(sf::Mouse::getPosition(global::window)).y;
      }
    }
  }

  bool is_moving = false;
};


