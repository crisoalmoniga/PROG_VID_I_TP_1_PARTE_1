#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Mario {
public:
    Mario(const sf::Texture& texture, sf::Sound& jumpSound);

    void update();
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    void stopJump();
    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;
    void setMovable(bool movable);
    void handleCollision(const sf::FloatRect& blockBounds);

private:
    sf::Sprite sprite;
    sf::Vector2f position;
    float speed;
    float jumpSpeed;
    float gravity;
    bool isJumping;
    bool movable;
    sf::Sound& jumpSound;

    void handleInput();
    void handleJump();
};