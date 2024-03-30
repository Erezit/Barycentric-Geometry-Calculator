#include "Scene.h"
#include <iostream>

Scene::Scene() {
  objects.push_back(new BasePoint(80,150));
  objects.push_back(new BasePoint(300,170));
  objects.push_back(new BasePoint(150,90));
  objects.push_back(new Line(dynamic_cast<Point*>(objects[0]),dynamic_cast<Point*>(objects[1])));
  objects.push_back(new Line(dynamic_cast<Point*>(objects[1]),dynamic_cast<Point*>(objects[2])));
  objects.push_back(new Line(dynamic_cast<Point*>(objects[2]),dynamic_cast<Point*>(objects[0])));
}
void Scene::drawScene() {
  for(int i = 0; i < objects.size(); ++i) {
    objects[i]->draw();
  }
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

