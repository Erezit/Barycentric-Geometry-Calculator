#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "toolsMode.h"
#include "ButtonManager.h"

int main()
{
    Scene main_scene;
    ButtonManager button_manager;
    ModeManager mode_manager;
    global::window.setFramerateLimit(60);
    while (global::window.isOpen())
    {
        while (global::window.pollEvent(main_scene.event))
        {
            if (main_scene.event.type == sf::Event::Closed) {
                global::window.close();
            }
            if(main_scene.event.type ==  sf::Event::MouseButtonReleased) {
                sf::Vector2f mouse_click = global::window.mapPixelToCoords(sf::Mouse::getPosition(global::window));
                if (button_manager.ChooseButton(mouse_click)) {
                   //  std::cout << main_scene.selected_shapes.size()  << std::endl;
                  for(auto shape : main_scene.selected_shapes) {
                    shape -> choosenFinal();  
                  }
                  main_scene.selected_shapes.clear();
                  mode_manager.ChangeMode(button_manager.ChooseButton(mouse_click));
                  main_scene.selected_shapes.clear();
                }
            }
        }
        mode_manager.CurrentMode(main_scene);
        main_scene.drawScene();
        button_manager.draw();
        global::window.display();
        global::window.clear(sf::Color(255,255,255));
        
    }

    return 0;
}
