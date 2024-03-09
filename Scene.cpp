

#include "Scene.h"
#include <iostream>

void Scene::drawScene() {
  for(int i = 0; i < objects.size(); ++i) {
    objects[i]->draw();
  }
}

void Scene::movePoint() {
  Shape* moveble_object;
  std::cout << "Try to move" << std::endl;
    std::cout << "MAGIC" << std::endl;
    if(Scene::event.type == sf::Event::MouseButtonPressed) {
      sf::Vector2i position = sf::Mouse::getPosition();
      //moveble_object = Scene::selectObject(position.x, position.y);
      std::cout << "Find Object"<< std::endl;
      moveble_object = Scene::objects[0];
      if(moveble_object != nullptr) {
        std::cout << "Start move" << std::endl;
        Point* moveble_point = dynamic_cast<Point*>(moveble_object);
        while(Scene::event.type != sf::Event::MouseButtonReleased) {
          while(global::window.pollEvent(Scene::event)) {
          sf::Vector2i current_pos = sf::Mouse::getPosition(global::window);
          moveble_point->circle.move(current_pos.x - moveble_point->x_coord_,current_pos.y - moveble_point->y_coord_);
          moveble_point->x_coord_ = current_pos.x;
          moveble_point->y_coord_ = current_pos.y;
          Scene::drawScene();
          global::window.display();
          global::window.clear();
          }
        }
      }
    }
}
