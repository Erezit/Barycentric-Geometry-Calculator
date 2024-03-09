#include <iostream>
#include <SFML/Graphics.hpp>
#include "Scene.h"

int main()
{
    
    Scene main_scene;
    

    while (global::window.isOpen())
        
    {
        while (global::window.pollEvent(main_scene.event))
        {
            if (main_scene.event.type == sf::Event::Closed)
                global::window.close();
            if(main_scene.event.type == sf::Event::MouseButtonPressed) {
                 sf::Vector2i position = sf::Mouse::getPosition(global::window);
                 std::cout << position.x << " " << position.y << std::endl;
                 main_scene.movePoint();
            }
        }



        main_scene.drawScene();
        global::window.display();
        global::window.clear();
        
    }

    return 0;
}
