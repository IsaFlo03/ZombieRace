#include <SFML/Graphics.hpp>
#include <vector>

double velocidad = 0.03;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Hello Kitty - Nivel 2");

    // Cargar los fondos del nivel 2
    sf::Texture fondoTexture1;
    if (!fondoTexture1.loadFromFile("assets/images/Fondo nivel 2.png"))
    {
        return -1;
    }
    
    sf::Texture fondoTexture2;
    if (!fondoTexture2.loadFromFile("assets/images/Fondo nivel 2.png"))
    {
        return -1;
    }
    
    // Cargar la imagen de la casita cerrada (inicial)
    sf::Texture cabanaAbiertaTexture;
    if (!cabanaAbiertaTexture.loadFromFile("assets/images/casita cerrada.png"))
    {
        return -1;
    }
    
    // Cargar la imagen de la casita (final)
    sf::Texture cabanitaTexture;
    if (!cabanitaTexture.loadFromFile("assets/images/casita.png"))
    {
        return -1;
    }
    
    // Cargar la imagen de interior para la victoria
    sf::Texture interiorTexture;
    if (!interiorTexture.loadFromFile("assets/images/casita adentro.png"))
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
    
    // Configurar todos los fondos (todos usando Fondo nivel 2)
    for (int i = 0; i < NUM_FONDOS; i++) {
        fondos[i].setTexture(fondoTexture1);
        fondos[i].setScale(escala1, escala1);
        fondos[i].setPosition(i * fondoAncho, 0);
    }

    // Cargar la imagen de Hello Kitty
    sf::Texture texture;
    if (!texture.loadFromFile("assets/images/hellokitty.png"))
    {
        return -1;
    }

    // Crear un sprite y asignarle la textura
    sf::Sprite sprite(texture);
    float posicionInicialX = 100;
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
    float alturaSuelo = 630; // Altura donde está el suelo
    bool enElSuelo = true;
    bool spacePressedBefore = false;

    // Variable para el desplazamiento del fondo
    float fondoOffset = 0.0f;
    float velocidadFondo = 0.5f; // Velocidad del fondo mantiene igual
    float distanciaRecorrida = 0.0f; // Distancia total recorrida sin ciclar
    
    // Crear meta (cabañita de llegada)
    float anchoCabanita = 1024.0f * 0.3f; // Ancho de la cabañita escalada (307.2)
    float distanciaMeta = 4800.0f - 800.0f + anchoCabanita; // Meta aparece completa en el borde derecho
    sf::Sprite cabanita(cabanaAbiertaTexture); // Iniciar con cabana abierta
    cabanita.setScale(0.3f, 0.3f); // Escalar la cabañita más pequeña
    cabanita.setPosition(distanciaMeta, alturaSuelo - 307.2f); // Posicionada sobre el suelo
    
    bool juegoGanado = false;
    sf::Clock relojVictoria; // Reloj para esperar antes de mostrar interior
    bool mostrarInterior = false;
    
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
    
    // Crear texto de victoria
    sf::Text textoVictoria;
    textoVictoria.setFont(zombieFont);
    textoVictoria.setString("estas a salvo esta vez");
    textoVictoria.setCharacterSize(50);
    textoVictoria.setFillColor(sf::Color::Red);
    textoVictoria.setPosition(150, 250);
    
    // Ajustar posición inicial de Hello Kitty para estar exactamente sobre el suelo
    float alturaSprite = frameHeight * 0.3f; // 592 * 0.3 = 177.6
    sprite.setPosition(posicionInicialX, alturaSuelo - alturaSprite);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
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
                // El fondo NO retrocede, solo Hello Kitty se mueve
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
        cabanita.setPosition(distanciaMeta - distanciaRecorrida, alturaSuelo - 307.2f);
        
        // Verificar colisión entre Hello Kitty y la cabañita
        float posXCabanita = distanciaMeta - distanciaRecorrida;
        float posXHelloKitty = sprite.getPosition().x;
        float anchoHelloKitty = frameWidth * 0.3f;
        float anchoCabanita = 1024.0f * 0.3f; // 307.2 píxeles
        
        // Si Hello Kitty llega a la mitad de la cabañita, desaparecer y cambiar imagen
        if (posXHelloKitty + anchoHelloKitty >= posXCabanita + (anchoCabanita / 2.0f) && !juegoGanado) {
            juegoGanado = true;
            cabanita.setTexture(cabanitaTexture); // Cambiar a cabana cerrada
            relojVictoria.restart(); // Iniciar contador para mostrar interior
        }
        
        // Verificar si han pasado 0.5 segundos desde que ganó
        if (juegoGanado && relojVictoria.getElapsedTime().asSeconds() >= 0.5f) {
            mostrarInterior = true;
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
        float alturaSprite = frameHeight * 0.3f;
        if (sprite.getPosition().y + alturaSprite >= alturaSuelo) {
            sprite.setPosition(sprite.getPosition().x, alturaSuelo - alturaSprite);
            velocidadY = 0;
            enElSuelo = true;
        }

        // Límites de pantalla
        if (sprite.getPosition().x < 0) {
            sprite.setPosition(0, sprite.getPosition().y);
        }
        if (sprite.getPosition().x > 800 - frameWidth * 0.3f) {
            sprite.setPosition(800 - frameWidth * 0.3f, sprite.getPosition().y);
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
        
        // Dibujar Hello Kitty solo si no ha ganado
        if (!juegoGanado) {
            window.draw(sprite);
        }
        
        // Mostrar mensaje de victoria si ganó y han pasado 0.5 segundos
        if (mostrarInterior) {
            window.draw(interiorSprite);
            window.draw(textoVictoria);
        }
        
        window.display();
    }

    return 0;
}
