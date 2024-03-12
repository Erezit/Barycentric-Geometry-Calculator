#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "toolsMode.h"
#include "ButtonManager.h"

int main()
{

    Scene main_scene;
    ButtonManager button_manager;
    while (global::window.isOpen())
    {
        while (global::window.pollEvent(main_scene.event))
        {
            if (main_scene.event.type == sf::Event::Closed) {
                global::window.close();
            }
            if(main_scene.event.type ==  sf::Event::MouseButtonReleased) {
                sf::Vector2f button_click = global::window.mapPixelToCoords(sf::Mouse::getPosition(global::window));
                button_manager.ChangeMode(button_manager.ChoseButton(button_click)); 
            }
        }
        button_manager.draw();
        button_manager.mode_manager.CurrentMode(main_scene);
        main_scene.drawScene();
        global::window.display();
        global::window.clear();
        
    }

    return 0;
}
