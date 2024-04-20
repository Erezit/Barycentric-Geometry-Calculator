#pragma once

#include "shape.h"
#include <SFML/Graphics.hpp>

class Scene {
    public:
    Scene();
    void drawScene();
     
    std::vector<Shape*> selected_shapes;
    sf::RectangleShape panel_draw;
    sf::RectangleShape panel_prove;

    template <typename T = Shape>
    Shape* selectObject() {
      Shape* cur_select_object = nullptr;
      double min_distance = 1000000;
      for(int i = 0; i < Scene::objects.size(); ++i) {
      Shape* shape_form = dynamic_cast<T*>(Scene::objects[i]);
      if (shape_form == nullptr) {
        continue;
      }
      if(shape_form->getDistance() < min_distance && dynamic_cast<T*>(shape_form)) {
        cur_select_object = shape_form;
        min_distance = shape_form->getDistance();
      }
    }
    if(min_distance!=1000000 &&  cur_select_object->getDistance() > 30) {
        return nullptr;
    }
    return cur_select_object;
}


    template <typename T = Shape>
    void TryGetObject() {
      Shape* new_shape = selectObject<T>();
      if (event.type == sf::Event::MouseButtonPressed && dynamic_cast<T*>(new_shape)!= nullptr && (new_shape != nullptr)) {
        for (auto shape : selected_shapes) {
          if (shape == new_shape) {
            return;
          }
        }
        //std::cout << "I've got an object!!" << std::endl;
        selected_shapes.push_back(new_shape);
        //std::cout << "Totally i've got " << selected_shapes.size() << std::endl;
      }
    }


    bool Checker(int point_number = 0, int line_number = 0, int circle_number = 0);

    std::vector<Shape*> objects;
    sf::Event event;

};
