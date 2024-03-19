#pragma once

#include "Button.h"
#include "toolsMode.h"

class ButtonManager {
public:
  ButtonManager();
  void draw();
  Button* ChooseButton(sf::Vector2f button_click);

private:
  std::vector<Button*> all_buttons;
};

class ModeManager {
public:
  ModeManager() = default;
  void ChangeMode(Button* button);
  void CurrentMode(Scene& scene);
  std::function<void(Scene&)> current_mode = NoMode::active;
};
