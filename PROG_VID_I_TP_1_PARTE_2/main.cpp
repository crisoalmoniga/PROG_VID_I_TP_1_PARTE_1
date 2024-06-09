#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "Mario.h"
#include "Fondo.h"
#include "Block.h"
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>


//Tengo varias cosas pendientes y otras que no llego a corregir:
// - Implementar Afichmation: en este caso no llegué a agregar la clase.
// - Música: si bien no es parte de la consigna, agregué algo de sonido pero no llegué con la música ya que tengo que editar el loop en reaper y luego implementarla.
// - Organizar el main: creo que podría llevarme la carga de texturas a cada clase y me entró la misma duda con el ordenamiento burbuja, está bien que cargue en el main?


// Método de ordenamiento burbuja
void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main() {
    // Crear una ventana de SFML
    sf::RenderWindow window(sf::VideoMode(800, 600), "PROG_VID_I_TP_1_PARTE_2");
    window.setFramerateLimit(60);

    // Cargar la textura de Mario
    sf::Texture marioTexture;
    if (!marioTexture.loadFromFile("assets/mario.png")) {
        return 1;
    }

    // Cargar la textura del fondo
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/mundo_fondo.jpg")) {
        return 1;
    }

    // Cargar la textura del bloque
    sf::Texture blockTexture;
    if (!blockTexture.loadFromFile("assets/bloque_pared.png")) {
        return 1;
    }

    // Cargar la fuente para los textos
    sf::Font font;
    if (!font.loadFromFile("assets/military_font_7.ttf")) {
        return 1;
    }

    // Cargar sonidos
    sf::SoundBuffer jumpBuffer;
    if (!jumpBuffer.loadFromFile("assets/jump.ogg")) {
        return 1;
    }
    sf::Sound jumpSound(jumpBuffer);

    sf::SoundBuffer collisionBuffer;
    if (!collisionBuffer.loadFromFile("assets/collision.ogg")) {
        return 1;
    }
    sf::Sound collisionSound(collisionBuffer);

    // Crear el objeto Mario
    Mario mario(marioTexture, jumpSound);

    // Crear el objeto Fondo
    Fondo fondo(backgroundTexture);

    // Crear un vector de valores desordenados
    std::vector<int> values(10);
    std::srand(std::time(0));
    for (int& value : values) {
        value = std::rand() % 999 + 1;
    }

    // Crear los bloques con los valores desordenados
    std::vector<Block> blocks;
    for (int value : values) {
        blocks.emplace_back(value, font, blockTexture);
    }

    // Colocar los bloques en la pantalla
    float startX = 50.0f; // Posición inicial en X
    float gap = 70.0f;    // Espacio entre los bloques
    for (int i = 0; i < blocks.size(); ++i) {
        blocks[i].setPosition(startX + i * gap, 260.0f); // Posicionar los bloques en una fila
    }

    // Configurar el temporizador
    sf::Clock clock;
    sf::Time timeLimit = sf::seconds(60);
    sf::Text timerText;
    timerText.setFont(font);
    timerText.setCharacterSize(24);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(700, 50);

    int nextBlockIndex = 0;

    // Bucle principal del juego
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Actualizar el tiempo restante
        sf::Time elapsedTime = clock.getElapsedTime();
        sf::Time remainingTime = timeLimit - elapsedTime;
        if (remainingTime.asSeconds() <= 0) {
            remainingTime = sf::Time::Zero;
        }

        int seconds = static_cast<int>(remainingTime.asSeconds());
        timerText.setString("Time: " + std::to_string(seconds));

        // Actualizar la posición de Mario
        mario.update();
        sf::FloatRect marioBounds = mario.getBounds();

        // Obtener el valor mínimo actual que debería golpear
        if (nextBlockIndex < blocks.size()) {
            // Encontrar el siguiente valor mínimo no golpeado
            int currentMinValue = INT_MAX;
            for (int i = 0; i < blocks.size(); ++i) {
                if (!blocks[i].isCorrect() && blocks[i].getValue() < currentMinValue) {
                    currentMinValue = blocks[i].getValue();
                }
            }

            // Verificar colisiones con los bloques
            for (int i = 0; i < blocks.size(); ++i) {
                if (marioBounds.intersects(blocks[i].getBounds()) && !blocks[i].isCorrect()) {
                    collisionSound.play(); // Reproducir sonido de colisión

                    // Verificar si el bloque tiene el valor mínimo esperado
                    if (blocks[i].getValue() == currentMinValue) {
                        blocks[i].setCorrect(true);
                        nextBlockIndex++;
                    }
                    else {
                        blocks[i].setIncorrect(true);
                        // Descontar 10 segundos solo si el bloque es incorrecto
                        timeLimit -= sf::seconds(10);
                    }

                    // Manejar la colisión de Mario con el bloque
                    mario.handleCollision(blocks[i].getBounds());
                }
            }
        }

        // Comprobar condiciones de fin de juego
        if (nextBlockIndex >= blocks.size() || remainingTime == sf::Time::Zero) {
            // Ordenar los valores
            bubbleSort(values);

            // Mostrar valores ordenados en los bloques
            for (int i = 0; i < blocks.size(); ++i) {
                blocks[i].setValue(values[i]);
                blocks[i].setCorrect(blocks[i].isCorrect());
            }

            // Detener al personaje
            mario.setMovable(false);
        }

        // Dibujar los elementos en la ventana
        window.clear();
        fondo.draw(window);
        mario.draw(window);
        for (Block& block : blocks) {
            block.draw(window);
        }
        window.draw(timerText);
        window.display();
    }

    return 0;
}