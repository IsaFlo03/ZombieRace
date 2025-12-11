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
    sprite.setPosition(300, 50);
    
    // Escalar la imagen para que se vea más pequeña y quepa completa
    sprite.setScale(0.3f, 0.3f);

    sf::Clock clock;
    float frameTime = 0.1f; // Tiempo entre cada frame en segundos
    int currentFrame = 0;
    int numFrames = 4; // Número total de frames en la animación
    int frameWidth = 216;  // Cada frame tiene 216 píxeles de ancho (864/4)
    int frameHeight = 592; // Cada frame tiene 592 píxeles de alto (1184/2)
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
        if (sprite.getPosition().x > 800)
        {
            sprite.setPosition(-frameWidth * 0.3f, sprite.getPosition().y);
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
