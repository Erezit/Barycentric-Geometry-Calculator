#include "ButtonManager.h"


ButtonManager::ButtonManager() {
  all_textures.resize(13);
  all_textures[0].loadFromFile("Textures/Move.png");
  all_textures[2].loadFromFile("Textures/Midpoint.png");
  all_textures[3].loadFromFile("Textures/Line.png");
  all_textures[4].loadFromFile("Textures/Delete.png"); 
  all_textures[5].loadFromFile("Textures/PresetOFF.png");
  all_textures[6].loadFromFile("Textures/Concurrency.png");
  all_textures[7].loadFromFile("Textures/Collinearity.png");
  all_textures[8].loadFromFile("Textures/Orthocenter.png");
  all_textures[9].loadFromFile("Textures/Incenter.png");
  all_textures[10].loadFromFile("Textures/Intersection.png");
  all_textures[11].loadFromFile("Textures/ProveOrthogonality.png");
  all_textures[12].loadFromFile("Textures/Incenter.png"); 
  all_buttons.push_back(new Button(10, 130, MoveBasePoint::active, all_textures[0]));
  all_buttons.push_back(new Button(10, 20, NoMode::active, all_textures[5]));
  all_buttons.push_back(new Button(10, 240, CreateMiddlePoint::active, all_textures[2]));
  all_buttons.push_back(new Button(10, 350, CreateLine::active, all_textures[3]));
  all_buttons.push_back(new Button(10, 460, FindLineIntersection::active, all_textures[10]));
  all_buttons.push_back(new Button(10, 570, RollBack::active, all_textures[4]));
  all_buttons.push_back(new Button(10, 680, MoveName::active, all_textures[0]));
  all_buttons.push_back(new Button(10, 790, ShowBarycentricCoordinate::active, all_textures[0]));
  all_buttons.push_back(new Button(130, 20, DrawIncenter::active, all_textures[9]));
  all_buttons.push_back(new Button(130, 130, drawOrthocenter::active, all_textures[8]));
  all_buttons.push_back(new Button(130, 240, FindDistance::active, all_textures[0]));
  all_buttons.push_back(new Button(130, 350, FindIsogonal::active, all_textures[0]));
  all_buttons.push_back(new Button(130, 460, CreateCircleByPoints::active, all_textures[0]));

  all_buttons.push_back(new Button(1290, 20, ProveIntersect::active, all_textures[6]));
  all_buttons.push_back(new Button(1290, 130, ProveCollinearity::active, all_textures[7]));
  all_buttons.push_back(new Button(1290, 240, ProvePendicular::active, all_textures[11]));
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
