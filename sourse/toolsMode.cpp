#include "toolsMode.h"
float max(float num1, float num2) {
    if(num1 > num2){
      return num1;
    }
  return num2;
}

void MoveBasePoint::active(Scene& cur_scene) {
  sf::Event& cur_event = cur_scene.event;
  if (cur_event.type == sf::Event::MouseButtonReleased) {
    is_moving = false;
    last_object = nullptr;
  }
  if (cur_event.type == sf::Event::MouseButtonPressed && cur_event.type != sf::Event::MouseButtonReleased) {
    is_moving = true;
  }

  if (is_moving) {
    Shape* movable_object = cur_scene.selectObject<Point>();
    if (movable_object != nullptr && last_object == nullptr) {
      last_object = movable_object;
    }

    if (last_object != nullptr) {
      movable_object = last_object;
    }

    if (Point* movable_point = dynamic_cast<BasePoint*>(movable_object)) {
      movable_point->circle.setPosition(global::window.mapPixelToCoords(
          sf::Mouse::getPosition(global::window)));
      movable_point->x_coord_ = max(110,
          global::window
              .mapPixelToCoords(sf::Mouse::getPosition(global::window))
              .x);
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
  current_scene.TryGetObject<Point>();
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

void CreateLine::active(Scene& current_scene) {
  current_scene.TryGetObject<Point>();
  if (current_scene.event.type == sf::Event::MouseButtonReleased && current_scene.Checker(2)) {
    std::cout << "Wow, I've got two pretty points to create line!" << std::endl;
    Point* first_point = dynamic_cast<Point*>(current_scene.selected_shapes[0]);
    Point* second_point = dynamic_cast<Point*>(current_scene.selected_shapes[1]);
    Line* line =  new Line(first_point, second_point);
    current_scene.objects.push_back(line);
    current_scene.selected_shapes.clear();
  }
}

void FindLineIntersection::active(Scene& current_scene) {
  current_scene.TryGetObject<Line>();
  if (current_scene.event.type == sf::Event::MouseButtonReleased && current_scene.Checker(0, 2)) {
    std::cout << "Wow, I've got two pretty line to create point!" << std::endl;
    Line* first_line = dynamic_cast<Line*>(current_scene.selected_shapes[0]);
    Line* second_line = dynamic_cast<Line*>(current_scene.selected_shapes[1]);
    PointByTwoLines* point = new PointByTwoLines(first_line, second_line);
    current_scene.objects.push_back(point);
    current_scene.selected_shapes.clear();
  }
}

bool RollBack::flag = true;

void RollBack::active(Scene& current_scene) {
  sf::Event& cur_event = current_scene.event;
  if (cur_event.type == sf::Event::MouseButtonPressed && !flag) {
    flag = true;
  }
  if (cur_event.type == sf::Event::MouseButtonReleased && flag) {
    if(current_scene.objects.size() > 6) {
      current_scene.objects.pop_back();
    }
    flag = false;
  }
}

bool MoveName::is_moving = false;
Shape* MoveName::last_object = nullptr;

void MoveName::active(Scene& current_scene) {
  sf::Event& cur_event = current_scene.event;
  if (cur_event.type == sf::Event::MouseButtonReleased) {
    is_moving = false;
    last_object = nullptr;
  }
  if (cur_event.type == sf::Event::MouseButtonPressed && cur_event.type != sf::Event::MouseButtonReleased) {
    is_moving = true;
  }
  if(is_moving) {
    Shape* movable_object = current_scene.selectObject<Point>();
    if (movable_object != nullptr && last_object == nullptr) {
      last_object = movable_object;
    }

    if (last_object != nullptr) {
      movable_object = last_object;
    }

    if (Point* movable_point = dynamic_cast<Point*>(movable_object)) {
      sf::Vector2f point_position = sf::Vector2f(movable_point->x_coord_, movable_point->y_coord_); 
      sf::Vector2f mouse_position = global::window.mapPixelToCoords(sf::Mouse::getPosition(global::window));
      sf::Vector2f new_delta = mouse_position - point_position;
      double size = sqrt(new_delta.x * new_delta.x + new_delta.y * new_delta.y);
      new_delta.x = new_delta.x / size * 15;
      new_delta.y = new_delta.y / size * 15;
      movable_point->name.setDelta(new_delta);
    }
  }
}


