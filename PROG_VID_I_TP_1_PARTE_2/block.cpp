#include "Block.h"

Block::Block(int value, const sf::Font& font, const sf::Texture& texture) : value(value), correct(false), incorrect(false) {
    sprite.setTexture(texture);
    text.setFont(font);
    text.setString(std::to_string(value));
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);
}

void Block::draw(sf::RenderWindow& window) {
    if (correct) {
        text.setFillColor(sf::Color::Green);
    }
    else if (incorrect) {
        text.setFillColor(sf::Color::Red);
    }
    else {
        text.setFillColor(sf::Color::Black);
    }
    window.draw(sprite);
    window.draw(text);
}

sf::FloatRect Block::getBounds() const {
    return sprite.getGlobalBounds();
}

int Block::getValue() const {
    return value;
}

void Block::setValue(int value) {
    this->value = value;
    text.setString(std::to_string(value));
}

void Block::setPosition(float x, float y) {
    sprite.setPosition(x, y);
    text.setPosition(x + 20, y - 20); // Ajustar la posición del texto sobre el bloque
}

sf::Vector2f Block::getPosition() const {
    return sprite.getPosition();
}

void Block::setCorrect(bool correct) {
    this->correct = correct;
    this->incorrect = false; // Asegurar que incorrecto se desactiva si es correcto
}

void Block::setIncorrect(bool incorrect) {
    this->incorrect = incorrect;
    if (incorrect) {
        this->correct = false; // Asegurar que correcto se desactiva si es incorrecto
    }
}

bool Block::isCorrect() const {
    return correct;
}