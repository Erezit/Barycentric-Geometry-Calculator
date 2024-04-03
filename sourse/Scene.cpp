#include "Scene.h"
#include <iostream>

Scene::Scene() {
  panel_draw.setFillColor(sf::Color{ 55, 55, 55, 255});
  panel_draw.setPosition(0, 0);
  panel_draw.setSize(sf::Vector2f(200, 900));

  panel_prove.setFillColor(sf::Color{ 55, 55, 55, 255});
  panel_prove.setPosition(1300, 0);
  panel_prove.setSize(sf::Vector2f(100, 900));

  objects.push_back(new BasePoint(350,150));
  objects.push_back(new BasePoint(900,720));
  objects.push_back(new BasePoint(300,720));
  objects[0] -> setCoordinates(1,0,0);
  objects[1] -> setCoordinates(0,1,0);
  objects[2] -> setCoordinates(0,0,1);
  objects.push_back(new Line(dynamic_cast<Point*>(objects[0]),dynamic_cast<Point*>(objects[1])));
  objects.push_back(new Line(dynamic_cast<Point*>(objects[1]),dynamic_cast<Point*>(objects[2])));
  objects.push_back(new Line(dynamic_cast<Point*>(objects[2]),dynamic_cast<Point*>(objects[0])));
}
void Scene::drawScene() {
 
  for(int i = 0; i < objects.size(); ++i) {
    objects[i]->draw();
  }
  global::window.draw(panel_draw);
  global::window.draw(panel_prove);
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

