#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
using namespace std;

int main()
{
    float fuerza = 100.0f;

    // Crear una ventana de SFML
    sf::RenderWindow ventana(sf::VideoMode(800, 600), "Ejemplo de Fisica con Box2D y SFML");

    // Crear un mundo de Box2D
    b2Vec2 vectorGravedad = {0.0f, 10.0f};
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = vectorGravedad;
    b2WorldId mundoId = b2CreateWorld(&worldDef);

    // Crear un suelo estático
    b2BodyDef cuerpoSueloDef = b2DefaultBodyDef();
    cuerpoSueloDef.position = {400.0f, 500.0f};
    b2BodyId cuerpoSueloId = b2CreateBody(mundoId, &cuerpoSueloDef);

    // Crear una forma rectangular
    int boxWidth = 600;
    int boxHeight = 10;
    b2Polygon formaSuelo = b2MakeBox(boxWidth / 2.0f, boxHeight / 2.0f);
    
    // Agregar la forma al cuerpo
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.friction = 1.0f;
    b2CreatePolygonShape(cuerpoSueloId, &shapeDef, &formaSuelo);

    // Crear un cuerpo dinámico
    b2BodyDef cuerpoBolaDef = b2DefaultBodyDef();
    cuerpoBolaDef.type = b2_dynamicBody;
    cuerpoBolaDef.position = {400.0f, 100.0f};
    b2BodyId cuerpoBolaId = b2CreateBody(mundoId, &cuerpoBolaDef);

    // Crear una forma circular
    float radioFormaBola = 25.0f;
    b2Circle formaBola = {{0.0f, 0.0f}, radioFormaBola};

    // Agregar la forma al cuerpo
    b2ShapeDef shapeDefBola = b2DefaultShapeDef();
    shapeDefBola.density = 1.0f;
    shapeDefBola.friction = 0.7f;
    b2CreateCircleShape(cuerpoBolaId, &shapeDefBola, &formaBola);

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
            b2Body_ApplyLinearImpulseToCenter(cuerpoBolaId, {-fuerza, 0.0f}, true);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            b2Body_ApplyLinearImpulseToCenter(cuerpoBolaId, {fuerza, 0.0f}, true);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            b2Body_ApplyLinearImpulseToCenter(cuerpoBolaId, {0.0f, -fuerza}, true);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            b2Body_ApplyLinearImpulseToCenter(cuerpoBolaId, {0.0f, fuerza}, true);

        // Actualizar el mundo de Box2D
        float timeStep = 1.0f / 60.0f;
        int subStepCount = 4;
        b2World_Step(mundoId, timeStep, subStepCount);
        
        b2Vec2 posicionBola = b2Body_GetPosition(cuerpoBolaId);
        cout << "Posicion de la bola: " << posicionBola.x << ", " << posicionBola.y << endl;

        // Limpiar la ventana
        ventana.clear();

        // Dibujar el suelo
        b2Vec2 posicionSuelo = b2Body_GetPosition(cuerpoSueloId);
        sf::RectangleShape suelo(sf::Vector2f(boxWidth, boxHeight));
        suelo.setOrigin(boxWidth / 2.0f, boxHeight / 2.0f);
        suelo.setPosition(posicionSuelo.x, posicionSuelo.y);
        ventana.draw(suelo);

        // Dibujar la bola
        sf::CircleShape bola(radioFormaBola);
        bola.setOrigin(radioFormaBola, radioFormaBola);
        bola.setFillColor(sf::Color::Red);
        bola.setPosition(posicionBola.x, posicionBola.y);
        ventana.draw(bola);

        // Mostrar la ventana
        ventana.display();
    }

    // Limpiar recursos
    b2DestroyWorld(mundoId);

    return 0;
}

