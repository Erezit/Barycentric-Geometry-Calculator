#pragma once


#include "shape.h"
#include "Button.h"
#include <SFML/Graphics.hpp>

class Scene {
    public:
    Scene() {
      objects.push_back(new BasePoint(10,30));
      objects.push_back(new BasePoint(150,120));
      objects.push_back(new BasePoint(100,40));
      objects.push_back(new Button(30, 30));
    }
    void drawScene();

    Shape* selectObject();
      


    std::vector<Object*> objects;
    sf::Event event;

};
