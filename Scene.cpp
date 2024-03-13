

#include "Scene.h"
#include <iostream>

void Scene::drawScene() {
  for(int i = 0; i < objects.size(); ++i) {
    objects[i]->draw();
  }
}

Shape* Scene::selectObject() {
    Shape* cur_select_object = nullptr;
    double min_distance = 1000000;
    for(int i = 0; i < Scene::objects.size(); ++i) {
      Shape* shape_form = dynamic_cast<Shape*>(Scene::objects[i]);
      if (shape_form == nullptr) {
        continue;
      }
      if(shape_form->getDistance() < min_distance) {
        cur_select_object = shape_form;
        min_distance = shape_form->getDistance();
      }
    }
    if(cur_select_object->getDistance() > 30) {
        return nullptr;
    }
    return cur_select_object;
}

bool Scene::Checker(int point_number, int line_number, int circle_number) {
  for (size_t i = 0; i < selected_shapes.size(); ++i) {
    if (Point* point = dynamic_cast<Point*>(selected_shapes[i])) {
      point_number--;
      if (point_number < 0) {
        return false;
      }
    } else if (Line* line = dynamic_cast<Line*>(selected_shapes[i])) {
      line_number--;
      if (line_number < 0) {
        return false;
      }
    } else {
      circle_number--;
      if (circle_number < 0) {
        return false;
      }
    }
  }
  return (point_number == 0 && line_number == 0 && circle_number == 0);
}

void Scene::TryGetObject() {
  Shape* new_shape = selectObject();
  if (event.type == sf::Event::MouseButtonPressed && (new_shape != nullptr)) {
    for (auto shape : selected_shapes) {
      if (shape == new_shape) {
        return;
      }
    }
    std::cout << "I've got an object!!" << std::endl;
    selected_shapes.push_back(new_shape);
    std::cout << "Totally i've got " << selected_shapes.size() << std::endl;
  }
}