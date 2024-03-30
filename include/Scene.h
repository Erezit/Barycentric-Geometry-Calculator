#pragma once

#include "shape.h"
#include <SFML/Graphics.hpp>

class Scene {
    public:
    Scene();
    void drawScene();
    Shape* selectObject();
    std::vector<Shape*> selected_shapes;
    void TryGetObject();
    bool Checker(int point_number = 0, int line_number = 0, int circle_number = 0);

    std::vector<Object*> objects;
    sf::Event event;

};
