#include "Fondo.h"

Fondo::Fondo(const sf::Texture& texture) : sprite(texture) {}

void Fondo::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}