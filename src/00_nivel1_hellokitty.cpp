#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

double velocidad = 0.05;

int main() {
    // Inicializar semilla aleatoria con valor fijo para posiciones consistentes
    std::srand(42);
    
    sf::RenderWindow window(sf::VideoMode(800, 600), "Hello Kitty Adventure");

    // Cargar y reproducir música de juego
    sf::Music musicaJuego;
    if (!musicaJuego.openFromFile("./assets/music/juego.ogg"))
    {
        return -1;
    }
    musicaJuego.setLoop(true);
    musicaJuego.play();

    // Cargar los fondos
    sf::Texture fondoTexture1;
    if (!fondoTexture1.loadFromFile("assets/images/Fond.png"))
    {
        return -1;
    }
    
    sf::Texture fondoTexture2;
    if (!fondoTexture2.loadFromFile("assets/images/fondo dos.png"))
    {
        return -1;
    }
    
    // Cargar la imagen de la cabaña abierta (inicial)
    sf::Texture cabanaAbiertaTexture;
    if (!cabanaAbiertaTexture.loadFromFile("assets/images/cabana abierta.png"))
    {
        return -1;
    }
    
    // Cargar la imagen de la cabañita cerrada (final)
    sf::Texture cabanitaTexture;
    if (!cabanitaTexture.loadFromFile("assets/images/cabanita.png"))
    {
        return -1;
    }
    
    // Cargar la imagen de interior para la victoria
    sf::Texture interiorTexture;
    if (!interiorTexture.loadFromFile("assets/images/interior.png"))
    {
        return -1;
    }
    
    // Cargar la imagen de Hello Kitty perdedora
    sf::Texture hellokittyPerdedoraTexture;
    if (!hellokittyPerdedoraTexture.loadFromFile("assets/images/hellokitty perdedora.png"))
    {
        return -1;
    }

    // Crear múltiples sprites del fondo para efecto parallax continuo
    const int NUM_FONDOS = 16; // 8 de cada tipo
    sf::Sprite fondos[NUM_FONDOS];
    
    // Escalar los fondos para que tengan exactamente el tamaño de la ventana (800x600)
    float escalaX1 = 800.0f / fondoTexture1.getSize().x;
    float escalaY1 = 600.0f / fondoTexture1.getSize().y;
    float escalaX2 = 800.0f / fondoTexture2.getSize().x;
    float escalaY2 = 600.0f / fondoTexture2.getSize().y;
    
    // Obtener el ancho del fondo escalado (ahora será 800)
    float fondoAncho = 800.0f;
    
    // Configurar todos los fondos (intercalando fond.png y fondo dos.png)
    for (int i = 0; i < NUM_FONDOS; i++) {
        if (i % 2 == 0) {
            // Pares: fond.png
            fondos[i].setTexture(fondoTexture1);
            fondos[i].setScale(escalaX1, escalaY1);
        } else {
            // Impares: fondo dos.png
            fondos[i].setTexture(fondoTexture2);
            fondos[i].setScale(escalaX2, escalaY2);
        }
        fondos[i].setPosition(i * fondoAncho, 0);
    }

    // Cargar la imagen de Hello Kitty
    sf::Texture texture;
    if (!texture.loadFromFile("assets/images/hellokitty.png"))
    {
        return -1;
    }

    // Cargar las texturas de los zombies
    sf::Texture zombieTextures[8];
    std::string zombieNames[8] = {
        "Zombirron", "Zombiano", "Zombilia", "Zombando",
        "Zombiguada", "Zombiscocho", "Zombiela", "Zombiboy"
    };
    
    for (int i = 0; i < 8; i++) {
        if (!zombieTextures[i].loadFromFile("assets/images/" + zombieNames[i] + ".png")) {
            return -1;
        }
    }

    // Crear un sprite y asignarle la textura
    sf::Sprite sprite(texture);
    float posicionInicialX = 100;
    sprite.setScale(0.22f, 0.22f); // Más grande

    sf::Clock clock;
    float frameTime = 0.1f;
    int currentFrame = 0;
    int numFrames = 4;
    int frameWidth = 320;  // Dimensión correcta (1280/4)
    int frameHeight = 612; // Dimensión correcta de hellokitty.png

    // Variables para el salto
    float velocidadY = 0;
    float gravedad = 0.01f;
    float fuerzaSalto = -1.5f;
    float alturaSuelo = 575; // Altura donde está el suelo (subida 4px más)
    bool enElSuelo = true;
    bool spacePressedBefore = false;

    // Variable para el desplazamiento del fondo
    float fondoOffset = 0.0f;
    float velocidadFondo = 0.5f; // Velocidad del fondo mantiene igual
    float distanciaRecorrida = 0.0f; // Distancia total recorrida sin ciclar
    
    // Crear sprites de zombies con posiciones fijas
    sf::Sprite zombieSprites[8];
    float zombiePosicionesIniciales[8];
    float alturaUniformeZombies = 120.0f;
    
    // Posiciones fijas y dispersas para cada zombie
    float posicionesFijas[8] = {
        850.0f, 1100.0f, 1300.0f, 1800.0f,
        2500.0f, 2650.0f, 3400.0f, 4100.0f
    };
    
    for (int i = 0; i < 8; i++) {
        zombieSprites[i].setTexture(zombieTextures[i]);
        
        // Calcular escala para que todos tengan la misma altura
        float alturaZombie = alturaUniformeZombies;
        float escalaUniforme = alturaZombie / zombieTextures[i].getSize().y;
        zombieSprites[i].setScale(escalaUniforme, escalaUniforme);
        
        // Usar posiciones fijas
        zombiePosicionesIniciales[i] = posicionesFijas[i];
        float posicionY = alturaSuelo - alturaZombie - 50.0f;
        
        zombieSprites[i].setPosition(zombiePosicionesIniciales[i], posicionY);
    }
    
    // Crear plataforma del suelo
    sf::RectangleShape plataformaSuelo;
    plataformaSuelo.setSize(sf::Vector2f(800, 40)); // Ancho completo, 40px de alto
    plataformaSuelo.setPosition(0, alturaSuelo);
    plataformaSuelo.setFillColor(sf::Color(101, 67, 33)); // Café oscuro
    
    // Crear meta (cabañita de llegada)
    float anchoCabanita = 1024.0f * 0.5f; // Ancho de la cabañita escalada (512)
    float distanciaMeta = 4800.0f - 800.0f + anchoCabanita; // Meta aparece completa en el borde derecho
    sf::Sprite cabanita(cabanaAbiertaTexture); // Iniciar con cabana abierta
    cabanita.setScale(0.5f, 0.5f); // Escalar la cabañita (1024 * 0.5 = 512)
    cabanita.setPosition(distanciaMeta, alturaSuelo - 450.0f); // Posicionada sobre el suelo
    
    bool juegoGanado = false;
    bool juegoPerdido = false;
    sf::Clock relojVictoria; // Reloj para esperar 2 segundos antes de mostrar interior
    bool mostrarInterior = false;
    float posicionPerdidaX = 0.0f;
    float posicionPerdidaY = 0.0f;
    
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
    textoVictoria.setCharacterSize(40);
    textoVictoria.setFillColor(sf::Color::Red);
    textoVictoria.setPosition(150, 220);
    
    // Crear sprite de Hello Kitty perdedora
    sf::Sprite hellokittyPerdedoraSprite(hellokittyPerdedoraTexture);
    // Escala un poco más grande
    hellokittyPerdedoraSprite.setScale(0.1f, 0.1f);
    
    // Crear texto de derrota
    sf::Text textoDerrota;
    textoDerrota.setFont(zombieFont);
    textoDerrota.setString("te atraparon\nPresiona R para reiniciar");
    textoDerrota.setCharacterSize(50);
    textoDerrota.setFillColor(sf::Color::White);
    textoDerrota.setPosition(150, 200);
    
    // Crear texto para volver al menu (derrota)
    sf::Text textoMenu;
    textoMenu.setFont(zombieFont);
    textoMenu.setString("presiona D para ir al menu");
    textoMenu.setCharacterSize(30);
    textoMenu.setFillColor(sf::Color::White);
    textoMenu.setPosition(180, 560);
    
    // Crear texto para volver al menu (victoria)
    sf::Text textoMenuVictoria;
    textoMenuVictoria.setFont(zombieFont);
    textoMenuVictoria.setString("presiona D para ir al menu");
    textoMenuVictoria.setCharacterSize(25);
    textoMenuVictoria.setFillColor(sf::Color::Black);
    textoMenuVictoria.setPosition(520, 560);
    
    // Ajustar posición inicial de Hello Kitty para estar exactamente sobre el suelo
    float alturaSprite = frameHeight * 0.3f; // 592 * 0.3 = 177.6
    sprite.setPosition(posicionInicialX, alturaSuelo - alturaSprite);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                musicaJuego.stop();
                window.close();
            }
        }

        // Movimiento horizontal
        bool moviendoDerecha = false;
        bool moviendoIzquierda = false;
        
        if (!juegoPerdido && !juegoGanado) {
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
        cabanita.setPosition(distanciaMeta - distanciaRecorrida, alturaSuelo - 450.0f);
        
        // Actualizar posiciones de los zombies con el movimiento del fondo
        for (int i = 0; i < 8; i++) {
            float posZombieX = zombiePosicionesIniciales[i] - distanciaRecorrida;
            float alturaZombie = alturaUniformeZombies;
            float posZombieY = alturaSuelo - alturaZombie - 50.0f;
            zombieSprites[i].setPosition(posZombieX, posZombieY);
        }
        
        // Verificar colisiones entre Hello Kitty y los zombies
        if (!juegoGanado && !juegoPerdido) {
            // Crear una zona de colisión más pequeña para Hello Kitty
            sf::FloatRect originalBounds = sprite.getGlobalBounds();
            float reduccion = 0.3f; // 30% de reducción en cada lado
            sf::FloatRect helloKittyBounds(
                originalBounds.left + originalBounds.width * reduccion,
                originalBounds.top + originalBounds.height * reduccion,
                originalBounds.width * (1.0f - 2.0f * reduccion),
                originalBounds.height * (1.0f - 2.0f * reduccion)
            );
            
            for (int i = 0; i < 8; i++) {
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
                    posicionPerdidaX = sprite.getPosition().x;
                    posicionPerdidaY = sprite.getPosition().y + 25.0f;
                    hellokittyPerdedoraSprite.setPosition(posicionPerdidaX, posicionPerdidaY);
                    break;
                }
            }
        }
        
        // Verificar colisión entre Hello Kitty y la cabañita
        float posXCabanita = distanciaMeta - distanciaRecorrida;
        float posXHelloKitty = sprite.getPosition().x;
        float anchoHelloKitty = frameWidth * 0.3f;
        float anchoCabanita = 1024.0f * 0.5f; // 512 píxeles
        
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
        // Si ya se mostró la pantalla de victoria por 2 segundos, pasar a nivel 2
        if (mostrarInterior && relojVictoria.getElapsedTime().asSeconds() >= 2.5f) {
            musicaJuego.stop();
            window.close();
            system("bin\\00_nivel2_hellokitty.exe");
            return 0;
        }
        
        // Reiniciar nivel si se presiona R cuando está perdido o ganado
        if ((juegoPerdido || juegoGanado) && sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            // Resetear variables del juego
            juegoPerdido = false;
            juegoGanado = false;
            mostrarInterior = false;
            
            // Resetear posición de Hello Kitty
            float alturaSprite = frameHeight * 0.3f;
            sprite.setPosition(posicionInicialX, alturaSuelo - alturaSprite);
            velocidadY = 0;
            enElSuelo = true;
            
            // Resetear fondo y distancia
            fondoOffset = 0.0f;
            distanciaRecorrida = 0.0f;
            
            // Resetear animación
            currentFrame = 0;
            sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
        }
        
        // Volver al menu si se presiona D cuando está perdido o ganado
        if ((juegoPerdido || juegoGanado) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            musicaJuego.stop();
            window.close();
            system("bin\\00_Menu.exe");
        }

        // Salto con espacio
        if (!juegoPerdido) {
            bool spacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
            if (spacePressed && !spacePressedBefore && enElSuelo) {
                velocidadY = fuerzaSalto;
                enElSuelo = false;
            }
            spacePressedBefore = spacePressed;
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

        // Dibujar
        window.clear();
        if (juegoPerdido) {
            // Pantalla de derrota
            for (int i = 0; i < NUM_FONDOS; i++) {
                window.draw(fondos[i]);
            }
            window.draw(plataformaSuelo);
            window.draw(hellokittyPerdedoraSprite);
            window.draw(textoDerrota);
            window.draw(textoMenu);
        } else if (mostrarInterior) {
            // Pantalla de victoria
            window.draw(interiorSprite);
            window.draw(textoVictoria);
            // NO dibujar textoMenu ni textoMenuVictoria
        } else {
            // Juego normal
            for (int i = 0; i < NUM_FONDOS; i++) {
                window.draw(fondos[i]);
            }
            window.draw(plataformaSuelo);
            window.draw(cabanita);
            for (int i = 0; i < 8; i++) {
                float posX = zombieSprites[i].getPosition().x;
                if (posX > -200 && posX < 1000) {
                    window.draw(zombieSprites[i]);
                }
            }
            window.draw(sprite);
        }
        
        window.display();
    }

    return 0;
}
