#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Zombie Mayhem - Menu");

    // Cargar la imagen de fondo
    sf::Texture fondoTexture;
    if (!fondoTexture.loadFromFile("./assets/images/Fondo menu.png"))
    {
        return -1;
    }
    sf::Sprite fondoSprite(fondoTexture);
    
    // Escalar la imagen al tamaño de la ventana
    sf::Vector2u textureSize = fondoTexture.getSize();
    sf::Vector2u windowSize = window.getSize();
    float scaleX = (float)windowSize.x / textureSize.x;
    float scaleY = (float)windowSize.y / textureSize.y;
    fondoSprite.setScale(scaleX, scaleY);

    // Cargar la fuente Zombie Hunger
    sf::Font font;
    if (!font.loadFromFile("./assets/fonts/Zombie_Hunger[1].ttf"))
    {
        return -1;
    }

    // Cargar imágenes de personajes
    sf::Texture helloKittyTexture;
    if (!helloKittyTexture.loadFromFile("./assets/images/hellokitty.png"))
    {
        return -1;
    }
    sf::Sprite helloKittySprite(helloKittyTexture);
    
    sf::Texture snoopyTexture;
    if (!snoopyTexture.loadFromFile("./assets/images/snoopy.png"))
    {
        return -1;
    }
    sf::Sprite snoopySprite(snoopyTexture);

    // Título del juego
    sf::Text titulo;
    titulo.setFont(font);
    titulo.setString("Zombie Mayhem");
    titulo.setCharacterSize(80);
    titulo.setFillColor(sf::Color(0x65, 0x09, 0x09));
    
    // Centrar el título
    sf::FloatRect tituloRect = titulo.getLocalBounds();
    titulo.setOrigin(tituloRect.left + tituloRect.width/2.0f, tituloRect.top + tituloRect.height/2.0f);
    titulo.setPosition(400, 150);

    // Botón de Play
    sf::Text botonPlay;
    botonPlay.setFont(font);
    botonPlay.setString("PLAY");
    botonPlay.setCharacterSize(60);
    botonPlay.setFillColor(sf::Color(0xd7, 0xcc, 0x3a));
    
    // Centrar el texto del botón
    sf::FloatRect playRect = botonPlay.getLocalBounds();
    botonPlay.setOrigin(playRect.left + playRect.width/2.0f, playRect.top + playRect.height/2.0f);
    botonPlay.setPosition(400, 350);

    // Rectángulo para el botón
    sf::RectangleShape rectanguloBoton;
    rectanguloBoton.setSize(sf::Vector2f(200, 80));
    rectanguloBoton.setOrigin(100, 40);
    rectanguloBoton.setPosition(400, 350);
    rectanguloBoton.setFillColor(sf::Color::Transparent);
    rectanguloBoton.setOutlineColor(sf::Color(0xd7, 0xcc, 0x3a));
    rectanguloBoton.setOutlineThickness(3);

    // Botón de Zombiepedia
    sf::Text botonZombiepedia;
    botonZombiepedia.setFont(font);
    botonZombiepedia.setString("Zombiepedia");
    botonZombiepedia.setCharacterSize(50);
    botonZombiepedia.setFillColor(sf::Color(0x8B, 0x45, 0x13));
    
    // Centrar el texto del botón
    sf::FloatRect zombiepediaRect = botonZombiepedia.getLocalBounds();
    botonZombiepedia.setOrigin(zombiepediaRect.left + zombiepediaRect.width/2.0f, zombiepediaRect.top + zombiepediaRect.height/2.0f);
    botonZombiepedia.setPosition(400, 470);

    // Rectángulo para el botón Zombiepedia
    sf::RectangleShape rectanguloZombiepedia;
    rectanguloZombiepedia.setSize(sf::Vector2f(250, 80));
    rectanguloZombiepedia.setOrigin(125, 40);
    rectanguloZombiepedia.setPosition(400, 470);
    rectanguloZombiepedia.setFillColor(sf::Color::Transparent);
    rectanguloZombiepedia.setOutlineColor(sf::Color(0x8B, 0x45, 0x13));
    rectanguloZombiepedia.setOutlineThickness(3);

    bool juegoIniciado = false;
    bool zombiepediaAbierta = false;
    bool seleccionPersonaje = false;
    std::string personajeSeleccionado = "";

    // Textos para selección de personaje
    sf::Text tituloSeleccion;
    tituloSeleccion.setFont(font);
    tituloSeleccion.setString("Elige tu personaje");
    tituloSeleccion.setCharacterSize(60);
    tituloSeleccion.setFillColor(sf::Color(0x65, 0x09, 0x09));
    sf::FloatRect seleccionRect = tituloSeleccion.getLocalBounds();
    tituloSeleccion.setOrigin(seleccionRect.left + seleccionRect.width/2.0f, seleccionRect.top + seleccionRect.height/2.0f);
    tituloSeleccion.setPosition(400, 60);

    // Configurar sprite de Hello Kitty (mitad izquierda, centrado)
    float hkScale = 1.1f;
    helloKittySprite.setTextureRect(sf::IntRect(0, 0, 216, 592)); // Primer frame
    helloKittySprite.setScale(hkScale, hkScale);
    float hkScaledWidth = 216 * hkScale;
    float hkScaledHeight = 592 * hkScale;
    helloKittySprite.setPosition((200 - hkScaledWidth/2), 350 - hkScaledHeight/2);

    // Cargar segunda parte de Snoopy
    sf::Sprite snoopySprite2(snoopyTexture);
    
    // Configurar sprite de Snoopy completo (mitad derecha, centrado, misma altura)
    float snoopyScale = 0.8f;
    float snoopyScaledWidth = 264 * snoopyScale;
    float snoopyTotalHeight = 992 * snoopyScale; // altura total de ambas partes
    float snoopyPosX = 400 + (200 - snoopyScaledWidth/2);
    
    snoopySprite.setTextureRect(sf::IntRect(0, 0, 264, 496)); // Primer frame parte superior
    snoopySprite.setScale(snoopyScale, snoopyScale);
    snoopySprite.setPosition(snoopyPosX, 300 - snoopyTotalHeight/2);
    
    snoopySprite2.setTextureRect(sf::IntRect(0, 496, 264, 496)); // Parte inferior
    snoopySprite2.setScale(snoopyScale, snoopyScale);
    snoopySprite2.setPosition(snoopyPosX, 300 - snoopyTotalHeight/2 + 496 * snoopyScale);

    sf::Text opcionHelloKitty;
    opcionHelloKitty.setFont(font);
    opcionHelloKitty.setString("Hello Kitty");
    opcionHelloKitty.setCharacterSize(55);
    opcionHelloKitty.setFillColor(sf::Color(0xd7, 0xcc, 0x3a));
    sf::FloatRect hkRect = opcionHelloKitty.getLocalBounds();
    opcionHelloKitty.setOrigin(hkRect.left + hkRect.width/2.0f, hkRect.top + hkRect.height/2.0f);
    opcionHelloKitty.setPosition(400, 320);

    sf::Text opcionSnoopy;
    opcionSnoopy.setFont(font);
    opcionSnoopy.setString("Snoopy");
    opcionSnoopy.setCharacterSize(55);
    opcionSnoopy.setFillColor(sf::Color(0xd7, 0xcc, 0x3a));
    sf::FloatRect snoopyRect = opcionSnoopy.getLocalBounds();
    opcionSnoopy.setOrigin(snoopyRect.left + snoopyRect.width/2.0f, snoopyRect.top + snoopyRect.height/2.0f);
    opcionSnoopy.setPosition(400, 420);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            // Detectar clic en el botón Play
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    
                    if (!seleccionPersonaje && !zombiepediaAbierta)
                    {
                        sf::FloatRect playBounds = botonPlay.getGlobalBounds();
                        sf::FloatRect zombiepediaBounds = botonZombiepedia.getGlobalBounds();
                        
                        if (playBounds.contains(mousePos.x, mousePos.y))
                        {
                            seleccionPersonaje = true;
                        }
                        if (zombiepediaBounds.contains(mousePos.x, mousePos.y))
                        {
                            zombiepediaAbierta = true;
                        }
                    }
                    else if (seleccionPersonaje)
                    {
                        sf::FloatRect hkBounds = helloKittySprite.getGlobalBounds();
                        // Área combinada de Snoopy (ambas partes)
                        sf::FloatRect snoopyBounds(snoopySprite.getGlobalBounds().left,
                                                   snoopySprite.getGlobalBounds().top,
                                                   snoopySprite.getGlobalBounds().width,
                                                   snoopySprite.getGlobalBounds().height + snoopySprite2.getGlobalBounds().height);
                        
                        if (hkBounds.contains(mousePos.x, mousePos.y))
                        {
                            personajeSeleccionado = "hellokitty";
                            juegoIniciado = true;
                            seleccionPersonaje = false;
                        }
                        if (snoopyBounds.contains(mousePos.x, mousePos.y))
                        {
                            personajeSeleccionado = "snoopy";
                            juegoIniciado = true;
                            seleccionPersonaje = false;
                        }
                    }
                }
            }
        }

        // Efecto hover en el botón
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        
        if (!seleccionPersonaje && !zombiepediaAbierta)
        {
            // Para detectar hover en PLAY, usar las dimensiones del texto
            sf::FloatRect playBounds = botonPlay.getGlobalBounds();
            if (playBounds.contains(mousePos.x, mousePos.y))
            {
                botonPlay.setFillColor(sf::Color::Yellow);
            }
            else
            {
                botonPlay.setFillColor(sf::Color(0xd7, 0xcc, 0x3a));
            }

            // Efecto hover en el botón Zombiepedia
            sf::FloatRect zombiepediaBounds = botonZombiepedia.getGlobalBounds();
            if (zombiepediaBounds.contains(mousePos.x, mousePos.y))
            {
                botonZombiepedia.setFillColor(sf::Color(0xCD, 0x85, 0x3F));
            }
            else
            {
                botonZombiepedia.setFillColor(sf::Color(0x8B, 0x45, 0x13));
            }
        }
        else if (seleccionPersonaje)
        {
            // Efecto hover en Hello Kitty
            sf::FloatRect hkBounds = helloKittySprite.getGlobalBounds();
            if (hkBounds.contains(mousePos.x, mousePos.y))
            {
                helloKittySprite.setColor(sf::Color(255, 255, 200)); // Tinte amarillento
            }
            else
            {
                helloKittySprite.setColor(sf::Color::White);
            }

            // Efecto hover en Snoopy (ambas partes)
            sf::FloatRect snoopyBounds(snoopySprite.getGlobalBounds().left,
                                       snoopySprite.getGlobalBounds().top,
                                       snoopySprite.getGlobalBounds().width,
                                       snoopySprite.getGlobalBounds().height + snoopySprite2.getGlobalBounds().height);
            if (snoopyBounds.contains(mousePos.x, mousePos.y))
            {
                snoopySprite.setColor(sf::Color(255, 255, 200)); // Tinte amarillento
                snoopySprite2.setColor(sf::Color(255, 255, 200));
            }
            else
            {
                snoopySprite.setColor(sf::Color::White);
                snoopySprite2.setColor(sf::Color::White);
            }
        }

        // Si el juego ha iniciado, mostrar pantalla vacía para el juego
        if (juegoIniciado)
        {
            window.clear(sf::Color::Black);
            
            // Aquí irá el contenido del juego
            sf::Text mensajeJuego;
            mensajeJuego.setFont(font);
            mensajeJuego.setString("Jugando con: " + personajeSeleccionado);
            mensajeJuego.setCharacterSize(40);
            mensajeJuego.setFillColor(sf::Color::White);
            mensajeJuego.setPosition(150, 270);
            
            window.draw(mensajeJuego);
        }
        else if (seleccionPersonaje)
        {
            // Mostrar pantalla de selección de personaje
            window.clear(sf::Color::Black);
            window.draw(fondoSprite);
            window.draw(tituloSeleccion);
            window.draw(helloKittySprite);
            window.draw(snoopySprite);
            window.draw(snoopySprite2);
        }
        else if (zombiepediaAbierta)
        {
            // Mostrar Zombiepedia
            window.clear(sf::Color::Black);
            
            sf::Text mensajeZombiepedia;
            mensajeZombiepedia.setFont(font);
            mensajeZombiepedia.setString("Zombiepedia");
            mensajeZombiepedia.setCharacterSize(60);
            mensajeZombiepedia.setFillColor(sf::Color(0xd7, 0xcc, 0x3a));
            mensajeZombiepedia.setPosition(200, 270);
            
            window.draw(mensajeZombiepedia);
        }
        else
        {
            // Mostrar el menú
            window.clear(sf::Color::Black);
            window.draw(fondoSprite);
            window.draw(titulo);
            window.draw(botonPlay);
            window.draw(botonZombiepedia);
        }

        window.display();
    }

    return 0;
}
