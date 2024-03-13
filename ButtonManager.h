#pragma once

#include "Button.h"
#include "ModeManager.h"

class ButtonManager {
public:
  ButtonManager() {
    all_buttons.push_back(new Button(20, 20, MoveBasePoint::active));
    all_buttons.push_back(new Button(20, 70, NoMode::active));
    all_buttons.push_back(new Button(20, 120, CreateMiddlePoint::active));
  }

  void draw();

  void ChangeMode(Button* button);

  Button* ChooseButton(sf::Vector2f button_click);

  void CurrentMode(Scene& scene) {
    current_mode(scene);
  }

  std::function<void(Scene&)> current_mode = NoMode::active;


private:
  std::vector<Button*> all_buttons;
};
