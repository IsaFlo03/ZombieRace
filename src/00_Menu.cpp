#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>

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
    
    // Cargar y reproducir música de intro
    sf::Music musicaIntro;
    if (!musicaIntro.openFromFile("./assets/music/Intro.ogg"))
    {
        return -1;
    }
    musicaIntro.setLoop(true);
    musicaIntro.play();

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

    // === CARGAR RECURSOS DE ZOMBIEPEDIA ===
    // Imagen principal de Zombiepedia
    sf::Texture zombiepediaTexture;
    if (!zombiepediaTexture.loadFromFile("./assets/images/Zombiepedia-Photoroom.png"))
    {
        return -1;
    }
    sf::Sprite zombiepediaSprite(zombiepediaTexture);
    sf::FloatRect zpBounds = zombiepediaSprite.getLocalBounds();
    float zombiepediaScale = std::min((float)windowSize.x / zpBounds.width, 
                                       (float)windowSize.y / zpBounds.height);
    zombiepediaSprite.setScale(zombiepediaScale, zombiepediaScale);
    zombiepediaSprite.setOrigin(zpBounds.width / 2, zpBounds.height / 2);
    zombiepediaSprite.setPosition(windowSize.x / 2, windowSize.y / 2);

    // Cargar todas las páginas de Zombiepedia
    sf::Texture pagina1Texture, pagina2Texture, pagina3Texture, pagina4Texture, pagina5Texture, pagina6Texture;
    sf::Texture pagina7Texture, pagina8Texture, pagina9Texture, pagina10Texture;
    sf::Sprite pagina1Sprite, pagina2Sprite, pagina3Sprite, pagina4Sprite, pagina5Sprite, pagina6Sprite;
    sf::Sprite pagina7Sprite, pagina8Sprite, pagina9Sprite, pagina10Sprite;
    
    if (!pagina1Texture.loadFromFile("./assets/images/Pagina 1.png")) return -1;
    pagina1Sprite.setTexture(pagina1Texture);
    if (!pagina2Texture.loadFromFile("./assets/images/Pagina 2.png")) return -1;
    pagina2Sprite.setTexture(pagina2Texture);
    if (!pagina3Texture.loadFromFile("./assets/images/Pagina 3.png")) return -1;
    pagina3Sprite.setTexture(pagina3Texture);
    if (!pagina4Texture.loadFromFile("./assets/images/Pagina 4.png")) return -1;
    pagina4Sprite.setTexture(pagina4Texture);
    if (!pagina5Texture.loadFromFile("./assets/images/Pagina 5.png")) return -1;
    pagina5Sprite.setTexture(pagina5Texture);
    if (!pagina6Texture.loadFromFile("./assets/images/Pagina 6.png")) return -1;
    pagina6Sprite.setTexture(pagina6Texture);
    if (!pagina7Texture.loadFromFile("./assets/images/Pagina 7.png")) return -1;
    pagina7Sprite.setTexture(pagina7Texture);
    if (!pagina8Texture.loadFromFile("./assets/images/Pagina 8.png")) return -1;
    pagina8Sprite.setTexture(pagina8Texture);
    if (!pagina9Texture.loadFromFile("./assets/images/Pagina 9.png")) return -1;
    pagina9Sprite.setTexture(pagina9Texture);
    if (!pagina10Texture.loadFromFile("./assets/images/Pagina 10.png")) return -1;
    pagina10Sprite.setTexture(pagina10Texture);

    // Botones de navegación de Zombiepedia
    sf::Text zpBotonSiguiente;
    zpBotonSiguiente.setFont(font);
    zpBotonSiguiente.setString(">");
    zpBotonSiguiente.setCharacterSize(60);
    zpBotonSiguiente.setFillColor(sf::Color(0xd7, 0xcc, 0x3a));

    sf::Text zpBotonAnterior;
    zpBotonAnterior.setFont(font);
    zpBotonAnterior.setString("<");
    zpBotonAnterior.setCharacterSize(60);
    zpBotonAnterior.setFillColor(sf::Color(0xd7, 0xcc, 0x3a));

    sf::Text zpBotonVolver;
    zpBotonVolver.setFont(font);
    zpBotonVolver.setString("Menu");
    zpBotonVolver.setCharacterSize(40);
    zpBotonVolver.setFillColor(sf::Color(0x65, 0x09, 0x09));

    // Estados de Zombiepedia
    bool zpEnPortada = true;
    int zpPaginaActual = 1;

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
    float hkScaleX = 0.75f;
    float hkScaleY = 0.75f;
    helloKittySprite.setTextureRect(sf::IntRect(0, 0, 320, 612)); // Primer frame de hellokitty.png
    helloKittySprite.setScale(hkScaleX, hkScaleY);
    float hkScaledWidth = 320 * hkScaleX;
    float hkScaledHeight = 612 * hkScaleY;
    helloKittySprite.setPosition((200 - hkScaledWidth/2), 340 - hkScaledHeight/2);

    // Cargar segunda parte de Snoopy
    sf::Sprite snoopySprite2(snoopyTexture);
    
    // Configurar sprite de Snoopy completo (mitad derecha, centrado, misma altura)
    float snoopyScale = 0.8f;
    float snoopyScaledWidth = 264 * snoopyScale;
    float snoopyTotalHeight = 992 * snoopyScale; // altura total de ambas partes
    float snoopyPosX = 400 + (200 - snoopyScaledWidth/2);
    
    snoopySprite.setTextureRect(sf::IntRect(0, 0, 264, 496)); // Primer frame parte superior
    snoopySprite.setScale(snoopyScale, snoopyScale);
    snoopySprite.setPosition(snoopyPosX, 370 - snoopyTotalHeight/2);
    
    snoopySprite2.setTextureRect(sf::IntRect(0, 496, 264, 496)); // Parte inferior
    snoopySprite2.setScale(snoopyScale, snoopyScale);
    snoopySprite2.setPosition(snoopyPosX, 370 - snoopyTotalHeight/2 + 496 * snoopyScale);

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
        // Actualizar posiciones dinámicas para Zombiepedia
        sf::Vector2u currentWindowSize = window.getSize();
        zpBotonSiguiente.setPosition(currentWindowSize.x - 80, currentWindowSize.y - 100);
        zpBotonAnterior.setPosition(50, currentWindowSize.y - 100);
        zpBotonVolver.setPosition(20, 20);
        
        float mitadAncho = currentWindowSize.x / 2.0f;
        float mitadAlto = currentWindowSize.y / 2.0f;
        
        // Actualizar escalas de páginas
        float scale1 = std::min((float)currentWindowSize.x / pagina1Texture.getSize().x, (float)currentWindowSize.y / pagina1Texture.getSize().y);
        pagina1Sprite.setScale(scale1, scale1);
        pagina1Sprite.setPosition((currentWindowSize.x - pagina1Texture.getSize().x * scale1) / 2, (currentWindowSize.y - pagina1Texture.getSize().y * scale1) / 2);
        
        float scale2 = std::min((float)currentWindowSize.x / pagina2Texture.getSize().x, (float)currentWindowSize.y / pagina2Texture.getSize().y);
        pagina2Sprite.setScale(scale2, scale2);
        pagina2Sprite.setPosition((currentWindowSize.x - pagina2Texture.getSize().x * scale2) / 2, (currentWindowSize.y - pagina2Texture.getSize().y * scale2) / 2);
        
        float scale3 = std::min((float)currentWindowSize.x / pagina3Texture.getSize().x, (float)currentWindowSize.y / pagina3Texture.getSize().y);
        pagina3Sprite.setScale(scale3, scale3);
        pagina3Sprite.setPosition((currentWindowSize.x - pagina3Texture.getSize().x * scale3) / 2, (currentWindowSize.y - pagina3Texture.getSize().y * scale3) / 2);
        
        float scale4 = std::min((float)currentWindowSize.x / pagina4Texture.getSize().x, (float)currentWindowSize.y / pagina4Texture.getSize().y);
        pagina4Sprite.setScale(scale4, scale4);
        pagina4Sprite.setPosition((currentWindowSize.x - pagina4Texture.getSize().x * scale4) / 2, (currentWindowSize.y - pagina4Texture.getSize().y * scale4) / 2);
        
        float scale5 = std::min((float)currentWindowSize.x / pagina5Texture.getSize().x, (float)currentWindowSize.y / pagina5Texture.getSize().y);
        pagina5Sprite.setScale(scale5, scale5);
        pagina5Sprite.setPosition((currentWindowSize.x - pagina5Texture.getSize().x * scale5) / 2, (currentWindowSize.y - pagina5Texture.getSize().y * scale5) / 2);
        
        float scale6 = std::min((float)currentWindowSize.x / pagina6Texture.getSize().x, (float)currentWindowSize.y / pagina6Texture.getSize().y);
        pagina6Sprite.setScale(scale6, scale6);
        pagina6Sprite.setPosition((currentWindowSize.x - pagina6Texture.getSize().x * scale6) / 2, (currentWindowSize.y - pagina6Texture.getSize().y * scale6) / 2);
        
        float scale7 = std::min((float)currentWindowSize.x / pagina7Texture.getSize().x, (float)currentWindowSize.y / pagina7Texture.getSize().y);
        pagina7Sprite.setScale(scale7, scale7);
        pagina7Sprite.setPosition((currentWindowSize.x - pagina7Texture.getSize().x * scale7) / 2, (currentWindowSize.y - pagina7Texture.getSize().y * scale7) / 2);
        
        float scale8 = std::min((float)currentWindowSize.x / pagina8Texture.getSize().x, (float)currentWindowSize.y / pagina8Texture.getSize().y);
        pagina8Sprite.setScale(scale8, scale8);
        pagina8Sprite.setPosition((currentWindowSize.x - pagina8Texture.getSize().x * scale8) / 2, (currentWindowSize.y - pagina8Texture.getSize().y * scale8) / 2);
        
        float scale9 = std::min((float)currentWindowSize.x / pagina9Texture.getSize().x, (float)currentWindowSize.y / pagina9Texture.getSize().y);
        pagina9Sprite.setScale(scale9, scale9);
        pagina9Sprite.setPosition((currentWindowSize.x - pagina9Texture.getSize().x * scale9) / 2, (currentWindowSize.y - pagina9Texture.getSize().y * scale9) / 2);
        
        float scale10 = std::min((float)currentWindowSize.x / pagina10Texture.getSize().x, (float)currentWindowSize.y / pagina10Texture.getSize().y);
        pagina10Sprite.setScale(scale10, scale10);
        pagina10Sprite.setPosition((currentWindowSize.x - pagina10Texture.getSize().x * scale10) / 2, (currentWindowSize.y - pagina10Texture.getSize().y * scale10) / 2);
        
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
                    
                    if (zombiepediaAbierta)
                    {
                        // Lógica de Zombiepedia
                        if (zpEnPortada)
                        {
                            sf::FloatRect zpBounds = zombiepediaSprite.getGlobalBounds();
                            if (zpBounds.contains(mousePos.x, mousePos.y))
                            {
                                zpEnPortada = false;
                                zpPaginaActual = 1;
                            }
                        }
                        else
                        {
                            sf::FloatRect volverBounds = zpBotonVolver.getGlobalBounds();
                            if (volverBounds.contains(mousePos.x, mousePos.y))
                            {
                                if (zpPaginaActual >= 3 && zpPaginaActual <= 6)
                                {
                                    zpPaginaActual = 1;
                                }
                                else if (zpPaginaActual >= 7 && zpPaginaActual <= 10)
                                {
                                    zpPaginaActual = 2;
                                }
                                else
                                {
                                    // Volver al menú principal
                                    zombiepediaAbierta = false;
                                    zpEnPortada = true;
                                    zpPaginaActual = 1;
                                }
                            }
                            else
                            {
                                if (zpPaginaActual == 1)
                                {
                                    sf::FloatRect siguienteBounds = zpBotonSiguiente.getGlobalBounds();
                                    if (siguienteBounds.contains(mousePos.x, mousePos.y))
                                    {
                                        zpPaginaActual = 2;
                                    }
                                    else if (mousePos.x < mitadAncho && mousePos.y < mitadAlto)
                                    {
                                        zpPaginaActual = 3;
                                    }
                                    else if (mousePos.x >= mitadAncho && mousePos.y < mitadAlto)
                                    {
                                        zpPaginaActual = 4;
                                    }
                                    else if (mousePos.x < mitadAncho && mousePos.y >= mitadAlto)
                                    {
                                        zpPaginaActual = 5;
                                    }
                                    else if (mousePos.x >= mitadAncho && mousePos.y >= mitadAlto)
                                    {
                                        zpPaginaActual = 6;
                                    }
                                }
                                else if (zpPaginaActual == 2)
                                {
                                    sf::FloatRect anteriorBounds = zpBotonAnterior.getGlobalBounds();
                                    if (anteriorBounds.contains(mousePos.x, mousePos.y))
                                    {
                                        zpPaginaActual = 1;
                                    }
                                    else if (mousePos.x < mitadAncho && mousePos.y < mitadAlto)
                                    {
                                        zpPaginaActual = 7;
                                    }
                                    else if (mousePos.x >= mitadAncho && mousePos.y < mitadAlto)
                                    {
                                        zpPaginaActual = 8;
                                    }
                                    else if (mousePos.x < mitadAncho && mousePos.y >= mitadAlto)
                                    {
                                        zpPaginaActual = 9;
                                    }
                                    else if (mousePos.x >= mitadAncho && mousePos.y >= mitadAlto)
                                    {
                                        zpPaginaActual = 10;
                                    }
                                }
                            }
                        }
                    }
                    else if (!seleccionPersonaje && !zombiepediaAbierta)
                    {
                        sf::FloatRect playBounds = botonPlay.getGlobalBounds();
                        sf::FloatRect zombiepediaBounds = botonZombiepedia.getGlobalBounds();
                        
                        if (playBounds.contains(mousePos.x, mousePos.y))
                        {
                            seleccionPersonaje = true;
                        }
                        if (zombiepediaBounds.contains(mousePos.x, mousePos.y))
                        {
                            system("bin\\12_Zombiepedia.exe");
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
                            musicaIntro.stop();
                            window.close();
                            system("bin\\00_nivel1_hellokitty.exe");
                            return 0;
                        }
                        if (snoopyBounds.contains(mousePos.x, mousePos.y))
                        {
                            personajeSeleccionado = "snoopy";
                            musicaIntro.stop();
                            window.close();
                            system("bin\\00_nivel1_snoopy.exe");
                            return 0;
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
        else if (zombiepediaAbierta)
        {
            // Mostrar Zombiepedia
            window.clear(sf::Color::Black);
            window.draw(fondoSprite);
            
            if (zpEnPortada)
            {
                window.draw(zombiepediaSprite);
            }
            else
            {
                // Dibujar la página actual
                if (zpPaginaActual == 1) window.draw(pagina1Sprite);
                else if (zpPaginaActual == 2) window.draw(pagina2Sprite);
                else if (zpPaginaActual == 3) window.draw(pagina3Sprite);
                else if (zpPaginaActual == 4) window.draw(pagina4Sprite);
                else if (zpPaginaActual == 5) window.draw(pagina5Sprite);
                else if (zpPaginaActual == 6) window.draw(pagina6Sprite);
                else if (zpPaginaActual == 7) window.draw(pagina7Sprite);
                else if (zpPaginaActual == 8) window.draw(pagina8Sprite);
                else if (zpPaginaActual == 9) window.draw(pagina9Sprite);
                else if (zpPaginaActual == 10) window.draw(pagina10Sprite);
                
                // Dibujar botones de navegación según la página
                if (zpPaginaActual == 1)
                {
                    window.draw(zpBotonSiguiente);
                }
                else if (zpPaginaActual == 2)
                {
                    window.draw(zpBotonAnterior);
                }
                
                // Siempre dibujar el botón volver
                window.draw(zpBotonVolver);
            }
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
