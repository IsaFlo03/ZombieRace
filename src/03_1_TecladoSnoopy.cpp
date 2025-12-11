#include <SFML/Graphics.hpp>

double velocidad = 0.3;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snoopy Teclado");

    // Cargar la imagen de Snoopy
    sf::Texture texture;
    if (!texture.loadFromFile("assets/images/snoopy.png"))
    {
        return -1;
    }

    // Crear sprites para cada parte de Snoopy
    sf::Sprite spriteSuperior(texture);
    sf::Sprite spriteInferior(texture);
    
    // Dimensiones de cada frame
    int frameWidth = 264;  // Ancho de cada frame (1056/4 columnas)
    int frameHeight = 496; // Alto de cada frame (992/2 filas)
    
    // Configurar el rectángulo de textura para cada sprite
    spriteSuperior.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
    spriteInferior.setTextureRect(sf::IntRect(0, frameHeight, frameWidth, frameHeight));
    
    // Escalar ambos sprites
    float scale = 0.2f;
    spriteSuperior.setScale(scale, scale);
    spriteInferior.setScale(scale, scale);
    
    // Posición inicial
    float posX = 300;
    float posY = 250;
    float scaledHeight = frameHeight * scale;
    
    spriteSuperior.setPosition(posX, posY);
    spriteInferior.setPosition(posX, posY + scaledHeight);

    sf::Clock clock;
    float frameTime = 0.1f;
    int currentFrame = 0;
    int numFrames = 4;

    // Variables para el salto
    float velocidadY = 0;
    float gravedad = 0.01f;
    float fuerzaSalto = -1.5f;
    float suelo = 250;
    bool enElSuelo = true;
    bool spacePressedBefore = false;

    // Variables para el boost de velocidad
    float velocidadActual = velocidad;
    float velocidadBoost = velocidad * 3.0f;
    bool boostActivo = false;
    sf::Clock boostClock;
    bool upPressedBefore = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Activar boost con flecha arriba (solo una vez por toque)
        bool upPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
        if (upPressed && !upPressedBefore && !boostActivo) {
            boostActivo = true;
            velocidadActual = velocidadBoost;
            boostClock.restart();
        }
        upPressedBefore = upPressed;

        // Desactivar boost después de 2 segundos
        if (boostActivo && boostClock.getElapsedTime().asSeconds() >= 2.0f) {
            boostActivo = false;
            velocidadActual = velocidad;
        }

        // Movimiento horizontal con teclado (funciona también durante el salto)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            spriteSuperior.move(-velocidadActual, 0);
            spriteInferior.move(-velocidadActual, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            spriteSuperior.move(velocidadActual, 0);
            spriteInferior.move(velocidadActual, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            spriteSuperior.move(0, velocidad);
            spriteInferior.move(0, velocidad);
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
        spriteSuperior.move(0, velocidadY);
        spriteInferior.move(0, velocidadY);

        // Verificar si está en el suelo
        if (spriteSuperior.getPosition().y >= suelo) {
            spriteSuperior.setPosition(spriteSuperior.getPosition().x, suelo);
            spriteInferior.setPosition(spriteInferior.getPosition().x, suelo + scaledHeight);
            velocidadY = 0;
            enElSuelo = true;
        }

        // Actualizar animación
        if (clock.getElapsedTime().asSeconds() >= frameTime)
        {
            currentFrame = (currentFrame + 1) % numFrames;
            spriteSuperior.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
            spriteInferior.setTextureRect(sf::IntRect(currentFrame * frameWidth, frameHeight, frameWidth, frameHeight));
            clock.restart();
        }

        window.clear();
        window.draw(spriteSuperior);
        window.draw(spriteInferior);
        window.display();
    }

    return 0;
}
