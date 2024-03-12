#include "toolsMode.h"

void MovePoint::active(Scene& cur_scene) {
         sf::Event& cur_event = cur_scene.event;
         if (cur_event.type == sf::Event::MouseButtonReleased) {
         is_moving = false;
         last_object = nullptr;
        }
        if (cur_event.type == sf::Event::MouseButtonPressed || is_moving) {
          is_moving = true;
        }
    
    if (is_moving) {
         Shape* movable_object = cur_scene.selectObject();
         if(movable_object != nullptr && last_object == nullptr) {
           last_object = movable_object;
         }
         
         if(last_object != nullptr) {
           movable_object = last_object;
         }

    if (Point* movable_point = dynamic_cast<Point *>(movable_object)) {
      movable_point->circle.setPosition(global::window.mapPixelToCoords(
      sf::Mouse::getPosition(global::window)));
      movable_point->x_coord_ = global::window.mapPixelToCoords(sf::Mouse::getPosition(global::window)).x;
      movable_point->y_coord_ = global::window.mapPixelToCoords(sf::Mouse::getPosition(global::window)).y;
    }
  }
}

bool MovePoint::is_moving = false;

Shape* MovePoint::last_object = nullptr;
