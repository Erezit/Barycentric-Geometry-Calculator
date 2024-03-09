#include <iostream>
#include "shape.h"
#include <SFML/Graphics.hpp>

int main()
{
    std::vector<Shape*> objects;
    objects.push_back(new BasePoint(10,30));
    objects.push_back(new BasePoint(150,120));
    objects.push_back(new BasePoint(100,40));

    while (global::window.isOpen())
        
    {
        sf::Event event;
        while (global::window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                global::window.close();
        }


        for(int i = 0; i < objects.size(); ++i) {
            objects[i]->draw();
        }
        global::window.display();
        global::window.clear();
    }

    return 0;
}
