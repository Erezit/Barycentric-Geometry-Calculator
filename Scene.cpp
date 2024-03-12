

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
