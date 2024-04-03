#include "ButtonManager.h"


ButtonManager::ButtonManager() {
  all_textures.resize(8);
  all_textures[0].loadFromFile("Textures/Move.png");
  all_textures[2].loadFromFile("Textures/Midpoint.png");
  all_textures[3].loadFromFile("Textures/Line.png");
  all_textures[4].loadFromFile("Textures/Delete.png"); 
  all_textures[5].loadFromFile("Textures/PresetOFF.png");
  all_textures[6].loadFromFile("Textures/Concurrency.png");
  all_textures[7].loadFromFile("Textures/Collinearity.png");
  all_buttons.push_back(new Button(10, 120, MoveBasePoint::active, all_textures[0]));
  all_buttons.push_back(new Button(10, 20, NoMode::active, all_textures[5]));
  all_buttons.push_back(new Button(10, 220, CreateMiddlePoint::active, all_textures[2]));
  all_buttons.push_back(new Button(10, 320, CreateLine::active, all_textures[3]));
  all_buttons.push_back(new Button(10, 420, FindLineIntersection::active, all_textures[0]));
  all_buttons.push_back(new Button(10, 520, RollBack::active, all_textures[4]));
  all_buttons.push_back(new Button(10, 620, MoveName::active, all_textures[0]));
  all_buttons.push_back(new Button(10, 720, ShowBarycentricCoordinate::active, all_textures[0]));
  all_buttons.push_back(new Button(1310, 20, ProveIntersect::active, all_textures[6]));
  all_buttons.push_back(new Button(1310, 120, ProveCollinearity::active, all_textures[7]));
  all_buttons.push_back(new Button(1310, 220, DrawIncenter::active, all_textures[0]));
  all_buttons.push_back(new Button(1310, 321, drawOrthocenter::active, all_textures[0]));
}

void ButtonManager::draw() {
  for (int i = 0; i < all_buttons.size(); ++i) {
    all_buttons[i]->draw();
  }
}

Button* ButtonManager::ChooseButton(sf::Vector2f button_click) {
  for (auto button : all_buttons) {
    if (button->Contain(button_click)) {
      return button;
    }
  }
  return nullptr;
}


void ModeManager::ChangeMode(Button* button) {
  if (button != nullptr) {
    std::cout << "Change Mode" << std::endl;
    current_mode = button->corresponding_function;
  }
}

void ModeManager::CurrentMode(Scene& scene) {
  current_mode(scene);
}
