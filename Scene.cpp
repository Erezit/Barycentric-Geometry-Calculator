

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
        if(Scene::objects[i]->getDistance() < min_distance) {
           cur_select_object = Scene::objects[i];
           min_distance = Scene::objects[i]->getDistance();
        }
    }
    return cur_select_object;
}
