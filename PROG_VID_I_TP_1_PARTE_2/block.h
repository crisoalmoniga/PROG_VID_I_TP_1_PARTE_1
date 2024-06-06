#include <SFML/Graphics.hpp>

class Block {
public:
    Block(int value, const sf::Font& font, const sf::Texture& texture);

    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    int getValue() const;
    void setValue(int value);
    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;
    void setCorrect(bool correct);
    void setIncorrect(bool incorrect);
    bool isCorrect() const;

private:
    sf::Sprite sprite;
    sf::Text text;
    int value;
    bool correct;
    bool incorrect;
};