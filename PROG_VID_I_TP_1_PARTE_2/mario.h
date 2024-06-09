#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Mario {
public:
    // Constructor que inicializa a Mario con una textura y un sonido de salto
    Mario(const sf::Texture& texture, sf::Sound& jumpSound);

    // Actualiza el estado de Mario
    void update();

    // Dibuja a Mario en la ventana proporcionada
    void draw(sf::RenderWindow& window);

    // Devuelve los l�mites (bounding box) de Mario
    sf::FloatRect getBounds() const;

    // Detiene el salto de Mario
    void stopJump();

    // Establece la posici�n de Mario
    void setPosition(float x, float y);

    // Devuelve la posici�n de Mario
    sf::Vector2f getPosition() const;

    // Establece si Mario es movible o no
    void setMovable(bool movable);

    // Maneja la colisi�n de Mario con los bloques
    void handleCollision(const sf::FloatRect& blockBounds);

private:
    sf::Sprite sprite; // Sprite que representa a Mario
    sf::Vector2f position; // Posici�n de Mario
    float speed; // Velocidad de movimiento de Mario
    float jumpSpeed; // Velocidad de salto de Mario
    float gravity; // Gravedad que afecta a Mario durante el salto
    bool isJumping; // Indica si Mario est� saltando
    bool movable; // Indica si Mario puede moverse
    sf::Sound& jumpSound; // Sonido que se reproduce cuando Mario salta

    // Maneja la entrada del usuario para mover a Mario
    void handleInput();

    // Maneja la l�gica del salto de Mario
    void handleJump();
};