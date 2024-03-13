#include "toolsMode.h"

void MoveBasePoint::active(Scene& cur_scene) {
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
    if (movable_object != nullptr && last_object == nullptr) {
      last_object = movable_object;
    }

    if (last_object != nullptr) {
      movable_object = last_object;
    }

    if (Point* movable_point = dynamic_cast<BasePoint*>(movable_object)) {
      movable_point->circle.setPosition(global::window.mapPixelToCoords(
          sf::Mouse::getPosition(global::window)));
      movable_point->x_coord_ =
          global::window
              .mapPixelToCoords(sf::Mouse::getPosition(global::window))
              .x;
      movable_point->y_coord_ =
          global::window
              .mapPixelToCoords(sf::Mouse::getPosition(global::window))
              .y;
    }
  }
}

bool MoveBasePoint::is_moving = false;

Shape* MoveBasePoint::last_object = nullptr;

void CreateMiddlePoint::active(Scene& current_scene) {
  // std::cout << current_scene.selected_shapes.size() << std::endl;
  current_scene.TryGetObject();
  if (current_scene.event.type == sf::Event::MouseButtonReleased && current_scene.Checker(2)) {
    std::cout << "Wow, I've got two pretty points to create midpoint!" << std::endl;
    Point* first_point = dynamic_cast<Point*>(current_scene.selected_shapes[0]);
    Point* second_point = dynamic_cast<Point*>(current_scene.selected_shapes[1]);
    MiddlePoint* middlePoint = new MiddlePoint(first_point, second_point);
    current_scene.objects.push_back(middlePoint);
    std::cout << "Now there are " << current_scene.objects.size() << " points" << std::endl;
    current_scene.selected_shapes.clear();
  }
}