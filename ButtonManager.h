#pragma once

#include "ModeManager.h"
#include "Button.h"

class ButtonManager {
    public:
    ButtonManager() {
      all_buttons.push_back(new Button(20,20, MovePoint::active));
      all_buttons.push_back(new Button(20,70, NoMode::active));
    }
    public:
    void draw();
    void ChangeMode(Button* button);
    Button* ChoseButton(sf::Vector2f button_click);
    public: 
    ModeManager mode_manager;
    private:
    std::vector<Button*> all_buttons;
};
