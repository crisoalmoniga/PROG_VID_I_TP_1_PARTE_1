#include "Block.h"

// Constructor que inicializa el bloque con un valor, una fuente y una textura
Block::Block(int value, const sf::Font& font, const sf::Texture& texture) : value(value), correct(false), incorrect(false) {
    sprite.setTexture(texture); // Establece la textura del sprite
    text.setFont(font); // Establece la fuente del texto
    text.setString(std::to_string(value)); // Establece el texto con el valor del bloque
    text.setCharacterSize(20); // Establece el tamaño del texto
    text.setFillColor(sf::Color::Black); // Establece el color del texto
    text.setStyle(sf::Text::Bold); // Establece el estilo del texto
}

// Dibuja el bloque en la ventana proporcionada
void Block::draw(sf::RenderWindow& window) {
    if (correct) {
        text.setFillColor(sf::Color::Green); // Si el bloque es correcto, el texto se muestra en verde
    }
    else if (incorrect) {
        text.setFillColor(sf::Color::Red); // Si el bloque es incorrecto, el texto se muestra en rojo
    }
    else {
        text.setFillColor(sf::Color::Black); // Si el bloque no es ni correcto ni incorrecto, el texto se muestra en negro
    }
    window.draw(sprite); // Dibuja el sprite en la ventana
    window.draw(text); // Dibuja el texto en la ventana
}

// Devuelve los límites (bounding box) del bloque
sf::FloatRect Block::getBounds() const {
    return sprite.getGlobalBounds();
}

// Devuelve el valor del bloque
int Block::getValue() const {
    return value;
}

// Establece un nuevo valor para el bloque y actualiza el texto
void Block::setValue(int value) {
    this->value = value; // Establece un nuevo valor para el bloque
    text.setString(std::to_string(value)); // Actualiza el texto con el nuevo valor
}

// Establece la posición del bloque y del texto asociado
void Block::setPosition(float x, float y) {
    sprite.setPosition(x, y); // Establece la posición del sprite
    text.setPosition(x + 5, y + 8); // Ajustar la posición del texto sobre el bloque
}

// Devuelve la posición del bloque
sf::Vector2f Block::getPosition() const {
    return sprite.getPosition();
}

// Marca el bloque como correcto y desmarca como incorrecto
void Block::setCorrect(bool correct) {
    this->correct = correct;
    this->incorrect = false; // Asegurar que incorrecto se desactiva si es correcto
}

// Marca el bloque como incorrecto y desmarca como correcto
void Block::setIncorrect(bool incorrect) {
    this->incorrect = incorrect;
    if (incorrect) {
        this->correct = false; // Asegurar que correcto se desactiva si es incorrecto
    }
}

// Devuelve si el bloque es correcto
bool Block::isCorrect() const {
    return correct;
}