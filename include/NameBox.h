#include <SFML/Graphics.hpp>

class NameBox {
    public:
      NameBox() = default;
      void setName(char sbl);
      void setPosition(double, double);
      sf::Text getName();
    private:
      sf::Text name;
      sf::Font font;
      sf::Vector2f delta = sf::Vector2f(10, -10);
      double x_coord_;
      double y_coord_;
};

