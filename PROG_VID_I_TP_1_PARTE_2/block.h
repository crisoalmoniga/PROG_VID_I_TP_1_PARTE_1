#include <SFML/Graphics.hpp>

class Block {
public:
    // Constructor que inicializa el bloque con un valor, una fuente y una textura
    Block(int value, const sf::Font& font, const sf::Texture& texture);

    // Dibuja el bloque en la ventana proporcionada
    void draw(sf::RenderWindow& window);

    // Devuelve los límites (bounding box) del bloque
    sf::FloatRect getBounds() const;

    // Devuelve el valor del bloque
    int getValue() const;

    // Establece un nuevo valor para el bloque y actualiza el texto
    void setValue(int value);

    // Establece la posición del bloque y del texto asociado
    void setPosition(float x, float y);

    // Devuelve la posición del bloque
    sf::Vector2f getPosition() const;

    // Marca el bloque como correcto y desmarca como incorrecto
    void setCorrect(bool correct);

    // Marca el bloque como incorrecto y desmarca como correcto
    void setIncorrect(bool incorrect);

    // Devuelve si el bloque es correcto
    bool isCorrect() const;

private:
    sf::Sprite sprite; // Sprite que representa el bloque
    sf::Text text; // Texto que muestra el valor del bloque
    int value; // Valor del bloque
    bool correct; // Indica si el bloque es correcto
    bool incorrect; // Indica si el bloque es incorrecto
};