#include "Mario.h"

Mario::Mario(const sf::Texture& texture, sf::Sound& jumpSound) : sprite(texture), position(100.f, 400.f), speed(5.0f), jumpSpeed(-10.0f), gravity(0.5f), isJumping(false), movable(true), jumpSound(jumpSound) {
    sprite.setPosition(position);
}

void Mario::update() {
    if (movable) {
        handleInput();
        handleJump();
    }
}

void Mario::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Mario::getBounds() const {
    return sprite.getGlobalBounds();
}

void Mario::stopJump() {
    isJumping = false;
    jumpSpeed = -10.0f;
}

void Mario::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
    sprite.setPosition(position);
}

sf::Vector2f Mario::getPosition() const {
    return position;
}

void Mario::setMovable(bool movable) {
    this->movable = movable;
}

void Mario::handleCollision(const sf::FloatRect& blockBounds) {
    sf::FloatRect marioBounds = getBounds();

    if (marioBounds.intersects(blockBounds)) {
        // Check collision direction
        float marioBottom = marioBounds.top + marioBounds.height;
        float blockBottom = blockBounds.top + blockBounds.height;
        float marioRight = marioBounds.left + marioBounds.width;
        float blockRight = blockBounds.left + blockBounds.width;

        float bottomCollision = blockBottom - marioBounds.top;
        float topCollision = marioBottom - blockBounds.top;
        float leftCollision = marioRight - blockBounds.left;
        float rightCollision = blockRight - marioBounds.left;

        if (topCollision < bottomCollision && topCollision < leftCollision && topCollision < rightCollision) {
            // Collision from the top
            stopJump();
            setPosition(position.x, blockBounds.top - marioBounds.height);
        }
        else if (bottomCollision < topCollision && bottomCollision < leftCollision && bottomCollision < rightCollision) {
            // Collision from the bottom
            position.y = blockBounds.top + blockBounds.height;
            jumpSpeed = 0;
        }
        else if (leftCollision < rightCollision && leftCollision < topCollision && leftCollision < bottomCollision) {
            // Collision from the left
            position.x = blockBounds.left - marioBounds.width;
        }
        else if (rightCollision < leftCollision && rightCollision < topCollision && rightCollision < bottomCollision) {
            // Collision from the right
            position.x = blockBounds.left + blockBounds.width;
        }
        sprite.setPosition(position);
    }
}

void Mario::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        position.x -= speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        position.x += speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isJumping) {
        isJumping = true;
        jumpSound.play();
    }
    sprite.setPosition(position);
}

void Mario::handleJump() {
    if (isJumping) {
        position.y += jumpSpeed;
        jumpSpeed += gravity;
        if (position.y >= 400.f) {
            isJumping = false;
            position.y = 400.f;
            jumpSpeed = -10.0f;
        }
        sprite.setPosition(position);
    }
}