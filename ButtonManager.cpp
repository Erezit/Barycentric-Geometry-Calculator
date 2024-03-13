#include "ButtonManager.h"

void ButtonManager::draw() {
  for (int i = 0; i < all_buttons.size(); ++i) {
    all_buttons[i]->draw();
  }
}

void ButtonManager::ChangeMode(Button* button) {
  if (button != nullptr) {
    std::cout << "Change Mode" << std::endl;
    current_mode = button->corresponding_function;
  }
}



Button* ButtonManager::ChooseButton(sf::Vector2f button_click) {
  for (int i = 0; i < all_buttons.size(); ++i) {
    if (all_buttons[i]->Contain(button_click)) {
      return all_buttons[i];
    }
  }
  return nullptr;
}
