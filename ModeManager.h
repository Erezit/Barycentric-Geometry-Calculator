#pragma once
#include <functional>
#include "Scene.h"
#include "toolsMode.h"

class ModeManager{
    public:

    ModeManager() {}

    void CurrentMode(Scene& scene) {
      current_mode(scene);
    }

    std::function<void(Scene&)> current_mode = NoMode::active;
};


