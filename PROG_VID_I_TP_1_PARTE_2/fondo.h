#include <SFML/Graphics.hpp>

class Fondo {
public:
    // Constructor que inicializa el fondo con una textura
    Fondo(const sf::Texture& texture);

    // Dibuja el fondo en la ventana proporcionada
    void draw(sf::RenderWindow& window);

private:
    sf::Sprite sprite; // Sprite que representa el fondo
};