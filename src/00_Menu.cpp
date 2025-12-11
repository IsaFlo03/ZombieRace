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
                    sf::FloatRect playBounds = botonPlay.getGlobalBounds();
                    sf::FloatRect zombiepediaBounds = botonZombiepedia.getGlobalBounds();
                    
                    if (playBounds.contains(mousePos.x, mousePos.y))
                    {
                        juegoIniciado = true;
                    }
                    if (zombiepediaBounds.contains(mousePos.x, mousePos.y))
                    {
                        zombiepediaAbierta = true;
                    }
                }
            }
        }

        // Efecto hover en el botón
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        
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

        // Si el juego ha iniciado, mostrar pantalla vacía para el juego
        if (juegoIniciado)
        {
            window.clear(sf::Color::Black);
            
            // Aquí irá el contenido del juego
            sf::Text mensajeJuego;
            mensajeJuego.setFont(font);
            mensajeJuego.setString("El juego comenzara aqui...");
            mensajeJuego.setCharacterSize(40);
            mensajeJuego.setFillColor(sf::Color::White);
            mensajeJuego.setPosition(150, 270);
            
            window.draw(mensajeJuego);
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
