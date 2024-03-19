#include "ButtonManager.h"


ButtonManager::ButtonManager() {
  all_buttons.push_back(new Button(20, 20, MoveBasePoint::active));
  all_buttons.push_back(new Button(20, 70, NoMode::active));
  all_buttons.push_back(new Button(20, 120, CreateMiddlePoint::active));
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