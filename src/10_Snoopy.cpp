#include <SFML/Graphics.hpp>

int main()
{
    // Crear una ventana más grande para ver a Snoopy completo
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snoopy Animado");

    // Cargar la imagen desde un archivo
    sf::Texture texture;
    if (!texture.loadFromFile("assets/images/snoopy.png"))
    {
        // Manejo de error si no se puede cargar la imagen
        return -1;
    }

    // Crear sprites para cada parte de Snoopy
    sf::Sprite spriteSuperior(texture);
    sf::Sprite spriteInferior(texture);
    
    // Dimensiones de cada frame
    int frameWidth = 264;  // Ancho de cada frame (1056/4 columnas)
    int frameHeight = 496; // Alto de cada frame (992/2 filas)
    
    // Configurar el rectángulo de textura para cada sprite (usar la primera columna)
    spriteSuperior.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight)); // Parte superior
    spriteInferior.setTextureRect(sf::IntRect(0, frameHeight, frameWidth, frameHeight)); // Parte inferior
    
    // Calcular escala para que quepa en la ventana
    float totalHeight = frameHeight * 2; // Altura total de ambas partes
    float scaleX = 800.0f / frameWidth;
    float scaleY = 600.0f / totalHeight;
    float scale = (scaleX < scaleY) ? scaleX * 0.9f : scaleY * 0.9f; // 90% del espacio disponible
    
    spriteSuperior.setScale(scale, scale);
    spriteInferior.setScale(scale, scale);
    
    // Posicionar los sprites uno debajo del otro y centrados
    float scaledWidth = frameWidth * scale;
    float scaledHeight = frameHeight * scale;
    float startX = (800 - scaledWidth) / 2;
    float startY = (600 - (scaledHeight * 2)) / 2;
    
    spriteSuperior.setPosition(startX, startY);
    spriteInferior.setPosition(startX, startY + scaledHeight);

    sf::Clock clock;
    float frameTime = 0.1f; // Tiempo entre cada frame en segundos
    int currentFrame = 0;
    int numFrames = 4; // Número de frames por fila

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

        // Actualizar el frame de la animación
        if (clock.getElapsedTime().asSeconds() >= frameTime)
        {
            currentFrame = (currentFrame + 1) % numFrames;
            // Actualizar ambos sprites con el mismo frame
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
