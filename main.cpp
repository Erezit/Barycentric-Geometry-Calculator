#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "toolsMode.h"
int main()
{
    MovePoint tool_move_point;
    Scene main_scene;
    while (global::window.isOpen())
        
    {
        while (global::window.pollEvent(main_scene.event))
        {
            if (main_scene.event.type == sf::Event::Closed) {
                global::window.close();
            }
            if(main_scene.event.type == sf::Event::MouseButtonPressed || tool_move_point.is_moving) {
                tool_move_point(main_scene);
            }
        }
        main_scene.drawScene();
        global::window.display();
        global::window.clear();
        
    }

    return 0;
}
