#include "Scene.h"
#include <iostream>

Scene::Scene() {
  panel_draw.setFillColor(sf::Color{ 55, 55, 55, 255});
  panel_draw.setPosition(0, 0);
  panel_draw.setSize(sf::Vector2f(240, 900));

   
  panel_prove_tools.setFillColor(sf::Color{ 150, 0, 24, 255});
  panel_prove_tools.setPosition(1280, 0);
  panel_prove_tools.setSize(sf::Vector2f(140, 347));
  
  panel_help_tool.setFillColor(sf::Color{128, 128, 0, 255});
  panel_help_tool.setPosition(1280, 345);
  panel_help_tool.setSize(sf::Vector2f(140, 230));

  panel_value_tools.setFillColor(sf::Color{ 0, 86, 100, 255});
  panel_value_tools.setPosition(1280, 565);
  panel_value_tools.setSize(sf::Vector2f(140, 343));

  objects.push_back(new BasePoint(350,150));
  objects.push_back(new BasePoint(900,720));
  objects.push_back(new BasePoint(300,722));
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
  global::window.draw(panel_prove_tools);
  global::window.draw(panel_help_tool);
  global::window.draw(panel_value_tools);
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

