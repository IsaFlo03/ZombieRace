#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    // Crear una ventana
    sf::RenderWindow window(sf::VideoMode(800, 600), "Zombie Corriendo");

    // Cargar la imagen desde un archivo
    sf::Texture texture;
    if (!texture.loadFromFile("assets/images/Horda bien.png"))
    {
        std::cout << "Error: No se pudo cargar la imagen" << std::endl;
        return -1;
    }

    // Obtener dimensiones de la textura
    sf::Vector2u textureSize = texture.getSize();
    std::cout << "Tamaño de la textura: " << textureSize.x << "x" << textureSize.y << std::endl;
    
    // Calcular dimensiones de cada frame (5 columnas, 1 fila)
    int numFrames = 5;
    int frameWidth = textureSize.x / numFrames;
    int frameHeight = textureSize.y;
    
    std::cout << "Dimensiones del frame: " << frameWidth << "x" << frameHeight << std::endl;
    
    // Crear un sprite y asignarle la textura
    sf::Sprite sprite(texture);
    
    // Calcular escala para que los zombies quepan completos en la ventana
    float scaleX = 600.0f / frameWidth;  // Dejar espacio horizontal
    float scaleY = 500.0f / frameHeight; // Dejar espacio vertical
    float scale = (scaleX < scaleY) ? scaleX : scaleY;
    
    sprite.setScale(-scale, scale); // Escala negativa en X para espejear horizontalmente
    
    // Centrar verticalmente
    float scaledHeight = frameHeight * scale;
    float scaledWidth = frameWidth * scale;
    // Ajustar posición inicial considerando el espejeo
    sprite.setPosition(scaledWidth, (600 - scaledHeight) / 2);

    sf::Clock clock;
    sf::Clock moveClock;
    float frameTime = 0.2f; // Aumentar tiempo entre frames para animación más lenta
    int currentFrame = 0;
    float speed = 100.0f;

    while (window.isOpen())
    {
        // Procesar eventos
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // Mover sprite a la derecha
        float deltaTime = moveClock.restart().asSeconds();
        sprite.move(speed * deltaTime, 0);

        // Si sale de la pantalla, volver al inicio
        float scaledWidth = frameWidth * scale;
        if (sprite.getPosition().x > 800)
        {
            float scaledHeight = frameHeight * scale;
            sprite.setPosition(-scaledWidth, (600 - scaledHeight) / 2);
        }

        // Actualizar el frame de la animación
        if (clock.getElapsedTime().asSeconds() >= frameTime)
        {
            currentFrame = (currentFrame + 1) % numFrames;
            sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
            clock.restart();
        }

        // Limpiar con el fondo predeterminado (negro)
        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}
