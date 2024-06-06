#include <SFML/Graphics.hpp>

class Fondo {
public:
    Fondo(const sf::Texture& texture);

    void draw(sf::RenderWindow& window);

private:
    sf::Sprite sprite;
};