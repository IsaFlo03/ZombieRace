#include <SFML/Graphics.hpp>

int main()
{
    // Crear una ventana
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sprite Animado");

    // Cargar la imagen desde un archivo
    sf::Texture texture;
    if (!texture.loadFromFile("assets/images/hellokitty.png"))
    {
        // Manejo de error si no se puede cargar la imagen
        return -1;
    }

    // Crear un sprite y asignarle la textura
    sf::Sprite sprite(texture);
    
    // Dimensiones de cada frame - imagen hellokitty.png es 1280x612
    int numFrames = 4; // Número total de frames en la animación (4 columnas)
    int frameWidth = 320;  // Cada frame tiene 320 píxeles de ancho (1280/4)
    int frameHeight = 612; // Altura de la imagen
    
    // Establecer el primer frame desde el inicio
    sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
    
    // Escalar para que se vea bien en la ventana
    float scale = 0.2f;
    sprite.setScale(scale, scale);
    
    // Centrar verticalmente
    float scaledHeight = frameHeight * scale;
    sprite.setPosition(300, (600 - scaledHeight) / 2);

    sf::Clock clock;
    float frameTime = 0.1f; // Tiempo entre cada frame en segundos
    int currentFrame = 0;
    float speed = 100.0f; // Velocidad de movimiento en píxeles por segundo

    sf::Clock movementClock; // Reloj para el movimiento

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

        // Mover el sprite hacia la derecha
        float deltaTime = movementClock.restart().asSeconds();
        sprite.move(speed * deltaTime, 0);

        // Si el sprite sale por la derecha, reiniciar a la izquierda
        float scaledWidth = frameWidth * scale;
        if (sprite.getPosition().x > 800)
        {
            sprite.setPosition(-scaledWidth, sprite.getPosition().y);
        }

        // Actualizar el frame de la animación
        if (clock.getElapsedTime().asSeconds() >= frameTime)
        {
            currentFrame = (currentFrame + 1) % numFrames;
            // Usar la primera fila de frames (Y=0), recorriendo las columnas
            sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
            clock.restart();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}
