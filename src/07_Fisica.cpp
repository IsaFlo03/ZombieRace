#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
using namespace std;

int main()
{
    float fuerza = 100.0f;

    // Crear una ventana de SFML
    sf::RenderWindow ventana(sf::VideoMode(800, 600), "Ejemplo de Fisica con Box2D y SFML");

    // Crear un mundo de Box2D v3.x
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = {0.0f, 10.0f};
    b2WorldId mundo = b2CreateWorld(&worldDef);

    // Crear un suelo estático
    b2BodyDef cuerpoSueloDef = b2DefaultBodyDef();
    cuerpoSueloDef.position = {400.0f, 500.0f};
    b2BodyId cuerpoSuelo = b2CreateBody(mundo, &cuerpoSueloDef);

    // Crear una forma rectangular
    int boxWidth = 600;
    int boxHeight = 10;
    b2Polygon formaSuelo = b2MakeBox(boxWidth / 2.0f, boxHeight / 2.0f);

    // Agregar la forma al cuerpo
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.friction = 1.0f;
    b2CreatePolygonShape(cuerpoSuelo, &shapeDef, &formaSuelo);

    // Crear un cuerpo dinámico
    b2BodyDef cuerpoBolaDef = b2DefaultBodyDef();
    cuerpoBolaDef.type = b2_dynamicBody;
    cuerpoBolaDef.position = {400.0f, 100.0f};
    b2BodyId cuerpoBola = b2CreateBody(mundo, &cuerpoBolaDef);

    // Crear una forma circular
    float radioCirculo = 25.0f;
    b2Circle formaBola = {{0.0f, 0.0f}, radioCirculo};

    // Agregar la forma al cuerpo
    b2ShapeDef shapeDefBola = b2DefaultShapeDef();
    shapeDefBola.density = 1.0f;
    shapeDefBola.friction = 0.7f;
    b2CreateCircleShape(cuerpoBola, &shapeDefBola, &formaBola);

    // Bucle principal del juego
    while (ventana.isOpen())
    {
        // Procesar eventos
        sf::Event evento;
        while (ventana.pollEvent(evento))
        {
            if (evento.type == sf::Event::Closed)
                ventana.close();
        }

        // Controlar la bola con el teclado
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            b2Body_ApplyLinearImpulse(cuerpoBola, {-fuerza, 0.0f}, b2Body_GetWorldPoint(cuerpoBola, {0.0f, 0.0f}), true);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            b2Body_ApplyLinearImpulse(cuerpoBola, {fuerza, 0.0f}, b2Body_GetWorldPoint(cuerpoBola, {0.0f, 0.0f}), true);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            b2Body_ApplyLinearImpulse(cuerpoBola, {0.0f, -fuerza}, b2Body_GetWorldPoint(cuerpoBola, {0.0f, 0.0f}), true);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            b2Body_ApplyLinearImpulse(cuerpoBola, {0.0f, fuerza}, b2Body_GetWorldPoint(cuerpoBola, {0.0f, 0.0f}), true);

        // Actualizar el mundo de Box2D
        b2World_Step(mundo, 1.0f / 60.0f, 4);
        
        b2Vec2 posicionBola = b2Body_GetPosition(cuerpoBola);
        cout << "Posicion de la bola: " << posicionBola.x << ", " << posicionBola.y << endl;

        // Limpiar la ventana
        ventana.clear();

        // Dibujar el suelo
        b2Vec2 posicionSuelo = b2Body_GetPosition(cuerpoSuelo);
        sf::RectangleShape suelo(sf::Vector2f(boxWidth, boxHeight));
        suelo.setOrigin(boxWidth / 2.0f, boxHeight / 2.0f);
        suelo.setPosition(posicionSuelo.x, posicionSuelo.y);
        ventana.draw(suelo);

        // Dibujar la bola
        sf::CircleShape bola(radioCirculo);
        bola.setOrigin(radioCirculo, radioCirculo);
        bola.setFillColor(sf::Color::Red);
        bola.setPosition(posicionBola.x, posicionBola.y);
        ventana.draw(bola);

        // Mostrar la ventana
        ventana.display();
    }

    // Limpiar recursos
    b2DestroyWorld(mundo);

    return 0;
}

