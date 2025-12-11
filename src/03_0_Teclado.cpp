#include <SFML/Graphics.hpp>

double velocidad = 0.3;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Hello Kitty Teclado");

    // Cargar la imagen de Hello Kitty
    sf::Texture texture;
    if (!texture.loadFromFile("assets/images/hellokitty.png"))
    {
        return -1;
    }

    // Crear un sprite y asignarle la textura
    sf::Sprite sprite(texture);
    sprite.setPosition(300, 250);
    sprite.setScale(0.3f, 0.3f);

    sf::Clock clock;
    float frameTime = 0.1f;
    int currentFrame = 0;
    int numFrames = 4;
    int frameWidth = 216;
    int frameHeight = 592;

    // Variables para el salto
    float velocidadY = 0;
    float gravedad = 0.01f;
    float fuerzaSalto = -1.5f;
    float suelo = 250;
    bool enElSuelo = true;
    bool spacePressedBefore = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Movimiento horizontal con teclado (funciona también durante el salto)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            sprite.move(-velocidad, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            sprite.move(velocidad, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            sprite.move(0, -velocidad);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            sprite.move(0, velocidad);
        }

        // Salto con espacio (solo una vez por toque)
        bool spacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
        if (spacePressed && !spacePressedBefore && enElSuelo) {
            velocidadY = fuerzaSalto;
            enElSuelo = false;
        }
        spacePressedBefore = spacePressed;

        // Aplicar gravedad y movimiento vertical
        velocidadY += gravedad;
        sprite.move(0, velocidadY);

        // Verificar si está en el suelo
        if (sprite.getPosition().y >= suelo) {
            sprite.setPosition(sprite.getPosition().x, suelo);
            velocidadY = 0;
            enElSuelo = true;
        }

        // Actualizar animación
        if (clock.getElapsedTime().asSeconds() >= frameTime)
        {
            currentFrame = (currentFrame + 1) % numFrames;
            sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
            clock.restart();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}
