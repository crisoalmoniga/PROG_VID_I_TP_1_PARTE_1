#include "Fondo.h"

// Constructor que inicializa el fondo con una textura
Fondo::Fondo(const sf::Texture& texture) : sprite(texture) {}

// Dibuja el fondo en la ventana proporcionada
void Fondo::draw(sf::RenderWindow& window) {
    window.draw(sprite); // Dibuja el sprite del fondo en la ventana
}