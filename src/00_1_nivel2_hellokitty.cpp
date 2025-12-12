#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

double velocidad = 0.03;

int main() {
    // Inicializar semilla aleatoria con valor fijo para posiciones consistentes
    std::srand(42);
    
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
    
    // Cargar la imagen de derrota
    sf::Texture derrotaTexture;
    if (!derrotaTexture.loadFromFile("assets/images/hellokitty perdedora.png"))
    {
        return -1;
    }
    
    // Cargar la imagen de la horda de zombies
    sf::Texture hordaTexture;
    if (!hordaTexture.loadFromFile("assets/images/Horda bien.png"))
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

    // Cargar las texturas de los zombies
    sf::Texture zombieTextures[7];
    std::string zombieNames[7] = {
        "Zombirron", "Zombiano", "Zombilia", "Zombando",
        "Zombiguada", "Zombiscocho", "Zombiela"
    };
    
    for (int i = 0; i < 7; i++) {
        if (!zombieTextures[i].loadFromFile("assets/images/" + zombieNames[i] + ".png")) {
            return -1;
        }
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
    
    // Crear sprites de zombies con posiciones aleatorias
    sf::Sprite zombieSprites[7];
    float zombiePosicionesIniciales[7]; // Guardar posiciones iniciales absolutas
    float alturaUniformeZombies = 100.0f; // Altura uniforme para todos los zombies
    
    // Posiciones fijas y dispersas para cada zombie
    float posicionesFijas[7] = {
        600.0f, 1200.0f, 1800.0f, 2400.0f,
        3000.0f, 3600.0f, 4000.0f
    };
    
    for (int i = 0; i < 7; i++) {
        zombieSprites[i].setTexture(zombieTextures[i]);
        
        // Calcular escala para que todos tengan la misma altura
        float escalaUniforme = alturaUniformeZombies / zombieTextures[i].getSize().y;
        zombieSprites[i].setScale(escalaUniforme, escalaUniforme);
        
        // Usar posiciones fijas
        zombiePosicionesIniciales[i] = posicionesFijas[i];
        float posicionY = alturaSuelo - alturaUniformeZombies - 50.0f;
        
        zombieSprites[i].setPosition(zombiePosicionesIniciales[i], posicionY);
    }
    
    bool enElSuelo = true;
    bool spacePressedBefore = false;

    // Variable para el desplazamiento del fondo
    float fondoOffset = 0.0f;
    float velocidadFondo = 0.5f; // Velocidad del fondo
    float distanciaRecorrida = 0.0f; // Distancia total recorrida sin ciclar
    
    // Configurar la horda de zombies que persigue
    int hordaNumFrames = 5;
    int hordaFrameWidth = hordaTexture.getSize().x / hordaNumFrames;
    int hordaFrameHeight = hordaTexture.getSize().y;
    int hordaCurrentFrame = 0;
    float hordaScale = 0.9f; // Escala más grande para la horda
    
    sf::Sprite hordaSprite(hordaTexture);
    hordaSprite.setTextureRect(sf::IntRect(0, 0, hordaFrameWidth, hordaFrameHeight));
    hordaSprite.setScale(hordaScale, hordaScale);
    float hordaPosX = -200.0f; // Empieza fuera de la pantalla a la izquierda
    float hordaPosY = alturaSuelo - (hordaFrameHeight * hordaScale) + 255.0f; // Bajada 255 píxeles
    hordaSprite.setPosition(hordaPosX, hordaPosY);
    float hordaVelocidad = 0.06f; // Velocidad un poquito más lenta
    sf::Clock hordaClock; // Reloj independiente para la horda
    sf::Clock relojInicioHorda; // Reloj para controlar cuándo empieza la horda
    bool hordaIniciada = false; // Si la horda ya debe moverse
    bool helloKittySeMovio = false; // Si Hello Kitty ya se movió
    
    // Crear meta (cabañita de llegada)
    float anchoCabanita = 1024.0f * 0.3f; // Ancho de la cabañita escalada (307.2)
    float distanciaMeta = 4800.0f - 800.0f + anchoCabanita; // Meta aparece completa en el borde derecho
    sf::Sprite cabanita(cabanaAbiertaTexture); // Iniciar con cabana abierta
    cabanita.setScale(0.3f, 0.3f); // Escalar la cabañita más pequeña
    cabanita.setPosition(distanciaMeta, alturaSuelo - 307.2f); // Posicionada sobre el suelo
    
    bool juegoGanado = false;
    bool juegoPerdido = false;
    sf::Clock relojVictoria; // Reloj para esperar antes de mostrar interior
    sf::Clock relojDerrota; // Reloj para esperar antes de mostrar derrota
    bool mostrarInterior = false;
    bool mostrarDerrota = false;
    
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
    
    // Crear sprite de derrota
    sf::Sprite derrotaSprite(derrotaTexture);
    derrotaSprite.setScale(0.5f, 0.5f);
    
    // Crear texto de derrota
    sf::Text textoDerrota;
    textoDerrota.setFont(zombieFont);
    textoDerrota.setString("te atraparon los zombies");
    textoDerrota.setCharacterSize(50);
    textoDerrota.setFillColor(sf::Color::Red);
    textoDerrota.setPosition(120, 250);
    
    // Crear texto de reinicio
    sf::Text textoReiniciar;
    textoReiniciar.setFont(zombieFont);
    textoReiniciar.setString("Reiniciar");
    textoReiniciar.setCharacterSize(50);
    textoReiniciar.setFillColor(sf::Color::White);
    textoReiniciar.setPosition(300, 350);
    
    // Ajustar posición inicial de Hello Kitty para estar exactamente sobre el suelo
    float alturaSprite = frameHeight * 0.3f; // 592 * 0.3 = 177.6
    sprite.setPosition(posicionInicialX, alturaSuelo - alturaSprite);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            // Detectar clic para reiniciar cuando se pierde
            if (event.type == sf::Event::MouseButtonPressed && juegoPerdido)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    sf::FloatRect reiniciarBounds = textoReiniciar.getGlobalBounds();
                    
                    if (reiniciarBounds.contains(mousePos.x, mousePos.y))
                    {
                        // Reiniciar el juego
                        juegoPerdido = false;
                        mostrarDerrota = false;
                        distanciaRecorrida = 0.0f;
                        fondoOffset = 0.0f;
                        sprite.setPosition(posicionInicialX, alturaSuelo - alturaSprite);
                        velocidadY = 0;
                        enElSuelo = true;
                        hordaPosX = -200.0f; // Reiniciar posición de la horda
                        hordaIniciada = false; // Reiniciar estado de la horda
                        helloKittySeMovio = false; // Reiniciar estado de movimiento
                    }
                }
            }
        }

        // Movimiento horizontal (solo si no ha perdido ni ganado)
        bool moviendoDerecha = false;
        bool moviendoIzquierda = false;
        
        if (!juegoPerdido && !juegoGanado) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                // Solo permitir retroceder si no está en la posición inicial
                if (sprite.getPosition().x > posicionInicialX) {
                    sprite.move(-velocidad, 0);
                    moviendoIzquierda = true;
                    // El fondo NO retrocede, solo Hello Kitty se mueve
                    
                    // Iniciar el reloj cuando Hello Kitty se mueve por primera vez
                    if (!helloKittySeMovio) {
                        helloKittySeMovio = true;
                        relojInicioHorda.restart();
                    }
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                sprite.move(velocidad, 0);
                moviendoDerecha = true;
                
                // Iniciar el reloj cuando Hello Kitty se mueve por primera vez
                if (!helloKittySeMovio) {
                    helloKittySeMovio = true;
                    relojInicioHorda.restart();
                }
                // Mover el fondo solo si no hemos llegado a la meta
                if (distanciaRecorrida < distanciaMeta) {
                    fondoOffset -= velocidadFondo;
                    distanciaRecorrida += velocidadFondo; // Acumular distancia real
                }
            }
        }

        // Salto con espacio (solo si no ha perdido)
        if (!juegoPerdido) {
            bool spacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
            if (spacePressed && !spacePressedBefore && enElSuelo) {
                velocidadY = fuerzaSalto;
                enElSuelo = false;
            }
            spacePressedBefore = spacePressed;
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
        
        // Actualizar posiciones de los zombies con el movimiento del fondo
        for (int i = 0; i < 7; i++) {
            float posZombieX = zombiePosicionesIniciales[i] - distanciaRecorrida;
            float posZombieY = alturaSuelo - alturaUniformeZombies - 50.0f;
            zombieSprites[i].setPosition(posZombieX, posZombieY);
        }
        
        // Actualizar posición de la horda que persigue a Hello Kitty
        if (!juegoPerdido && !juegoGanado) {
            // Verificar si han pasado 3 segundos desde que Hello Kitty se movió
            if (helloKittySeMovio && !hordaIniciada && relojInicioHorda.getElapsedTime().asSeconds() >= 3.0f) {
                hordaIniciada = true;
            }
            
            // Solo mover la horda si ya debe estar activa
            if (hordaIniciada) {
                hordaPosX += hordaVelocidad;
            }
            hordaSprite.setPosition(hordaPosX, hordaPosY);
        }
        
        // Verificar colisiones entre Hello Kitty y los zombies
        if (!juegoGanado && !juegoPerdido) {
            // Crear una zona de colisión más pequeña para Hello Kitty (40% del tamaño original)
            sf::FloatRect originalBounds = sprite.getGlobalBounds();
            float reduccion = 0.3f; // 30% de reducción en cada lado
            sf::FloatRect helloKittyBounds(
                originalBounds.left + originalBounds.width * reduccion,
                originalBounds.top + originalBounds.height * reduccion,
                originalBounds.width * (1.0f - 2.0f * reduccion),
                originalBounds.height * (1.0f - 2.0f * reduccion)
            );
            
            for (int i = 0; i < 7; i++) {
                // También reducir la zona de colisión de los zombies
                sf::FloatRect originalZombieBounds = zombieSprites[i].getGlobalBounds();
                sf::FloatRect zombieBounds(
                    originalZombieBounds.left + originalZombieBounds.width * reduccion,
                    originalZombieBounds.top + originalZombieBounds.height * reduccion,
                    originalZombieBounds.width * (1.0f - 2.0f * reduccion),
                    originalZombieBounds.height * (1.0f - 2.0f * reduccion)
                );
                
                if (helloKittyBounds.intersects(zombieBounds)) {
                    juegoPerdido = true;
                    mostrarDerrota = true; // Mostrar inmediatamente
                    // Guardar la posición de Hello Kitty al momento de la colisión y bajarla 25 píxeles
                    derrotaSprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + 25.0f);
                    break;
                }
            }
            
            // Verificar colisión con la horda
            sf::FloatRect originalHordaBounds = hordaSprite.getGlobalBounds();
            sf::FloatRect hordaBounds(
                originalHordaBounds.left + originalHordaBounds.width * reduccion,
                originalHordaBounds.top + originalHordaBounds.height * reduccion,
                originalHordaBounds.width * (1.0f - 2.0f * reduccion),
                originalHordaBounds.height * (1.0f - 2.0f * reduccion)
            );
            if (helloKittyBounds.intersects(hordaBounds)) {
                juegoPerdido = true;
                mostrarDerrota = true;
                derrotaSprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + 25.0f);
            }
        }
        
        // Verificar colisión entre Hello Kitty y la cabañita
        float posXCabanita = distanciaMeta - distanciaRecorrida;
        float posXHelloKitty = sprite.getPosition().x;
        float anchoHelloKitty = frameWidth * 0.3f;
        float anchoCabanita = 1024.0f * 0.3f; // 307.2 píxeles
        
        // Si Hello Kitty llega a la mitad de la cabañita, desaparecer y cambiar imagen
        if (posXHelloKitty + anchoHelloKitty >= posXCabanita + (anchoCabanita / 2.0f) && !juegoGanado && !juegoPerdido) {
            juegoGanado = true;
            cabanita.setTexture(cabanitaTexture); // Cambiar a cabana cerrada
            relojVictoria.restart(); // Iniciar contador para mostrar interior
        }
        
        // Verificar si han pasado 0.5 segundos desde que ganó
        if (juegoGanado && relojVictoria.getElapsedTime().asSeconds() >= 0.5f) {
            mostrarInterior = true;
        }

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
        
        // Animar la horda continuamente
        if (hordaClock.getElapsedTime().asSeconds() >= frameTime) {
            hordaCurrentFrame = (hordaCurrentFrame + 1) % hordaNumFrames;
            hordaSprite.setTextureRect(sf::IntRect(hordaCurrentFrame * hordaFrameWidth, 0, hordaFrameWidth, hordaFrameHeight));
            hordaClock.restart();
        }

        // Dibujar
        window.clear();
        
        // Dibujar todos los fondos para efecto continuo
        for (int i = 0; i < NUM_FONDOS; i++) {
            window.draw(fondos[i]);
        }
        
        // Dibujar meta
        window.draw(cabanita);
        
        // Dibujar zombies
        for (int i = 0; i < 7; i++) {
            // Solo dibujar zombies que estén dentro de la pantalla visible
            float posX = zombieSprites[i].getPosition().x;
            if (posX > -200 && posX < 1000) {
                window.draw(zombieSprites[i]);
            }
        }
        
        // Dibujar la horda perseguidora
        if (!juegoPerdido && !juegoGanado) {
            window.draw(hordaSprite);
        }
        
        // Dibujar Hello Kitty solo si no ha ganado ni perdido
        if (!juegoGanado && !juegoPerdido) {
            window.draw(sprite);
        }
        
        // Mostrar mensaje de victoria si ganó y han pasado 0.5 segundos
        if (mostrarInterior) {
            window.draw(interiorSprite);
            window.draw(textoVictoria);
        }
        
        // Mostrar mensaje de derrota si perdió y han pasado 0.5 segundos
        if (mostrarDerrota) {
            window.draw(derrotaSprite);
            window.draw(textoDerrota);
            window.draw(textoReiniciar);
        }
        
        window.display();
    }

    return 0;
}
