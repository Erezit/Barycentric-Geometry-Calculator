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
                sf::Vector2f mouse_click = global::window.mapPixelToCoords(sf::Mouse::getPosition(global::window));
                if (button_manager.ChooseButton(mouse_click)) {
                  button_manager.ChangeMode(button_manager.ChooseButton(mouse_click));
                  main_scene.selected_shapes.clear();
                }
            }
        }
        button_manager.draw();
        button_manager.CurrentMode(main_scene);
        main_scene.drawScene();
        global::window.display();
        global::window.clear();
        
    }

    return 0;
}
