#pragma once


#include "shape.h"
#include <SFML/Graphics.hpp>

class Scene {
    public:
    Scene() {
      objects.push_back(new BasePoint(10,30));
      objects.push_back(new BasePoint(150,120));
      objects.push_back(new BasePoint(100,40));
    }
    void drawScene();
    Shape* selectObject(double x_pos, double y_pos);
    void movePoint();
    


    std::vector<Shape*> objects;
    sf::Event event;

};
