#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

double velocidad = 0.03;

int main() {
    // Inicializar semilla aleatoria
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snoopy - Nivel 3");

    // Cargar y reproducir música de juego
    sf::Music musicaJuego;
    if (!musicaJuego.openFromFile("./assets/music/juego.ogg"))
    {
        return -1;
    }
    musicaJuego.setLoop(true);
    musicaJuego.play();
    
    // Cargar música de derrota
    sf::Music musicaGoblin;
    if (!musicaGoblin.openFromFile("./assets/music/Goblin_00.ogg"))
    {
        return -1;
    }
    musicaGoblin.setLoop(true);

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

    // Cargar imagen de derrota
    sf::Texture derrotaTexture;
    if (!derrotaTexture.loadFromFile("assets/images/snoopy perdedor.png"))
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

    // Crear sprites de zombies con posiciones fijas
    sf::Sprite zombieSprites[8];
    float zombiePosicionesIniciales[8];
    float alturaUniformeZombies = 100.0f;
    
    // Posiciones fijas y bien distribuidas para cada zombie (alejadas mínimo 100px de la meta en 4800)
    float posicionesFijas[8] = {
        600.0f, 1050.0f, 1500.0f, 1950.0f,
        2400.0f, 2850.0f, 3300.0f, 3750.0f
    };
    
    for (int i = 0; i < 8; i++) {
        zombiePosicionesIniciales[i] = posicionesFijas[i];
    }
    
    for (int i = 0; i < 8; i++) {
        zombieSprites[i].setTexture(zombieTextures[i]);
        
        // Calcular escala - Zombiboy (índice 7) es más grande
        float alturaZombie = (i == 7) ? 115.0f : alturaUniformeZombies; // Zombiboy más grande
        float escalaUniforme = alturaZombie / zombieTextures[i].getSize().y;
        zombieSprites[i].setScale(escalaUniforme, escalaUniforme);
        
        // Usar posiciones fijas
        float posicionY = alturaSuelo - alturaZombie - 45.0f;
        
        zombieSprites[i].setPosition(zombiePosicionesIniciales[i], posicionY);
    }

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
    bool juegoPerdido = false; // Nuevo: estado de derrota
    bool mostrarDerrota = false; // Nuevo: mostrar imagen de derrota
    sf::Clock relojDerrota; // Reloj para la pantalla de derrota
    sf::Clock relojOscilacion; // Reloj para el movimiento de zombies
    
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
    textoVolverMenu.setString("presiona m para ir al menu");
    textoVolverMenu.setCharacterSize(40);
    textoVolverMenu.setFillColor(sf::Color::Black);
    textoVolverMenu.setPosition(380, 540);
    
    // Crear sprite de derrota
    sf::Sprite derrotaSprite(derrotaTexture);
    derrotaSprite.setScale(0.18f, 0.18f); // Ligeramente más pequeño que Snoopy
    
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
    textoReiniciar.setString("Presiona R para reiniciar");
    textoReiniciar.setCharacterSize(50);
    textoReiniciar.setFillColor(sf::Color::White);
    textoReiniciar.setPosition(100, 350);
    
    // Crear texto para volver al menu
    sf::Text textoMenu;
    textoMenu.setFont(zombieFont);
    textoMenu.setString("presiona D para ir al menu");
    textoMenu.setCharacterSize(25);
    textoMenu.setFillColor(sf::Color::Black);
    textoMenu.setPosition(520, 560);
    
    // Ajustar posición inicial de Snoopy para estar exactamente sobre el suelo
    float alturaSprite = frameHeight * 0.2f; // 992 * 0.2 = 198.4
    sprite.setPosition(posicionInicialX, alturaSuelo - alturaSprite);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                musicaJuego.stop();
                window.close();
            }
            
            // Detectar tecla R para reiniciar cuando se muestra la pantalla de derrota
            if (mostrarDerrota && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                // Reiniciar el juego
                juegoPerdido = false;
                mostrarDerrota = false;
                sprite.setPosition(posicionInicialX, alturaSuelo - (frameHeight * 0.2f));
                distanciaRecorrida = 0.0f;
                fondoOffset = 0.0f;
                velocidadY = 0;
                enElSuelo = true;
                // Mantener posiciones fijas de zombies (no regenerar)
                for (int i = 0; i < 8; i++) {
                    zombiePosicionesIniciales[i] = posicionesFijas[i];
                }
                
                // Controlar música
                musicaGoblin.stop();
                musicaJuego.play();
            }
            
            // Detectar tecla D para volver al menu cuando se muestra la pantalla de derrota
            if (mostrarDerrota && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D) {
                musicaGoblin.stop();
                musicaJuego.stop();
                window.close();
                system("bin\\00_Menu.exe");
            }
            
            // Detectar tecla M para volver al menu cuando se muestra la pantalla de amigos
            if (mostrarAmigos && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M) {
                musicaJuego.stop();
                window.close();
                system("bin\\00_Menu.exe");
            }
        }

        // Movimiento horizontal
        bool moviendoDerecha = false;
        bool moviendoIzquierda = false;
        
        if (!juegoPerdido && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            // Solo permitir retroceder si no está en la posición inicial
            if (sprite.getPosition().x > posicionInicialX) {
                sprite.move(-velocidad, 0);
                moviendoIzquierda = true;
                // El fondo NO retrocede, solo Snoopy se mueve
            }
        }
        if (!juegoPerdido && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
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
        
        // Actualizar posiciones de los zombies con el movimiento del fondo
        float tiempoOscilacion = relojOscilacion.getElapsedTime().asSeconds();
        for (int i = 0; i < 8; i++) {
            // Calcular oscilación de 15px hacia adelante y atrás
            float desplazamientoOscilacion = std::sin(tiempoOscilacion * 2.0f + i * 0.5f) * 15.0f;
            float posZombieX = zombiePosicionesIniciales[i] - distanciaRecorrida + desplazamientoOscilacion;
            float alturaZombie = (i == 7) ? 115.0f : alturaUniformeZombies; // Zombiboy más grande
            float posZombieY = alturaSuelo - alturaZombie - 45.0f;
            zombieSprites[i].setPosition(posZombieX, posZombieY);
        }
        
        // Verificar colisiones entre Snoopy y los zombies
        if (!juegoGanado && !juegoPerdido) {
            // Crear una zona de colisión más pequeña para Snoopy
            sf::FloatRect originalBounds = sprite.getGlobalBounds();
            float reduccion = 0.3f; // 30% de reducción en cada lado
            sf::FloatRect snoopyBounds(
                originalBounds.left + originalBounds.width * reduccion,
                originalBounds.top + originalBounds.height * reduccion,
                originalBounds.width * (1.0f - 2.0f * reduccion),
                originalBounds.height * (1.0f - 2.0f * reduccion)
            );
            
            // Verificar colisión con cada zombie
            for (int i = 0; i < 8; i++) {
                sf::FloatRect zombieOriginalBounds = zombieSprites[i].getGlobalBounds();
                sf::FloatRect zombieBounds(
                    zombieOriginalBounds.left + zombieOriginalBounds.width * reduccion,
                    zombieOriginalBounds.top + zombieOriginalBounds.height * reduccion,
                    zombieOriginalBounds.width * (1.0f - 2.0f * reduccion),
                    zombieOriginalBounds.height * (1.0f - 2.0f * reduccion)
                );
                
                if (snoopyBounds.intersects(zombieBounds)) {
                    juegoPerdido = true;
                    musicaJuego.pause();
                    musicaGoblin.play();
                    mostrarDerrota = true;
                    derrotaSprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + 30.0f);
                    break;
                }
            }
        }
        
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
        bool spacePressed = !juegoPerdido && sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
        if (spacePressed && !spacePressedBefore && enElSuelo) {
            velocidadY = fuerzaSalto;
            enElSuelo = false;
        }
        spacePressedBefore = spacePressed;

        // Aplicar gravedad y movimiento vertical
        if (!juegoPerdido) {
            velocidadY += gravedad;
            sprite.move(0, velocidadY);
        }

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
        if (!juegoPerdido && (moviendoDerecha || moviendoIzquierda)) {
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
        
        // Dibujar zombies
        for (int i = 0; i < 8; i++) {
            window.draw(zombieSprites[i]);
        }
        
        // Dibujar Snoopy solo si no ha ganado ni perdido
        if (!juegoGanado && !juegoPerdido) {
            window.draw(sprite);
        }
        
        // Mostrar sprite de derrota si perdió (reemplaza a Snoopy)
        if (juegoPerdido) {
            window.draw(derrotaSprite);
        }
        
        // Mostrar pantalla de derrota si perdió
        if (mostrarDerrota) {
            window.draw(textoDerrota);
            window.draw(textoReiniciar);
            window.draw(textoMenu);
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
