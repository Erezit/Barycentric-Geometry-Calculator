#include <iostream>
#include "shape.h"
#include <SFML/Graphics.hpp>

int main()
{
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (global::window.isOpen())
        
    {
        sf::Event event;
        while (global::window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                global::window.close();
        }

        global::window.clear();
        global::window.draw(shape);
        global::window.display();
    }

    return 0;
}
