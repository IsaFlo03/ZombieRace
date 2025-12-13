#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Zombiepedia");

    // Cargar fondo de menú
    sf::Texture fondoTexture;
    if (!fondoTexture.loadFromFile("./assets/images/Fondo menu.png"))
    {
        return -1;
    }
    sf::Sprite fondoSprite(fondoTexture);
    
    // Escalar el fondo al tamaño de la ventana
    sf::Vector2u fondoSize = fondoTexture.getSize();
    sf::Vector2u windowSize = window.getSize();
    float fondoScaleX = (float)windowSize.x / fondoSize.x;
    float fondoScaleY = (float)windowSize.y / fondoSize.y;
    fondoSprite.setScale(fondoScaleX, fondoScaleY);

    // Cargar imagen principal de Zombiepedia
    sf::Texture zombiepediaTexture;
    if (!zombiepediaTexture.loadFromFile("./assets/images/Zombiepedia-Photoroom.png"))
    {
        return -1;
    }
    sf::Sprite zombiepediaSprite(zombiepediaTexture);
    
    // Escalar y centrar la imagen de Zombiepedia
    sf::FloatRect bounds = zombiepediaSprite.getLocalBounds();
    float zombiepediaScale = std::min((float)windowSize.x / bounds.width, 
                                       (float)windowSize.y / bounds.height);
    zombiepediaSprite.setScale(zombiepediaScale, zombiepediaScale);
    zombiepediaSprite.setOrigin(bounds.width / 2, bounds.height / 2);
    zombiepediaSprite.setPosition(windowSize.x / 2, windowSize.y / 2);

    // Cargar páginas
    sf::Texture pagina1Texture;
    if (!pagina1Texture.loadFromFile("./assets/images/Pagina 1.png"))
    {
        return -1;
    }
    sf::Sprite pagina1Sprite(pagina1Texture);
    
    // Escalar página 1 manteniendo proporción y añadir márgenes
    sf::Vector2u p1Size = pagina1Texture.getSize();
    float margen = 20.0f; // Margen de 20 píxeles
    float scale1 = std::min((float)(windowSize.x - 2 * margen) / p1Size.x, (float)(windowSize.y - 2 * margen) / p1Size.y);
    pagina1Sprite.setScale(scale1, scale1);
    // Centrar con márgenes
    pagina1Sprite.setPosition((windowSize.x - p1Size.x * scale1) / 2, (windowSize.y - p1Size.y * scale1) / 2);

    sf::Texture pagina2Texture;
    if (!pagina2Texture.loadFromFile("./assets/images/Pagina 2.png"))
    {
        return -1;
    }
    sf::Sprite pagina2Sprite(pagina2Texture);
    
    // Escalar página 2 manteniendo proporción y añadir márgenes
    sf::Vector2u p2Size = pagina2Texture.getSize();
    float scale2 = std::min((float)(windowSize.x - 2 * margen) / p2Size.x, (float)(windowSize.y - 2 * margen) / p2Size.y);
    pagina2Sprite.setScale(scale2, scale2);
    pagina2Sprite.setPosition((windowSize.x - p2Size.x * scale2) / 2, (windowSize.y - p2Size.y * scale2) / 2);

    // Cargar páginas de información (3, 4, 5, 6)
    sf::Texture pagina3Texture, pagina4Texture, pagina5Texture, pagina6Texture;
    sf::Sprite pagina3Sprite, pagina4Sprite, pagina5Sprite, pagina6Sprite;
    
    if (!pagina3Texture.loadFromFile("./assets/images/Pagina 3.png")) return -1;
    pagina3Sprite.setTexture(pagina3Texture);
    float scale3 = std::min((float)(windowSize.x - 2 * margen) / pagina3Texture.getSize().x, (float)(windowSize.y - 2 * margen) / pagina3Texture.getSize().y);
    pagina3Sprite.setScale(scale3, scale3);
    pagina3Sprite.setPosition((windowSize.x - pagina3Texture.getSize().x * scale3) / 2, (windowSize.y - pagina3Texture.getSize().y * scale3) / 2);
    
    if (!pagina4Texture.loadFromFile("./assets/images/Pagina 4.png")) return -1;
    pagina4Sprite.setTexture(pagina4Texture);
    float scale4 = std::min((float)(windowSize.x - 2 * margen) / pagina4Texture.getSize().x, (float)(windowSize.y - 2 * margen) / pagina4Texture.getSize().y);
    pagina4Sprite.setScale(scale4, scale4);
    pagina4Sprite.setPosition((windowSize.x - pagina4Texture.getSize().x * scale4) / 2, (windowSize.y - pagina4Texture.getSize().y * scale4) / 2);
    
    if (!pagina5Texture.loadFromFile("./assets/images/Pagina 5.png")) return -1;
    pagina5Sprite.setTexture(pagina5Texture);
    float scale5 = std::min((float)(windowSize.x - 2 * margen) / pagina5Texture.getSize().x, (float)(windowSize.y - 2 * margen) / pagina5Texture.getSize().y);
    pagina5Sprite.setScale(scale5, scale5);
    pagina5Sprite.setPosition((windowSize.x - pagina5Texture.getSize().x * scale5) / 2, (windowSize.y - pagina5Texture.getSize().y * scale5) / 2);
    
    if (!pagina6Texture.loadFromFile("./assets/images/Pagina 6.png")) return -1;
    pagina6Sprite.setTexture(pagina6Texture);
    float scale6 = std::min((float)(windowSize.x - 2 * margen) / pagina6Texture.getSize().x, (float)(windowSize.y - 2 * margen) / pagina6Texture.getSize().y);
    pagina6Sprite.setScale(scale6, scale6);
    pagina6Sprite.setPosition((windowSize.x - pagina6Texture.getSize().x * scale6) / 2, (windowSize.y - pagina6Texture.getSize().y * scale6) / 2);

    // Cargar páginas de información (7, 8, 9, 10)
    sf::Texture pagina7Texture, pagina8Texture, pagina9Texture, pagina10Texture;
    sf::Sprite pagina7Sprite, pagina8Sprite, pagina9Sprite, pagina10Sprite;
    
    if (!pagina7Texture.loadFromFile("./assets/images/Pagina 7.png")) return -1;
    pagina7Sprite.setTexture(pagina7Texture);
    float scale7 = std::min((float)(windowSize.x - 2 * margen) / pagina7Texture.getSize().x, (float)(windowSize.y - 2 * margen) / pagina7Texture.getSize().y);
    pagina7Sprite.setScale(scale7, scale7);
    pagina7Sprite.setPosition((windowSize.x - pagina7Texture.getSize().x * scale7) / 2, (windowSize.y - pagina7Texture.getSize().y * scale7) / 2);
    
    if (!pagina8Texture.loadFromFile("./assets/images/Pagina 8.png")) return -1;
    pagina8Sprite.setTexture(pagina8Texture);
    float scale8 = std::min((float)(windowSize.x - 2 * margen) / pagina8Texture.getSize().x, (float)(windowSize.y - 2 * margen) / pagina8Texture.getSize().y);
    pagina8Sprite.setScale(scale8, scale8);
    pagina8Sprite.setPosition((windowSize.x - pagina8Texture.getSize().x * scale8) / 2, (windowSize.y - pagina8Texture.getSize().y * scale8) / 2);
    
    if (!pagina9Texture.loadFromFile("./assets/images/Pagina 9.png")) return -1;
    pagina9Sprite.setTexture(pagina9Texture);
    float scale9 = std::min((float)(windowSize.x - 2 * margen) / pagina9Texture.getSize().x, (float)(windowSize.y - 2 * margen) / pagina9Texture.getSize().y);
    pagina9Sprite.setScale(scale9, scale9);
    pagina9Sprite.setPosition((windowSize.x - pagina9Texture.getSize().x * scale9) / 2, (windowSize.y - pagina9Texture.getSize().y * scale9) / 2);
    
    if (!pagina10Texture.loadFromFile("./assets/images/Pagina 10.png")) return -1;
    pagina10Sprite.setTexture(pagina10Texture);
    float scale10 = std::min((float)(windowSize.x - 2 * margen) / pagina10Texture.getSize().x, (float)(windowSize.y - 2 * margen) / pagina10Texture.getSize().y);
    pagina10Sprite.setScale(scale10, scale10);
    pagina10Sprite.setPosition((windowSize.x - pagina10Texture.getSize().x * scale10) / 2, (windowSize.y - pagina10Texture.getSize().y * scale10) / 2);

    // Cargar la fuente
    sf::Font font;
    if (!font.loadFromFile("./assets/fonts/Zombie_Hunger[1].ttf"))
    {
        return -1;
    }

    // Texto para instrucciones de navegación
    sf::Text textoNavegacion;
    textoNavegacion.setFont(font);
    textoNavegacion.setString("usa las flechitas para viajar entre paginas");
    textoNavegacion.setCharacterSize(30);
    textoNavegacion.setFillColor(sf::Color::Black);
    textoNavegacion.setPosition(windowSize.x / 2 - 250, windowSize.y - 50);

    sf::Text botonVolver;
    botonVolver.setFont(font);
    botonVolver.setString("Volver");
    botonVolver.setCharacterSize(40);
    botonVolver.setFillColor(sf::Color(0x65, 0x09, 0x09));
    botonVolver.setPosition(20, 20);
    
    // Texto "presiona A" en la portada
    sf::Text textoPresionaA;
    textoPresionaA.setFont(font);
    textoPresionaA.setString("presiona A");
    textoPresionaA.setCharacterSize(50);
    textoPresionaA.setFillColor(sf::Color::Black);
    textoPresionaA.setPosition(windowSize.x / 2 - 100, windowSize.y - 80);
    
    // Botón "volver" en la portada
    sf::Text botonVolverPortada;
    botonVolverPortada.setFont(font);
    botonVolverPortada.setString("volver");
    botonVolverPortada.setCharacterSize(35);
    botonVolverPortada.setFillColor(sf::Color(0x65, 0x09, 0x09));
    botonVolverPortada.setPosition(20, 20);

    // Estados
    bool enPortada = true;
    int paginaActual = 1; // 1-10
    
    // Definir cuadrantes de la pantalla
    float mitadAncho = windowSize.x / 2.0f;
    float mitadAlto = windowSize.y / 2.0f;
    
    // Cuadrantes para página 1
    sf::FloatRect cuadranteSuperiorIzq(0, 0, mitadAncho, mitadAlto);           // Página 3
    sf::FloatRect cuadranteSuperiorDer(mitadAncho, 0, mitadAncho, mitadAlto);  // Página 4
    sf::FloatRect cuadranteInferiorIzq(0, mitadAlto, mitadAncho, mitadAlto);   // Página 5
    sf::FloatRect cuadranteInferiorDer(mitadAncho, mitadAlto, mitadAncho, mitadAlto); // Página 6
    
    // Cuadrantes para página 2
    sf::FloatRect cuadranteSuperiorIzqP2(0, 0, mitadAncho, mitadAlto);           // Página 7
    sf::FloatRect cuadranteSuperiorDerP2(mitadAncho, 0, mitadAncho, mitadAlto);  // Página 8
    sf::FloatRect cuadranteInferiorIzqP2(0, mitadAlto, mitadAncho, mitadAlto);   // Página 9
    sf::FloatRect cuadranteInferiorDerP2(mitadAncho, mitadAlto, mitadAncho, mitadAlto); // Página 10

    while (window.isOpen())
    {
        // Actualizar tamaño de ventana y posiciones
        sf::Vector2u currentWindowSize = window.getSize();
        
        // Actualizar cuadrantes
        float mitadAncho = currentWindowSize.x / 2.0f;
        float mitadAlto = currentWindowSize.y / 2.0f;
        
        sf::FloatRect cuadranteSuperiorIzq(0, 0, mitadAncho, mitadAlto);
        sf::FloatRect cuadranteSuperiorDer(mitadAncho, 0, mitadAncho, mitadAlto);
        sf::FloatRect cuadranteInferiorIzq(0, mitadAlto, mitadAncho, mitadAlto);
        sf::FloatRect cuadranteInferiorDer(mitadAncho, mitadAlto, mitadAncho, mitadAlto);
        
        sf::FloatRect cuadranteSuperiorIzqP2(0, 0, mitadAncho, mitadAlto);
        sf::FloatRect cuadranteSuperiorDerP2(mitadAncho, 0, mitadAncho, mitadAlto);
        sf::FloatRect cuadranteInferiorIzqP2(0, mitadAlto, mitadAncho, mitadAlto);
        sf::FloatRect cuadranteInferiorDerP2(mitadAncho, mitadAlto, mitadAncho, mitadAlto);
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            // Detectar tecla A para abrir la Zombiepedia desde la portada
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A && enPortada)
            {
                enPortada = false;
                paginaActual = 1;
            }
            
            // Navegación con flechas del teclado
            if (event.type == sf::Event::KeyPressed && !enPortada)
            {
                if (event.key.code == sf::Keyboard::Right)
                {
                    // Flecha derecha: siguiente página
                    if (paginaActual == 1)
                    {
                        paginaActual = 2;
                    }
                }
                else if (event.key.code == sf::Keyboard::Left)
                {
                    // Flecha izquierda: página anterior
                    if (paginaActual == 2)
                    {
                        paginaActual = 1;
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

                    // Si estamos en la portada
                    if (enPortada)
                    {
                        // Detectar clic en botón volver de la portada
                        sf::FloatRect volverPortadaBounds = botonVolverPortada.getGlobalBounds();
                        if (volverPortadaBounds.contains(mousePos))
                        {
                            window.close();
                            system("bin\\00_Menu.exe");
                        }
                    }
                    else
                    {
                        // Botón volver (verificar primero antes de otros clics)
                        sf::FloatRect volverBounds = botonVolver.getGlobalBounds();
                        if (volverBounds.contains(mousePos))
                        {
                            // Si estamos en páginas 3-6, volver a página 1
                            if (paginaActual >= 3 && paginaActual <= 6)
                            {
                                paginaActual = 1;
                            }
                            // Si estamos en páginas 7-10, volver a página 2
                            else if (paginaActual >= 7 && paginaActual <= 10)
                            {
                                paginaActual = 2;
                            }
                            else
                            {
                                enPortada = true;
                            }
                        }
                        else
                        {
                            // En página 1
                            if (paginaActual == 1)
                            {
                                // Detectar clics en cuadrantes
                                if (cuadranteSuperiorIzq.contains(mousePos))
                                {
                                    paginaActual = 3;
                                }
                                else if (cuadranteSuperiorDer.contains(mousePos))
                                {
                                    paginaActual = 4;
                                }
                                else if (cuadranteInferiorIzq.contains(mousePos))
                                {
                                    paginaActual = 5;
                                }
                                else if (cuadranteInferiorDer.contains(mousePos))
                                {
                                    paginaActual = 6;
                                }
                            }
                            // En página 2
                            else if (paginaActual == 2)
                            {
                                // Detectar clics en cuadrantes
                                if (cuadranteSuperiorIzqP2.contains(mousePos))
                                {
                                    paginaActual = 7;
                                }
                                else if (cuadranteSuperiorDerP2.contains(mousePos))
                                {
                                    paginaActual = 8;
                                }
                                else if (cuadranteInferiorIzqP2.contains(mousePos))
                                {
                                    paginaActual = 9;
                                }
                                else if (cuadranteInferiorDerP2.contains(mousePos))
                                {
                                    paginaActual = 10;
                                }
                            }
                        }
                    }
                }
            }

            // Efecto hover en portada
            if (event.type == sf::Event::MouseMoved && enPortada)
            {
                sf::Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);
                
                // Hover en botón volver de la portada
                sf::FloatRect volverPortadaBounds = botonVolverPortada.getGlobalBounds();
                if (volverPortadaBounds.contains(mousePos))
                {
                    botonVolverPortada.setFillColor(sf::Color::Red);
                }
                else
                {
                    botonVolverPortada.setFillColor(sf::Color(0x65, 0x09, 0x09));
                }
                
                // Hover en imagen de Zombiepedia
                sf::FloatRect zombiepediaBounds = zombiepediaSprite.getGlobalBounds();
                if (zombiepediaBounds.contains(mousePos))
                {
                    float newScale = zombiepediaScale * 1.05f;
                    zombiepediaSprite.setScale(newScale, newScale);
                }
                else
                {
                    zombiepediaSprite.setScale(zombiepediaScale, zombiepediaScale);
                }
            }

            // Efectos hover en botón volver
            if (event.type == sf::Event::MouseMoved && !enPortada)
            {
                sf::Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);
                
                // Hover botón volver
                sf::FloatRect volverBounds = botonVolver.getGlobalBounds();
                if (volverBounds.contains(mousePos))
                {
                    botonVolver.setFillColor(sf::Color::Red);
                }
                else
                {
                    botonVolver.setFillColor(sf::Color(0x65, 0x09, 0x09));
                }
            }
        }

        window.clear(sf::Color::White);

        // Dibujar fondo siempre
        window.draw(fondoSprite);

        if (enPortada)
        {
            // Mostrar imagen de portada
            window.draw(zombiepediaSprite);
            window.draw(textoPresionaA);
            window.draw(botonVolverPortada);
        }
        else
        {
            // Mostrar la página actual
            if (paginaActual == 1)
            {
                window.draw(pagina1Sprite);
                window.draw(textoNavegacion);
            }
            else if (paginaActual == 2)
            {
                window.draw(pagina2Sprite);
                window.draw(textoNavegacion);
            }
            else if (paginaActual == 3)
            {
                window.draw(pagina3Sprite);
            }
            else if (paginaActual == 4)
            {
                window.draw(pagina4Sprite);
            }
            else if (paginaActual == 5)
            {
                window.draw(pagina5Sprite);
            }
            else if (paginaActual == 6)
            {
                window.draw(pagina6Sprite);
            }
            else if (paginaActual == 7)
            {
                window.draw(pagina7Sprite);
            }
            else if (paginaActual == 8)
            {
                window.draw(pagina8Sprite);
            }
            else if (paginaActual == 9)
            {
                window.draw(pagina9Sprite);
            }
            else if (paginaActual == 10)
            {
                window.draw(pagina10Sprite);
            }

            window.draw(botonVolver);
        }

        window.display();
    }

    return 0;
}
