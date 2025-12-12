#include <SFML/Graphics.hpp>
#include <vector>

double velocidad = 0.03;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snoopy - Nivel 3");

    // Cargar los fondos del nivel 3
    sf::Texture fondoTexture1;
    if (!fondoTexture1.loadFromFile("assets/images/Fondo nivel 3.png"))
    {
        return -1;
    }
    
    sf::Texture fondoTexture2;
    if (!fondoTexture2.loadFromFile("assets/images/Fondo nivel 3.png"))
    {
        return -1;
    }
    
    // Cargar la imagen de la casita cerrada (inicial)
    sf::Texture cabanaAbiertaTexture;
    if (!cabanaAbiertaTexture.loadFromFile("assets/images/salvacion.png"))
    {
        return -1;
    }
    
    // Cargar la imagen de la casita (final)
    sf::Texture cabanitaTexture;
    if (!cabanitaTexture.loadFromFile("assets/images/salvacion.png"))
    {
        return -1;
    }
    
    // Cargar la imagen de interior para la victoria
    sf::Texture interiorTexture;
    if (!interiorTexture.loadFromFile("assets/images/imagen final.png"))
    {
        return -1;
    }

    // Cargar la imagen de snoopy amigos para mostrar después
    sf::Texture amigosTexture;
    if (!amigosTexture.loadFromFile("assets/images/snoopy amigos.png"))
    {
        return -1;
    }

    // Crear múltiples sprites del fondo para efecto parallax continuo
    const int NUM_FONDOS = 16; // 8 de cada tipo
    sf::Sprite fondos[NUM_FONDOS];
    
    // Usar escala proporcional manteniendo aspect ratio (no estirar la imagen)
    float escalaX1 = 800.0f / fondoTexture1.getSize().x;
    float escalaY1 = 600.0f / fondoTexture1.getSize().y;
    // Usar la escala menor para mantener proporción y que se vea bien
    float escala1 = (escalaX1 < escalaY1) ? escalaY1 : escalaY1;
    
    // Obtener el ancho del fondo escalado
    float fondoAncho = fondoTexture1.getSize().x * escala1;
    
    // Configurar todos los fondos (todos usando Fondo nivel 3)
    for (int i = 0; i < NUM_FONDOS; i++) {
        fondos[i].setTexture(fondoTexture1);
        fondos[i].setScale(escala1, escala1);
        fondos[i].setPosition(i * fondoAncho, 0);
    }

    // Cargar la imagen de Snoopy
    sf::Texture texture;
    if (!texture.loadFromFile("assets/images/snoopy.png"))
    {
        return -1;
    }

    // Crear un sprite y asignarle la textura
    sf::Sprite sprite(texture);
    float posicionInicialX = 100;
    sprite.setScale(0.2f, 0.2f);

    sf::Clock clock;
    float frameTime = 0.1f;
    int currentFrame = 0;
    int numFrames = 4;
    int frameWidth = 264;
    int frameHeight = 992;

    // Variables para el salto
    float velocidadY = 0;
    float gravedad = 0.01f;
    float fuerzaSalto = -1.5f;
    float alturaSuelo = 630; // Altura donde está el suelo
    bool enElSuelo = true;
    bool spacePressedBefore = false;

    // Variable para el desplazamiento del fondo
    float fondoOffset = 0.0f;
    float velocidadFondo = 0.25f; // Velocidad del fondo más lenta
    float distanciaRecorrida = 0.0f; // Distancia total recorrida sin ciclar
    
    // Crear meta (cabañita de llegada)
    float anchoCabanita = 1024.0f * 0.5f; // Ancho de la cabañita escalada (512)
    float distanciaMeta = 4800.0f - 800.0f + anchoCabanita; // Meta aparece completa en el borde derecho
    sf::Sprite cabanita(cabanaAbiertaTexture); // Iniciar con cabana abierta
    cabanita.setScale(0.5f, 0.5f); // Escalar la cabañita más grande
    cabanita.setPosition(distanciaMeta, alturaSuelo - 400.0f); // Posicionada más abajo
    
    bool juegoGanado = false;
    sf::Clock relojVictoria; // Reloj para esperar antes de mostrar interior
    bool mostrarInterior = false;
    bool mostrarAmigos = false; // Mostrar imagen de amigos después de 30 segundos
    
    // Cargar la fuente para el mensaje de victoria
    sf::Font zombieFont;
    if (!zombieFont.loadFromFile("assets/fonts/Zombie_Hunger[1].ttf"))
    {
        return -1;
    }
    
    // Crear sprite de interior para la victoria
    sf::Sprite interiorSprite(interiorTexture);
    // Escalar para que cubra toda la ventana
    float escalaInteriorX = 800.0f / interiorTexture.getSize().x;
    float escalaInteriorY = 600.0f / interiorTexture.getSize().y;
    interiorSprite.setScale(escalaInteriorX, escalaInteriorY);
    interiorSprite.setPosition(0, 0);
    
    // Crear sprite de amigos para mostrar después
    sf::Sprite amigosSprite(amigosTexture);
    // Escalar para que cubra toda la ventana
    float escalaAmigosX = 800.0f / amigosTexture.getSize().x;
    float escalaAmigosY = 600.0f / amigosTexture.getSize().y;
    amigosSprite.setScale(escalaAmigosX, escalaAmigosY);
    amigosSprite.setPosition(0, 0);
    
    // Crear texto de victoria
    sf::Text textoVictoria;
    textoVictoria.setFont(zombieFont);
    textoVictoria.setString("estas a salvo esta vez");
    textoVictoria.setCharacterSize(50);
    textoVictoria.setFillColor(sf::Color::Red);
    textoVictoria.setPosition(150, 250);
    
    // Crear texto "wiiii" para pantalla de amigos
    sf::Text textoWiiii;
    textoWiiii.setFont(zombieFont);
    textoWiiii.setString("wiiii");
    textoWiiii.setCharacterSize(80);
    textoWiiii.setFillColor(sf::Color(135, 206, 235)); // Azul cielo
    textoWiiii.setPosition(300, 50);
    
    // Crear texto "volver al menu"
    sf::Text textoVolverMenu;
    textoVolverMenu.setFont(zombieFont);
    textoVolverMenu.setString("volver al menu");
    textoVolverMenu.setCharacterSize(40);
    textoVolverMenu.setFillColor(sf::Color::Black);
    textoVolverMenu.setPosition(480, 540);
    
    // Ajustar posición inicial de Snoopy para estar exactamente sobre el suelo
    float alturaSprite = frameHeight * 0.2f; // 992 * 0.2 = 198.4
    sprite.setPosition(posicionInicialX, alturaSuelo - alturaSprite);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            // Detectar clic en "volver al menu" cuando se muestra la pantalla de amigos
            if (mostrarAmigos && event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    sf::FloatRect boundsMenu = textoVolverMenu.getGlobalBounds();
                    if (boundsMenu.contains(mousePos.x, mousePos.y)) {
                        window.close(); // Cerrar el juego
                    }
                }
            }
        }

        // Movimiento horizontal
        bool moviendoDerecha = false;
        bool moviendoIzquierda = false;
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            // Solo permitir retroceder si no está en la posición inicial
            if (sprite.getPosition().x > posicionInicialX) {
                sprite.move(-velocidad, 0);
                moviendoIzquierda = true;
                // El fondo NO retrocede, solo Snoopy se mueve
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            sprite.move(velocidad, 0);
            moviendoDerecha = true;
            // Mover el fondo solo si no hemos llegado a la meta
            if (distanciaRecorrida < distanciaMeta) {
                fondoOffset -= velocidadFondo;
                distanciaRecorrida += velocidadFondo; // Acumular distancia real
            }
        }

        // Ciclar el fondo infinitamente de manera suave
        // Solo ciclar cuando el offset sea negativo (avanzando)
        if (fondoOffset <= -fondoAncho * 2) {
            fondoOffset += fondoAncho * 2; // Ciclar cada 2 fondos (1 par completo)
        }
        
        // Actualizar posiciones de todos los fondos
        for (int i = 0; i < NUM_FONDOS; i++) {
            fondos[i].setPosition(fondoOffset + (i * fondoAncho), 0);
        }
        
        // Actualizar posición de la meta usando distancia real
        cabanita.setPosition(distanciaMeta - distanciaRecorrida, alturaSuelo - 400.0f);
        
        // Verificar colisión entre Snoopy y la cabañita
        float posXCabanita = distanciaMeta - distanciaRecorrida;
        float posXSnoopy = sprite.getPosition().x;
        float anchoSnoopy = frameWidth * 0.2f;
        float anchoCabanita = 1024.0f * 0.5f; // 512 píxeles
        
        // Si Snoopy llega a la mitad de la cabañita, desaparecer y cambiar imagen
        if (posXSnoopy + anchoSnoopy >= posXCabanita + (anchoCabanita / 2.0f) && !juegoGanado) {
            juegoGanado = true;
            cabanita.setTexture(cabanitaTexture); // Cambiar a cabana cerrada
            relojVictoria.restart(); // Iniciar contador para mostrar interior
        }
        
        // Verificar si han pasado 0.5 segundos desde que ganó
        if (juegoGanado && relojVictoria.getElapsedTime().asSeconds() >= 0.5f) {
            mostrarInterior = true;
        }
        
        // Verificar si han pasado 3 segundos desde que mostró interior
        if (mostrarInterior && relojVictoria.getElapsedTime().asSeconds() >= 3.5f) {
            mostrarAmigos = true;
        }

        // Salto con espacio
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
        float alturaSprite = frameHeight * 0.2f;
        if (sprite.getPosition().y + alturaSprite >= alturaSuelo) {
            sprite.setPosition(sprite.getPosition().x, alturaSuelo - alturaSprite);
            velocidadY = 0;
            enElSuelo = true;
        }

        // Límites de pantalla
        if (sprite.getPosition().x < 0) {
            sprite.setPosition(0, sprite.getPosition().y);
        }
        if (sprite.getPosition().x > 800 - frameWidth * 0.2f) {
            sprite.setPosition(800 - frameWidth * 0.2f, sprite.getPosition().y);
        }

        // Actualizar animación solo cuando se mueve
        if (moviendoDerecha || moviendoIzquierda) {
            if (clock.getElapsedTime().asSeconds() >= frameTime) {
                currentFrame = (currentFrame + 1) % numFrames;
                sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
                clock.restart();
            }
        } else {
            // Mantener frame estático cuando no se mueve
            sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
        }

        // Dibujar
        window.clear();
        
        // Dibujar todos los fondos para efecto continuo
        for (int i = 0; i < NUM_FONDOS; i++) {
            window.draw(fondos[i]);
        }
        
        // Dibujar meta
        window.draw(cabanita);
        
        // Dibujar Snoopy solo si no ha ganado
        if (!juegoGanado) {
            window.draw(sprite);
        }
        
        // Mostrar mensaje de victoria si ganó y han pasado 0.5 segundos
        if (mostrarAmigos) {
            // Mostrar imagen de amigos después de 1 segundo
            window.draw(amigosSprite);
            window.draw(textoVolverMenu);
        } else if (mostrarInterior) {
            // Mostrar imagen final sin texto
            window.draw(interiorSprite);
        }
        
        window.display();
    }

    return 0;
}
